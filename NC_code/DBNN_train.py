import torch
import argparse
import json
import torch.nn as nn
import torch.nn.functional as F
from torch.nn.parameter import Parameter
from torch.utils.data import Dataset, DataLoader, random_split
import math
import json
import numpy as np
import matplotlib.pyplot as plt
import torch.optim as optim
import pickle
import time
from scipy.optimize import minimize
from tqdm import *
plt.rcParams.update({'font.size': 20})


# 设置命令行参数解析
def parse_args():
    parser = argparse.ArgumentParser(description="Train DBNN Model")
    parser.add_argument('--cuda', type=int, default=0, help="CUDA device (default: 0)")
    parser.add_argument('--bs', type=int, default=16, help="Batch size for training (default: 64)")
    parser.add_argument('--lr', type=float, default=0.08, help="Learning rate (default: 0.02)")
    parser.add_argument('--epochs', type=int, default=1500, help="Numer of epochs for training (default: 100)")
    parser.add_argument('--step_size', type=int, default=300, help="Number of epochs for learning rate decay (default: 100)")
    parser.add_argument('--gamma', type=float, default=1, help="Learning rate decay factor (default: 1)")
    return parser.parse_args()

args = parse_args()

# 设置设备
device = torch.device(f"cuda:{args.cuda}" if torch.cuda.is_available() else "cpu")
# Set the diagonal element of the bilinear matrix to be always zero

class BilinearModified(nn.Module):
    __constants__ = ['in1_features', 'in2_features', 'out_features']
    in1_features: int
    in2_features: int
    out_features: int
    weight: torch.Tensor

    def __init__(self, in1_features: int, in2_features: int, out_features: int, bias: bool = True,
                 device=None, dtype=None) -> None:
        factory_kwargs = {'device': device, 'dtype': dtype}
        super().__init__()
        self.in1_features = in1_features
        self.in2_features = in2_features
        self.out_features = out_features
        self.weight = Parameter(torch.empty((out_features, in1_features, in2_features), **factory_kwargs))

        if bias:
            # Use register_buffer to make bias a non-trainable fixed value (-70)
            self.register_buffer('bias', torch.tensor([-66.3], **factory_kwargs))
            # self.bias = Parameter(torch.tensor([-66.3], **factory_kwargs))
        else:
            self.register_parameter('bias', None)
        self.reset_parameters()
        # if bias:
        #     self.bias = Parameter(torch.empty(out_features, **factory_kwargs))
        # else:
        #     self.register_parameter('bias', None)
        # self.reset_parameters()

    def reset_parameters(self) -> None:
        bound = 1 / math.sqrt(self.weight.size(1))
        nn.init.uniform_(self.weight, -bound, bound)
        # if self.bias is not None:
        #     nn.init.uniform_(self.bias, -bound, bound)
        
        # Zero out the diagonal elements of the weight matrix
        with torch.no_grad():
            for i in range(min(self.in1_features, self.in2_features)):
                self.weight[:, i, i] = 0

    def forward(self, input1: torch.Tensor, input2: torch.Tensor) -> torch.Tensor:
        # Ensure diagonal elements are zero during the forward pass as well
        with torch.no_grad():
            for i in range(min(self.in1_features, self.in2_features)):
                self.weight[:, i, i] = 0

        return F.bilinear(input1, input2, self.weight, self.bias)

    def extra_repr(self) -> str:
        return (f'in1_features={self.in1_features}, in2_features={self.in2_features}, '
                f'out_features={self.out_features}, bias={self.bias is not None}')


class TimeSeriesDataset(Dataset):
    def __init__(self, data, targets):
        self.data = data
        self.targets = targets
    
    def __len__(self):
        return len(self.data)
    
    def __getitem__(self, idx):
        return self.data[idx], self.targets[idx]
    

# input size: (batch_size, N_synapse, time_dur)
# kernels size: (N_synapse, 1, time_dur)
# output after convolution: (batch_size, N_synapse, time_dur)
# transpose to (batch_size, time_dur, N_synapse)
# bilinear matrix size: (N_synapse, N_synapse, 1)
# output size: (batch_size, time_dur)

class DBNN(nn.Module):
    def __init__(self, num_dimensions, time_dur, device):
        super(DBNN, self).__init__()
        self.num_dimensions = num_dimensions
        self.time_dur = time_dur
        self.device = device
        # intinial values
        self.tau_rise = nn.Parameter(torch.ones(num_dimensions).to(self.device) * 5)
        self.tau_decay = nn.Parameter(torch.ones(num_dimensions).to(self.device) * 20)
        self.omega = nn.Parameter(torch.ones(num_dimensions).to(self.device) * 2)

        self.bilinear = BilinearModified(num_dimensions, num_dimensions, 1).to(self.device)

    def create_kernels(self):
        T = torch.arange(self.time_dur).to(self.device)
        N = self.num_dimensions
        net_tau_rise = self.tau_rise.unsqueeze(1)  # (N, 1)
        net_tau_decay = self.tau_decay.unsqueeze(1)  # (N, 1)
        net_omega = self.omega.unsqueeze(1)  # (N, 1)

        kernels = net_omega * (1 - torch.exp(-T / net_tau_rise)) * torch.exp(-T / net_tau_decay)
        return kernels.unsqueeze(1)
        
    def forward(self, x):

        kernels = self.create_kernels()
        kernel_flipped = torch.flip(kernels, dims=[2])

        # Convolve using the kernel (perform manual convolution)
        y = torch.nn.functional.conv1d(x, kernel_flipped, groups=self.num_dimensions, padding=self.time_dur - 1)[:, :, :self.time_dur][:,:,:self.time_dur]
        y_permuted = y.permute(0, 2, 1)
        bilinear_term = self.bilinear(y_permuted, y_permuted)
        linear_term = torch.sum(y_permuted, dim=2).unsqueeze(-1)
        output = bilinear_term + linear_term
        return output.squeeze(-1)

# set random seed
manual_seed = torch.seed()  
torch.manual_seed(manual_seed)  

print(f"Random seed used: {manual_seed}")


# load the data
# data = np.load('/data/mjy/Yeqiang/purePas_data.npz')

# input_data = data['ip_m_array']
# output_data = data['v_array']

# data = np.load('/data/mjy/Yeqiang/subthres_coarse_data.npz')
# data = np.load('/data/mjy/Yeqiang/coarse_fire_data.npz')

data = np.load('/home/mjy/project/bilinear_network/NC_code/data/data_5s_active.npz')

# input_data = data['coarse_ip_m_array']
# output_data = data['coarse_v_array']
input_data = data['ip']
output_data = data['op']

train_input = torch.tensor(input_data[:1000], dtype=torch.float32).to(device)
train_output = torch.tensor(output_data[:1000], dtype=torch.float32).to(device)
val_input = torch.tensor(input_data[1000:1100], dtype=torch.float32).to(device)
val_output = torch.tensor(output_data[1000:1100], dtype=torch.float32).to(device)
test_input = torch.tensor(input_data[1100:], dtype=torch.float32).to(device)
test_output = torch.tensor(output_data[1100:], dtype=torch.float32).to(device)

print('Data loaded')

num_dimensions = train_input.size()[1]
time_dur = train_input.size()[2]
# print(f'Number of synapses is: {num_dimensions}')
# print(f'Time duration is: {int(time_dur-1)} ms')

model = DBNN(num_dimensions=num_dimensions, time_dur=time_dur, device=device)
print('----------------------------------------')
print('Model created')
# print('Parameters contained:')
# for name, param in model.named_parameters():
#     print(name, param.size())


batch_size = args.bs
learning_rate = args.lr
num_epochs = args.epochs
step_size = args.step_size
gamma = args.gamma

train_dataset = TimeSeriesDataset(train_input, train_output)
val_dataset = TimeSeriesDataset(val_input, val_output)
test_dataset = TimeSeriesDataset(test_input, test_output)

train_loader = DataLoader(train_dataset, batch_size=batch_size, shuffle=True)
val_loader = DataLoader(val_dataset, batch_size=batch_size, shuffle=False)
test_loader = DataLoader(test_dataset, batch_size=batch_size, shuffle=False)


# MSE Loss
criterion = nn.MSELoss()

# =Adam
optimizer = optim.Adam(model.parameters(), lr=learning_rate)

# learning rate scheduler
# scheduler = torch.optim.lr_scheduler.StepLR(optimizer, step_size=step_size, gamma=gamma)

# training start
print('Training started')
start_time = time.time()

train_losses = []
val_losses = []
test_losses = []  # 仍然保留你原来的测试记录逻辑（可选）

best_val_loss = float('inf')
best_epoch = -1

# 路径：分别保存 best 和 last
# save_path_best = f'/home/mjy/project/bilinear_network/NC_code/parameters/DBNN_spike_bs{batch_size}_lr{learning_rate}_epochs{num_epochs}_seed{manual_seed}_BEST.pth'
save_path_last = f'/home/mjy/project/bilinear_network/NC_code/parameters/DBNN_spike_bs{batch_size}_lr{learning_rate}_epochs{num_epochs}_seed{manual_seed}_LAST.pth'

for epoch in tqdm(range(num_epochs), desc="Training Epochs"):
    # ---- train ----
    model.train()
    running_loss = 0.0
    for batch_data, batch_targets in train_loader:
        optimizer.zero_grad()
        output = model(batch_data)
        loss = criterion(output, batch_targets)
        loss.backward()
        optimizer.step()
        running_loss += loss.item() * batch_data.size(0)

    epoch_train_loss = running_loss / len(train_loader.dataset)
    train_losses.append(epoch_train_loss)

    # ---- validate ----
    # model.eval()
    # val_loss = 0.0
    # with torch.no_grad():
    #     for batch_data, batch_targets in val_loader:
    #         output = model(batch_data)
    #         loss = criterion(output, batch_targets)
    #         val_loss += loss.item() * batch_data.size(0)
    # epoch_val_loss = val_loss / len(val_loader.dataset)
    # val_losses.append(epoch_val_loss)

    # 打印
    if (epoch + 1) % 50 == 0 or epoch == 0 or epoch == num_epochs - 1:
        # print(f'Epoch [{epoch+1}/{num_epochs}]  Train: {epoch_train_loss:.4f}  Val: {epoch_val_loss:.4f}')
        print(f'Epoch [{epoch+1}/{num_epochs}]  Train: {epoch_train_loss:.4f}')

    # # ---- 保存验证最优 ----
    # if epoch_val_loss < best_val_loss:
    #     best_val_loss = epoch_val_loss
    #     best_epoch = epoch + 1
    #     torch.save(model.state_dict(), save_path_best)
    #     print(f"New best model at epoch {best_epoch}: val_loss={best_val_loss:.6f}")

    # # （可选）维持你原来每100个epoch在test上看一次
    # if (epoch + 1) % 100 == 0:
    #     test_loss_epoch = 0.0
    #     with torch.no_grad():
    #         for batch_data, batch_targets in test_loader:
    #             output = model(batch_data)
    #             loss = criterion(output, batch_targets)
    #             test_loss_epoch += loss.item() * batch_data.size(0)
    #     test_loss_epoch /= len(test_loader.dataset)
    #     test_losses.append(test_loss_epoch)
    #     print('----------------------------------------')
    #     print(f'Epoch [{epoch+1}/{num_epochs}], Test Loss: {test_loss_epoch:.4f}')

# 训练结束，保存最后一次参数
torch.save(model.state_dict(), save_path_last)

# 用最佳参数评估测试集（推荐）
# model.load_state_dict(torch.load(save_path_best, map_location=device))
# model.eval()
# final_test_loss = 0.0
# with torch.no_grad():
#     for batch_data, batch_targets in test_loader:
#         output = model(batch_data)
#         loss = criterion(output, batch_targets)
#         final_test_loss += loss.item() * batch_data.size(0)
# final_test_loss /= len(test_loader.dataset)

# print(f"Training complete.")
# # print(f"Best val model saved at: {save_path_best}  (epoch={best_epoch}, val_loss={best_val_loss:.6f})")
print(f"Last model saved at:     {save_path_last}")
# print(f"Final Test Loss (best ckpt): {final_test_loss:.6f}")

# 保存训练和测试 loss 到文件

# loss_data_path = f'/home/mjy/project/bilinear_network/NC_code/results/DBNN_purepas_loss_bs{batch_size}_lr{learning_rate}_epochs{num_epochs}_seed{manual_seed}.json'
# loss_data = {
#     "train_losses": train_losses,
#     "val_losses": val_losses,
#     "test_losses": test_losses,
#     "seed": manual_seed,
#     "best_epoch": best_epoch,
#     "best_val_loss": best_val_loss,
#     "final_test_loss_from_best": final_test_loss
# }
# with open(loss_data_path, 'w') as f:
#     json.dump(loss_data, f)
# print(f"Training results saved to {loss_data_path}.")


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
import geatpy as ea
plt.rcParams.update({'font.size': 20})


# 设置命令行参数解析
def parse_args():
    parser = argparse.ArgumentParser(description="Train DBNN Model")
    parser.add_argument('--cuda', type=int, default=0, help="CUDA device (default: 0)")
    parser.add_argument('--batch_size', type=int, default=16, help="Batch size for training (default: 64)")
    parser.add_argument('--learning_rate', type=float, default=0.02, help="Learning rate (default: 0.02)")
    parser.add_argument('--num_epochs', type=int, default=100, help="Number of epochs for training (default: 100)")
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
            self.register_buffer('bias', torch.tensor([-70.0], **factory_kwargs))
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

# class DBNN(nn.Module):
#     def __init__(self, num_dimensions, time_dur, device):
#         super(DBNN, self).__init__()
#         self.num_dimensions = num_dimensions
#         self.time_dur = time_dur
#         self.device = device
#         # intinial values
#         self.tau_rise = nn.Parameter(torch.ones(num_dimensions).to(self.device) * 50)
#         self.tau_decay = nn.Parameter(torch.ones(num_dimensions).to(self.device) * 200)
#         self.omega = nn.Parameter(torch.ones(num_dimensions).to(self.device) * 2)

#         self.bilinear = BilinearModified(num_dimensions, num_dimensions, 1).to(self.device)

#     def create_kernels(self):
#         T = torch.arange(self.time_dur).to(self.device)
#         N = self.num_dimensions
#         net_tau_rise = self.tau_rise.unsqueeze(1)  # (N, 1)
#         net_tau_decay = self.tau_decay.unsqueeze(1)  # (N, 1)
#         net_omega = self.omega.unsqueeze(1)  # (N, 1)

#         kernels = net_omega * (1 - torch.exp(-T / net_tau_rise)) * torch.exp(-T / net_tau_decay)
#         return kernels.unsqueeze(1)
        
#     def forward(self, x):

#         kernels = self.create_kernels()
#         kernel_flipped = torch.flip(kernels, dims=[2])

#         # Convolve using the kernel (perform manual convolution)
#         y = torch.nn.functional.conv1d(x, kernel_flipped, groups=self.num_dimensions, padding=self.time_dur - 1)[:, :, :self.time_dur][:,:,:self.time_dur]
#         y_permuted = y.permute(0, 2, 1)
#         bilinear_term = self.bilinear(y_permuted, y_permuted)
#         linear_term = torch.sum(y_permuted, dim=2).unsqueeze(-1)
#         output = bilinear_term + linear_term
#         return output.squeeze(-1)


class DBNN(nn.Module):
    def __init__(self, num_dimensions, time_dur, device):
        super(DBNN, self).__init__()
        self.num_dimensions = num_dimensions
        self.time_dur = time_dur
        self.device = device
        self.thres = -55
        # intinial values
        self.tau_reset = nn.Parameter(torch.ones(1).to(self.device)*8)
        self.tau_rise = nn.Parameter(torch.ones(num_dimensions).to(self.device) * 20)
        self.tau_decay = nn.Parameter(torch.ones(num_dimensions).to(self.device) * 30)
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
    
    def reset_fun(self,t):
        return -15 * torch.exp(-t / self.tau_reset)

    def forward(self, x):

        kernels = self.create_kernels()
        kernel_flipped = torch.flip(kernels, dims=[2])

        # Convolve using the kernel (perform manual convolution)
        y = torch.nn.functional.conv1d(x, kernel_flipped, groups=self.num_dimensions, padding=self.time_dur - 1)[:, :, :self.time_dur][:,:,:self.time_dur]
        y_permuted = y.permute(0, 2, 1)
        bilinear_term = self.bilinear(y_permuted, y_permuted)
        linear_term = torch.sum(y_permuted, dim=2).unsqueeze(-1)
        output = bilinear_term + linear_term
        #find firing time and add reset
        #为节省时间，可以把单个reset_fun记录下来，后面直接切片调用
        
        #卷积操作虽然不用逐个循环但是也还是需要重复计算，貌似不会省时间
        #还是逐个循环吧，从前往后依次reset，但是batch_size的问题
        
        op = output.squeeze(-1)
        len_t = op.shape[1]
        reset_rd = self.reset_fun(torch.arange(len_t).to(self.device))
        for i in range(len(op)):
            #获取第一个跨过阈值的下标
            # while True:
            #     indices = ((op[i][:-1] < self.thres) & (op[i][1:] > self.thres)).nonzero(as_tuple=False)+1
            #     if len(indices)==0:
            #         break
            #     firing_id = indices[0][0]
            #     op[i][firing_id:]+=reset_rd[:len_t-firing_id]
            indices = ((op[i][:-1] < self.thres) & (op[i][1:] > self.thres)).nonzero(as_tuple=False) + 1

            for j in range(len(indices)):
                firing_id = indices[j][0]
                op[i][firing_id:] += reset_rd[:len_t - firing_id]
        return op

# set random seed
manual_seed = torch.seed()  
torch.manual_seed(manual_seed)  

print(f"Random seed used: {manual_seed}")


# load the data
# data = np.load('/data/mjy/Yeqiang/purePas_data.npz')

# input_data = data['ip_m_array']
# output_data = data['v_array']

data = np.load('/data/mjy/Yeqiang/coarse_fire_data.npz')

input_data = data['coarse_ip_m_array']
output_data = data['coarse_v_array']

train_input = torch.tensor(input_data[:1000], dtype=torch.float32).to(device)
train_output = torch.tensor(output_data[:1000], dtype=torch.float32).to(device)
test_input = torch.tensor(input_data[1000:], dtype=torch.float32).to(device)
test_output = torch.tensor(output_data[1000:], dtype=torch.float32).to(device)

train_dataset = TimeSeriesDataset(train_input, train_output)
test_dataset = TimeSeriesDataset(test_input, test_output)

print('Data loaded')

num_dimensions = train_input.size()[1]
time_dur = train_input.size()[2]
print(f'Number of synapses is: {num_dimensions}')
print(f'Time duration is: {int(time_dur-1)} ms')

model = DBNN(num_dimensions=num_dimensions, time_dur=time_dur, device=device)
print('Model created')
print('Parameters contained:')
for name, param in model.named_parameters():
    print(name, param.size())


batch_size = args.batch_size
learning_rate = args.learning_rate
num_epochs = args.num_epochs
step_size = args.step_size
gamma = args.gamma

train_loader = DataLoader(train_dataset, batch_size=batch_size, shuffle=True)
test_loader = DataLoader(test_dataset, batch_size=batch_size, shuffle=False)

# MSE Loss
criterion = nn.MSELoss()

# =Adam
optimizer = optim.Adam(model.parameters(), lr=learning_rate)

# learning rate scheduler
# scheduler = torch.optim.lr_scheduler.StepLR(optimizer, step_size=step_size, gamma=gamma)

# training start
# training start
print('Training started')
start_time = time.time()

# 创建用于保存训练和测试 loss 的列表
train_losses = []
test_losses = []

for epoch in range(num_epochs):
    epoch_start_time = time.time()  # record the start time of each epoch

    model.train()  
    running_loss = 0.0
    for batch_data, batch_targets in train_loader:
        optimizer.zero_grad()  

        # forward pass
        output = model(batch_data)

        # calculate the loss
        loss = criterion(output, batch_targets)
        loss.backward()  
        optimizer.step()  

        running_loss += loss.item() * batch_data.size(0)

    epoch_loss = running_loss / len(train_loader.dataset)
    train_losses.append(epoch_loss)  # 保存训练 loss
    
    epoch_end_time = time.time()  # record the end time of each epoch
    epoch_time = epoch_end_time - epoch_start_time  # calculate the time of each epoch

    print(f'Epoch [{epoch+1}/{num_epochs}], Loss: {epoch_loss:.4f}, Time: {epoch_time:.2f} seconds')


    # scheduler.step()

    # check the test loss every 10 epochs
    if (epoch + 1) % 10 == 0:
        model.eval()  # switch to evaluation mode
        test_loss = 0.0

        with torch.no_grad():
            for batch_data, batch_targets in test_loader:
                # forward pass
                output = model(batch_data)

                # calculate the loss
                loss = criterion(output, batch_targets)
                test_loss += loss.item() * batch_data.size(0)

        test_loss /= len(test_loader.dataset)
        test_losses.append(test_loss)  # 保存测试 loss
        print(f'Epoch [{epoch+1}/{num_epochs}], Test Loss: {test_loss:.4f}')

# record the end time of the training process
end_time = time.time()
total_time = end_time - start_time

# save the model
save_path = f'/home/mjy/project/bilinear_network/parameters/spike_model_coarse_bs{batch_size}_lr{learning_rate}_epochs{num_epochs}_seed{manual_seed}.pth'
loss_data_path = f'/home/mjy/project/bilinear_network/training_results/spike_loss_data_bs{batch_size}_lr{learning_rate}_epochs{num_epochs}_seed{manual_seed}.json'

torch.save(model.state_dict(), save_path)
print(f"Training complete and model saved at {save_path}")
print(f"Total training time: {total_time:.2f} seconds")

# 保存训练和测试 loss 到文件
loss_data = {
    "train_losses": train_losses,
    "test_losses": test_losses,
    "seed": manual_seed  # 记录所使用的随机数种子
}
with open(loss_data_path, 'w') as f:
    json.dump(loss_data, f)

print("Training results saved.")

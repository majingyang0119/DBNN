import numpy as np 
import matplotlib.pyplot as plt
import pickle
import os

def generate_binary_poisson_spike_train(rate, duration, dt):
    """
    Generate a binary Poisson spike train.

    Parameters:
    - rate: Average number of spikes per second (Hz)
    - duration: Duration of the spike train in seconds
    - dt: Time step in seconds

    Returns:
    - spike_train: Array of 0s and 1s where 1 indicates a spike
    """
    num_time_bins = int(duration / dt)
    spike_train = np.zeros(num_time_bins)

    # Calculate the probability of a spike in each time bin
    spike_prob = rate * dt

    # Generate spikes
    spike_train = np.random.rand(num_time_bins) < spike_prob

    return spike_train.astype(int)

# Initialize parameters
num_tr_samples = 10000  # Total number of training samples
num_classes = 10  # Number of classes
num_features = 5  # Number of features per sample (dimensions)
duration = 1000  # Duration of the spike train (ms)
dt = 1  # Time step (ms)
rate = 5 / 1000 # Average number of spikes per second (Hz)

# Initialize empty arrays for data and labels
X_tr = np.zeros((num_tr_samples, num_features, duration))  # Training set
labels_tr = np.zeros(num_tr_samples, dtype=int)  # Labels

# Define which two dimensions are correlated in each class
related_features = [(0, 1), (0, 2), (0, 3), (1, 2), (1, 3), (1, 4), (2, 3), (2, 4), (3, 4), (0, 4)]

# Generate data
for i in range(num_tr_samples):
    class_label = i % num_classes  # Assign a class label (0-9) for each sample
    rel_feat = related_features[class_label]  # Get the indices of correlated features
    
    # Generate other non-correlated features
    for feat in range(num_features):
        if feat not in rel_feat:
            X_tr[i, feat] = generate_binary_poisson_spike_train(rate, duration, dt)
    
    # Generate correlated features
    base_value = generate_binary_poisson_spike_train(rate, duration, dt)
    X_tr[i, rel_feat[0]] = base_value
    X_tr[i, rel_feat[1]] = base_value # The second feature is the same as the first one
    
    labels_tr[i] = class_label

num_test_samples = 1000  # Total number of test samples

X_test = np.zeros((num_test_samples, num_features, duration))  # Training set
labels_test = np.zeros(num_test_samples, dtype=int)  # Labels
for i in range(num_test_samples):
    class_label = i % num_classes  # Assign a class label (0-9) for each sample
    rel_feat = related_features[class_label]  # Get the indices of correlated features
    
    # Generate other non-correlated features
    for feat in range(num_features):
        if feat not in rel_feat:
            X_test[i, feat] = generate_binary_poisson_spike_train(rate, duration, dt)
    
    # Generate correlated features
    base_value = generate_binary_poisson_spike_train(rate, duration, dt)
    X_test[i, rel_feat[0]] = base_value
    X_test[i, rel_feat[1]] = base_value # The second feature is the same as the first one
    
    labels_test[i] = class_label

dir_path = 'data'
file_name_X_tr = 'tr_input_corr100%_2.pkl'
file_name_Y_tr = 'tr_output_corr100%_2.pkl'
file_name_X_test = 'test_input_corr100%_2.pkl'
file_name_Y_test = 'test_output_corr100%_2.pkl'

file_path_X_tr = os.path.join(dir_path, file_name_X_tr)
file_path_Y_tr = os.path.join(dir_path, file_name_Y_tr)
file_path_X_test = os.path.join(dir_path, file_name_X_test)
file_path_Y_test = os.path.join(dir_path, file_name_Y_test)

with open(file_path_X_tr, 'wb') as f:
    pickle.dump(X_tr, f)
with open(file_path_Y_tr, 'wb') as f:
    pickle.dump(labels_tr, f)
with open(file_path_X_test, 'wb') as f:
    pickle.dump(X_test, f)
with open(file_path_Y_test, 'wb') as f:
    pickle.dump(labels_test, f)

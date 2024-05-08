import numpy as np
import torch
import torch.nn as nn
import torch.optim as optim
import matplotlib.pyplot as plt
import pandas as pd
import time

data = pd.read_csv('reglap8apr.csv')
data_x = np.array([data.values[:, 0], data.values[:, 1]], dtype=np.float32)
data_y = np.array([data.values[:, 2]], dtype=np.float32)
data_x = data_x.transpose()
data_y = data_y.transpose()

data_x = torch.from_numpy(data_x)
data_y = torch.from_numpy(data_y)


class NeuralNet(nn.Module):
    def __init__(self):
        super(NeuralNet, self).__init__()
        self.act_func = nn.Sigmoid()
        self.layer1 = nn.Linear(2, 36)
        self.layer2 = nn.Linear(36, 36)
        self.layer3 = nn.Linear(36, 1)

    def forward(self, x):
        x = self.act_func(self.layer1(x))
        x = self.act_func(self.layer2(x))
        x = self.layer3(x)
        return x


model = NeuralNet()
mse_loss = nn.MSELoss()
optimizer = optim.Adam(model.parameters(), lr=0.0001)

start_time = time.time()

for epoch in range(300000):
    optimizer.zero_grad()
    pred = model(data_x)
    loss = mse_loss(pred, data_y)
    loss.backward()
    optimizer.step()
    if (epoch + 1) % 1000 == 0:
        print("Epoch %d  Loss %f -> %f" %
              (epoch + 1, loss.item(), time.time()-start_time))

print("Training Done! Time: %f" % (time.time()-start_time))
torch.save(model, 'baru.pth')
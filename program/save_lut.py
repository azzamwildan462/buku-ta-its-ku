import numpy as np
import torch
import torch.nn as nn
import torch.optim as optim
import matplotlib.pyplot as plt
import csv
import pandas as pd

sudut = None
jarak_pixel = None

theta_max = 360
r_maks = 3200

model = torch.load('baru.pth')
model.eval()

lut = np.empty(r_maks*theta_max, dtype=np.int16)
input_buffer = np.random.random_sample((2, 2))

th_iter = 0
while th_iter < theta_max:
    r_iter = 500
    while r_iter < r_maks:
        index = th_iter * r_maks + r_iter
        input_buffer[0, 0] = (th_iter/180) - 1
        input_buffer[0, 1] = (r_iter/10/160) - 1
        input_buffer = torch.from_numpy(
            np.array(input_buffer, dtype=np.float32))

        pred = model(input_buffer[0, :])
        r_lap = pred.data * 600 + 600

        lut[index] = r_lap
        r_iter += 1
    th_iter += 1

lut.tofile("lut_px2cm.bin")
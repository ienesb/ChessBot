import os
import torch
from torch import nn
from torch.utils.data import DataLoader
from torchvision import datasets, transforms

import numpy as np

device = "cuda" if torch.cuda.is_available() else "cpu"

class ChessBotModel(nn.Module):
    def __init__(self):
        super(ChessBotModel, self).__init__()
        self.flatten = nn.Flatten()
        self.linear_relu_stack = nn.Sequential(
            nn.Linear(12*64, 2048),
            nn.ReLU(),
            nn.Linear(2048, 2048),
            nn.ReLU(),
            nn.Linear(2048, 3),
        )

    def forward(self, x):
        x = self.flatten(x)
        logits = self.linear_relu_stack(x)
        return logits

def train(X, Y, model):
    pass

def test(X, Y, model):
    pass

if __name__ == "__main__":
    path = "../build/data.txt"
    
    with open(path, "r") as file:
        for i, line in enumerate(file.readlines()):
            
            inputDataString, outputData = line.split(", ")
            inputData = []
            inputData[:0] = inputDataString
            outputData = outputData[:-1]
            
            if i == 0:
                X = np.array(inputData)
                Y = np.array(outputData)
            else:
                X = np.vstack((X, inputData))
                Y = np.append(Y, outputData)

            if i == 10:
                break
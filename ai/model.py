import torch
from torch import nn
from torch.utils.data import DataLoader
from torchvision import datasets, transforms

import numpy as np

import os

from dataset import ChessDataset

device = "cuda" if torch.cuda.is_available() else "cpu"

class ChessBotModel(nn.Module):
    def __init__(self):
        super(ChessBotModel, self).__init__()
        self.linear_relu_stack = nn.Sequential(
            nn.Linear(12*64, 2048),
            nn.ReLU(),
            nn.Linear(2048, 2048),
            nn.ReLU(),
            nn.Linear(2048, 3),
        )

    def forward(self, x):
        logits = self.linear_relu_stack(x)
        return logits

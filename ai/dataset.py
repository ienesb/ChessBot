import torch
from torch.utils.data import Dataset

import numpy as np

class ChessDataset(Dataset):
    def __init__(self, path="data.txt"):
        with open(path, "r") as file:
            for i, line in enumerate(file.readlines()):
                
                inputDataString, outputData = line.split(", ")
                inputData = []
                inputData[:0] = inputDataString
                d = {"1": [1,0,0], "-1": [0,1,0], "0": [0,0,1]}
                outputData = d[outputData[:-1]]
                inputData = list(map(int, inputData))
                
                if i == 0:
                    X = np.array(inputData)
                    Y = np.array(outputData)
                else:
                    X = np.vstack((X, inputData))
                    Y = np.vstack((Y, outputData))
                if i == 10:
                    break
        
        X = X.astype(np.float32)
        Y = Y.astype(np.float32)
        
        self.X = torch.from_numpy(X)
        self.Y = torch.from_numpy(Y)

    def __len__(self):
        return len(self.Y)

    def __getitem__(self, i):
        return self.X[i], self.Y[i]
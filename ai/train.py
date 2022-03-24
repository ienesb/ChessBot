import torch
from torch import nn
from torch.utils.data import DataLoader
from torchvision import datasets, transforms

import numpy as np

import argparse
import os

from dataset import ChessDataset
from model import ChessBotModel

device = "cuda" if torch.cuda.is_available() else "cpu"

def train(dataloader, model, loss_fn, optimizer):
    size = len(dataloader.dataset)
    model.train()
    for batch, (x, y) in enumerate(dataloader):
        x, y = x.to(device), y.to(device)
        pred = model(x)
        loss = loss_fn(pred, y)

        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        loss, current = loss.item(), batch * len(x)
        print(f"loss: {loss:>7f}  [{current:>5d}/{size:>5d}]")


def test(dataloader, model, loss_fn):
    size = len(dataloader.dataset)
    num_batches = len(dataloader)

    model.eval()
    test_loss, correct = 0, 0
    with torch.no_grad():
        for x, y in dataloader:
            x, y = x.to(device), y.to(device)

            pred = model(x)
            test_loss += loss_fn(pred, y).item()
            correct += (pred.argmax(1) == y).type(torch.float).sum().item()

    test_loss /= num_batches
    correct /= size
    print(f"Test Error: \n Accuracy: {(100*correct):>0.1f}%, Avg loss: {test_loss:>8f} \n")

if __name__ == "__main__":
    # params
    # save model
    # load model
    # ...

    parser = argparse.ArgumentParser(description='')
    parser.add_argument("-e", "--epoch", default=1)
    epochs = int(vars(parser.parse_args())["epoch"])

    dataset = ChessDataset()
    dataloader = DataLoader(dataset, batch_size=1, shuffle=True)
    
    model = ChessBotModel()
    model.to(device)

    optimizer = torch.optim.SGD(model.parameters(), lr=1e-3)
    loss_fn = nn.MSELoss()
    
    for e in range(epochs):
        print(f"Epoch {e+1}\n-------------------------------")
        train(dataloader, model, loss_fn, optimizer)
        test(dataloader, model, loss_fn)
    torch.save(model.state_dict(), "model.pth")
    print("Done!")
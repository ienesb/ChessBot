import torch
import argparse
import numpy as np
from model import ChessBotModel

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='')
    parser.add_argument("-i", "--input", required=True)

    model = ChessBotModel()
    model.load_state_dict(torch.load("model.pth"))
    model.eval()

    inputStr = vars(parser.parse_args())["input"]
    inputData = []
    inputData[:0] = inputStr
    inputData = list(map(int, inputData))
    X = np.array(inputData)
    X = X.astype(np.float32)
    X = torch.from_numpy(X)
    
    print(model(X)[0])

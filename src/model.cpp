#include <torch/torch.h>

#include "model.h"

ChessBotModel::ChessBotModel():torch::nn::Module(){
    this->linearLayers = torch::nn::Sequential(
            torch::nn::Linear(12*64, 2048),
            torch::nn::ReLU(),
            torch::nn::Linear(2048, 2048),
            torch::nn::ReLU(),
            torch::nn::Linear(2048, 3)
    );
}

torch::Tensor ChessBotModel::forward(torch::Tensor x){
    return this->linearLayers->forward(x);
}
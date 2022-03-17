#ifndef MODEL
#define MODEL

#include <torch/torch.h>

class ChessBotModel: torch::nn::Module{
    private:
    torch::nn::Sequential linearLayers;
    public:
    ChessBotModel();
    torch::Tensor forward(torch::Tensor x);
};
  
#endif
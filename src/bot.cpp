#include <torch/torch.h>

#include "bot.h"
#include "model.h"

Bot::Bot(std::string color, Game* game, std::string modelPath):Player::Player(color, game){

}

std::vector<Move> Bot::listAllMoves(){
    // type here
    // use game pointer and pieces vector
}
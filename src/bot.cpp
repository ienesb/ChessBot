#include <torch/torch.h>

#include "bot.h"
#include "model.h"
#include "move.h"
#include "utils.h"

Bot::Bot(std::string color, Game* game, std::string modelPath):Player::Player(color, game){

}

std::vector<Move> Bot::listAllMoves(){
    return listMoves(this->getPieces());
}
#include <torch/torch.h>

#include "bot.h"
#include "model.h"
#include "move.h"

Bot::Bot(std::string color, Game* game, std::string modelPath):Player::Player(color, game){
    // torch::load(model, modelPath);
}

std::vector<Move> Bot::listAllMoves(){
    // type here
    // use game pointer and pieces vector
}

// Move Bot::getBestMove(std::vector<Move> moves){
//     Move m, bestMove;
//     int result = 0;
//     int prediction;
//     for(m: moves){
//         prediction = this->model->forward(encode(m));
//         if(prediction > result){
//             result = prediction;
//             bestMove = m;
//         }
//     }
//     return bestMove;
// }

// int Bot::encode(Move move){
//     this->game->performMovement(move);
//     int result = getBinaryBoard(this->game);
//     this->game->undo();
//     return result;
// }
#include <torch/torch.h>

#include "bot.h"
#include "model.h"
#include "move.h"
#include "utils.h"

Bot::Bot(std::string color, Game* game, std::string modelPath):Player::Player(color, game){

}

std::vector<Move> Bot::listAllMoves(){
    /*
     * std::vector<s_pieceMove> listMoves(std::vector<Piece*> pieces, Game* game);
     *
     * Example Output:
     * std::vector<s_pieceMove>{s_pieceMove{Piece* rook, std::vector<std::vector<int>> moveCoords{{1,1},{2,3},{5,6}},
     *                          s_pieceMove{Piece* bishop, std::vector<std::vector<int>> moveCoords{{4,1},{4,2},{4,3}},
     *                          s_pieceMove{Piece* queen, std::vector<std::vector<int>> moveCoords{{7,1},{2,1},{1,6}}
     *                          }
     */
    auto package = listMoves(this->getPieces());
    return {};
}
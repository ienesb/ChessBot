#ifndef BOT
#define BOT

#include <vector>
#include <string>

#include "player.h"
#include "game.h"
#include "move.h"
#include "model.h"

class Bot: public Player{
    private:
    ChessBotModel* model;
    public:
    Bot(std::string color, Game* game, std::string modelPath);
    std::vector<Move> listAllMoves();
    Move getBestMove(std::vector<Move> moves);
    int encode(Move move);
};

#endif
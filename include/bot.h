#ifndef BOT
#define BOT

#include <vector>
#include <string>

#include "player.h"
#include "game.h"
#include "move.h"

class Bot: public Player{
    public:
    Bot(std::string color, Game* game, std::string modelPath);
    std::vector<Move> listAllMoves();
    Move getBestMove(std::vector<Move> moves);
    std::string encode(Move move);
    std::string getBinaryBoard();
    int exec(const char* cmd);
};

#endif
#ifndef BOT
#define BOT

#include <vector>
#include <string>

#include "player.h"
#include "game.h"

class Bot: public Player{
    private:
    public:
    Bot(std::string color, Game* game, std::string modelPath);
    std::vector<Move> Bot::listAllMoves();
};

#endif
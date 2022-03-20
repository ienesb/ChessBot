#ifndef MOVE
#define MOVE

#include "pieces.h"
#include "block.h"

struct Move{
    std::vector<Block*> targets;
    Piece* piece;
};
struct GameMove{ // temp move for game::performmovement(Move move) which will be removed when move struct is changed
    Block* target;
    Piece* piece;
};

#endif
#ifndef MOVE
#define MOVE

#include "pieces.h"
#include "block.h"

struct Move{
    std::vector<Block*> targets;
    Piece* piece;
};

#endif
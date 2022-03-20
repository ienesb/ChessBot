#ifndef MOVE
#define MOVE

#include "pieces.h"
#include "block.h"

struct Move{
    Block* target;
    Piece* piece;
};

#endif
#ifndef GAME
#define GAME

#include "block.h"
#include "pieces.h"

class Piece;
class Block;

class Game{
private:
    int numberOfPlayer{};
    Block* board[64]{};
    Piece* pieces[32]{};
    
public:
    Game();
    void press(Block* pressed);
    Block* getBlock(int x, int y);
    void performMovement(Piece* piece, Block* target);
    
};
#endif
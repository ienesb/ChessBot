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
    King* wKing;
    King* bKing;
    
public:
    Game();
    void press(Block* pressed);
    Block* getBlock(int x, int y);
    King* getKing(std::string color); 
    void performMovement(Piece* piece, Block* target);
    void update();
    
};
#endif
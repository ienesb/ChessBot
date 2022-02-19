#ifndef GAME
#define GAME

#include "block.h"
#include "pieces.h"

class Piece;
class Block;

class Game{
private:
    int numberOfPlayer{};
    King* wKing;
    King* bKing;
    
public:
    Block* board[64]{};
    Game(QWidget* centralwidget);
    void press(Block* pressed);
    Block* getBlock(int x, int y);
    King* getKing(std::string color); 
    void performMovement(Piece* piece, Block* target);
    void update();
    
};
#endif
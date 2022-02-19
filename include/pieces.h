#ifndef PIECES
#define PIECES

#include "game.h"
#include "block.h"

class Game;
class Block;

class Piece{
    private:
    std::string color; // "w" or "b" 
    Block* block;
    Game* game;

    public:
    std::string path = "";
    Piece(std::string color, Block* block, Game* game);
    void setBlock(Block* block);
    Block* getBlock();
    std::string getColor();
    virtual int checkMove(Block* target);
    Game* getGame();
};

class Knight: public Piece{
    public:
    std::string path = "pngs/pieces/at.png";
    int checkMove(Block* target) override;
};

class Bishop: public Piece{
    public:
    std::string path = "pngs/pieces/fil.png";
    int checkMove(Block* target) override;
};

class Rook: public Piece{
    public:
    std::string path = "pngs/pieces/kale.png";
    int checkMove(Block* target) override;
};

class Queen: public Piece{
    public:
    std::string path = "pngs/pieces/vezir.png";
    int checkMove(Block* target) override;
};

class King: public Piece{
    public:
    std::string path = "pngs/pieces/sah.png";
    int checkMove(Block* target) override;
};

class Pawn: public Piece{
    public:
    std::string path = "pngs/pieces/piyon.png";
    int checkMove(Block* target) override;
};

#endif
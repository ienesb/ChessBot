#ifndef PIECES
#define PIECES

#include <opencv2/opencv.hpp>

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
    std::string name = "";
    cv::Mat image;
    Piece(std::string color, Block* block, Game* game);
    void setBlock(Block* block);
    Block* getBlock();
    std::string getColor();
    virtual int checkMove(Block* target);
    Game* getGame();
};

class Knight: public Piece{
    public:
    Knight(std::string color, Block* block, Game* game);
    int checkMove(Block* target) override;
};

class Bishop: public Piece{
    public:
    Bishop(std::string color, Block* block, Game* game);
    int checkMove(Block* target) override;
};

class Rook: public Piece{
    public:
    Rook(std::string color, Block* block, Game* game);
    int checkMove(Block* target) override;
};

class Queen: public Piece{
    public:
    Queen(std::string color, Block* block, Game* game);
    int checkMove(Block* target) override;
};

class King: public Piece{
    public:
    King(std::string color, Block* block, Game* game);
    int checkMove(Block* target) override;
};

class Pawn: public Piece{
    public:
    Pawn(std::string color, Block* block, Game* game);
    int checkMove(Block* target) override;
};

#endif
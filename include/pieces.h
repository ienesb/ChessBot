#ifndef PIECES
#define PIECES

class Piece{
    private:
    std::string color; // "w" or "b" 
    Block* block;
    Game* game;

    public:
    Piece(std::string color, Block* block=nullptr);
    void setBlock(Block* block);
    Block* getBlock();
    std::string getColor();
    virtual int checkMove(Block* target);
};

class Knight: public Piece{
    public:
    int checkMove(Block* target);
};

class Bishop: public Piece{
    public:
    int checkMove(Block* target);
};

class Rook: public Piece{
    public:
    int checkMove(Block* target);
};

class Queen: public Piece{
    public:
    int checkMove(Block* target);
};

class King: public Piece{
    public:
    int checkMove(Block* target);
};

class Pawn: public Piece{
    public:
    int checkMove(Block* target);
};


#endif
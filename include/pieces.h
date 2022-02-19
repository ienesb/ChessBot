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
    Game* getGame();
};

class Knight: public Piece{
    public:
    int checkMove(Block* target) override;
};

class Bishop: public Piece{
    public:
    int checkMove(Block* target) override;
};

class Rook: public Piece{
    public:
    int checkMove(Block* target) override;
};

class Queen: public Piece{
    public:
    int checkMove(Block* target) override;
};

class King: public Piece{
    public:
    int checkMove(Block* target) override;
};

class Pawn: public Piece{
    public:
    int checkMove(Block* target) override;
};

#endif
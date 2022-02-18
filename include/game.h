#ifndef GAME
#define GAME

class Game{
    private:
    int numberOfPlayer;
    Block* board[64];
    Piece* pieces[32];
    
    public:
    Game();
    void press(Block* pressed);
    Block* getBlock(int x, int y);
    
}


#endif
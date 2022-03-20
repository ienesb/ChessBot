#ifndef PLAYER
#define PLAYER

#include <vector>
#include <string>

#include "game.h"

class Player{
    private:
    std::string color; // "w" or "b"
    Game* game;
    std::vector<Piece*> pieces;

    public:
    Player(std::string color, Game* game);
    std::string getColor();
    Game* getGame();
    void setPiece(Piece* piece);
    void removePiece(Piece* piece);
    std::vector<Piece*> getPieces();
    void printPieces();
    void updatePieces();
};

#endif
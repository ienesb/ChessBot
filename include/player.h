#ifndef PLAYER
#define PLAYER

#include <vector>
#include <string>

#include "move.h"
class Game;

class Player{
    private:
    std::string color; // "w" or "b"
    std::vector<Piece*> pieces;
    std::vector<Piece*> capturedPieces;

    public:
    Game* game;
    std::string type;
    Player(std::string color, Game* game, std::string type);
    std::string getColor();
    Game* getGame();
    void setPiece(Piece* piece);
    void removePiece(Piece* piece);
    std::vector<Piece*> getPieces();
    void printPieces();
    void updatePieces();
    std::vector<Move> listAllMoves();
    // Move getBestMove();
    std::string encode(Move move);
    std::string getBinaryBoard();
    float exec(const char* cmd);
};

#endif

#ifndef BLOCK
#define BLOCK

#include <QtWidgets/QLabel>

#include <iostream>
#include <vector>

#include "game.h"
#include "pieces.h"

class Piece;
class Game;

class Block : public QLabel{
    private:
    Piece* piece;
    Game* game;
    std::string color; // "w" or "b"
    int x; //coordinates
    int y;

    public:
    bool isClicked;
    std::string path;
    std::string clickedPath;
    void mousePressEvent(QMouseEvent *ev);
    Block(QWidget* widget, Game* game, int x, int y);
    Block(QWidget* widget, Game* game, int x, int y, Piece* piece);
    void setPiece(Piece* piece);
    Piece* getPiece();
    std::vector<int> getCoordinates();
    std::string getColor();
    void update();

};

#endif
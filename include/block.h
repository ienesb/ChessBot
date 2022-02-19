#ifndef BLOCK
#define BLOCK

#include <iostream>
#include <vector>
#include <QApplication>
#include <QLabel>

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
    void mousePressEvent(QMouseEvent *ev) override;
    Block(QDialog *Dialog, Game* game, int x, int y, Piece* piece=nullptr);
    void setPiece(Piece* piece);
    Piece* getPiece();
    std::vector<int> getCoordinates();
    std::string getColor();

};

#endif
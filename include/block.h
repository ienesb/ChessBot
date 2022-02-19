#ifndef BLOCK
#define BLOCK

#include <iostream>
#include <vector>
#include <QApplication>
#include <QLabel>

class Piece;
class Game;

class Block : public QLabel{
    private:
    Piece* piece;
    Game* game;
    char color; // "w" or "b"
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
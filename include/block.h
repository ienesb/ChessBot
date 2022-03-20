#ifndef BLOCK
#define BLOCK

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <QMouseEvent>
#include <QPixmap>
#include <opencv2/opencv.hpp>

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
    std::string name;
    int x; //coordinates
    int y;

    public:
    bool isClicked;
    std::string whitePath;
    std::string blackPath;
    std::string clickedPath;
    void mousePressEvent(QMouseEvent *ev);
    Block(QWidget* widget, Game* game, int x, int y);
    ~Block();
    void setPiece(Piece* piece);
    Piece* getPiece();
    std::vector<int> getCoordinates();
    std::string getColor();
    void update();

};

#endif
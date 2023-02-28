#ifndef BLOCK
#define BLOCK

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <QMouseEvent>
#include <QPixmap>
#include <iostream>
#include <vector>

#include "pieces.h"
class Game;

class Block : public QLabel{
    Q_OBJECT

private:
    Piece* piece;
    Game* game;
    std::string color; // "w" or "b"
    std::string name;
    int x; //coordinates
    int y;

public:
    //explicit Block(QObject *parent = nullptr);
    Block(QWidget* widget, Game* game,
          int x, int y, QGridLayout* gridLayout);
    ~Block();
    bool isClicked;
    std::string whitePath;
    std::string blackPath;
    std::string clickedPath;
    void mousePressEvent(QMouseEvent *ev);
    void setPiece(Piece* piece);
    Piece* getPiece();
    std::vector<int> getCoordinates();
    std::string getColor();
    void update();

signals:

public slots:

};

#endif

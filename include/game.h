#ifndef GAME
#define GAME

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <QMouseEvent>
#include <QPixmap>

#include "block.h"
#include "pieces.h"

#define SIZE 100

class Piece;
class Block;

class Game{
private:
    int numberOfPlayer{};
    King* wKing;
    King* bKing;
    Block* chosen;
    std::string turn;
    
public:
    Block* board[64]{};
    Game(QWidget* centralwidget);
    void press(Block* pressed);
    Block* getBlock(int x, int y);
    King* getKing(std::string color); 
    void performMovement(Piece* piece, Block* target);
    void update();
    
};
#endif
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
    bool isCheck;
    std::vector<int>* attackerCoord;
    
public:
    Block* board[64]{};
    Game(QWidget* centralWidget);
    void press(Block* pressed);
    Block* getBlock(int x, int y);
    Block* getBlock(const std::vector<int>& coord);
    King* getKing(const std::string& color);
    void performMovement(Piece* piece, Block* target);
    void update();

    void updateCheck();
    bool getCheck() const;
    std::vector<int>* getAttacker() const;
    
};
#endif
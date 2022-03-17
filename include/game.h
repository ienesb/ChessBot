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
#include "player.h"

#define SIZE 100

class Piece;
class Block;
class Player;

class Game{
private:
    // int numberOfPlayer{};
    King* wKing;
    King* bKing;
    Rook* castlingRook;
    Block* chosen;
    std::string turn;
    bool isCheck;
    std::vector<int>* attackerCoord;
    Player* whitePlayer;
    Player* blackPlayer;

    bool wCastlingLeft;
    bool wCastlingRight;
    bool bCastlingLeft;
    bool bCastlingRight;
    const std::vector<std::vector<int>> wCastlingLeftCoords = {{2,1},{3,1},{4,1}};
    const std::vector<std::vector<int>> bCastlingLeftCoords = {{2,8},{3,8},{4,8}};
    const std::vector<std::vector<int>> wCastlingRightCoords = {{6,1},{7,1}};
    const std::vector<std::vector<int>> bCastlingRightCoords = {{6,8},{7,8}};
    void updateCastling(Piece* piece, Block* target);

    
public:
    Block* board[64]{};
    Game(QWidget* centralWidget);
    void press(Block* pressed);
    Block* getBlock(int x, int y);
    Block* getBlock(const std::vector<int>& coord);
    King* getKing(const std::string& color);
    void setCastlingRook(Rook* rook);
    void performMovement(Piece* piece, Block* target);
    void performCastling(King* king, Block* target);
    void update();

    void updateCheck();
    std::vector<int>* getAttacker() const;
    std::vector<bool> getCastling() const;
};
#endif
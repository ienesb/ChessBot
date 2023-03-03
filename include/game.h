#ifndef GAME
#define GAME

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <QtMultimedia/QMediaPlayer>
#include <QMouseEvent>
#include <QPixmap>
#define SIZE 75

class MainWindow;

#include "block.h"
#include "pieces.h"
#include "move.h"
#include "player.h"

class Game{
private:
    std::string turn;
    King* wKing;
    King* bKing;
    Rook* castlingRook;
    Block* chosen;
    bool isCheck;
    std::vector<int>* attackerCoord;
    Player* whitePlayer;
    Player* blackPlayer;
    Player* mePlayer;
    Move lastMove;
    Block* undoBlock;
    Piece* undoPiece;

    QMediaPlayer *player;
    MainWindow *mainWindow;

    bool wCastlingLeft;
    bool wCastlingRight;
    bool bCastlingLeft;
    bool bCastlingRight;
    const std::vector<std::vector<int>> wCastlingLeftCoords = {{2,1},{3,1},{4,1}};
    const std::vector<std::vector<int>> bCastlingLeftCoords = {{2,8},{3,8},{4,8}};
    const std::vector<std::vector<int>> wCastlingRightCoords = {{6,1},{7,1}};
    const std::vector<std::vector<int>> bCastlingRightCoords = {{6,8},{7,8}};
    void updateCastling(Piece* piece, Block* target);
    void play_chess_sound(int mode);

    
public:
    Block* board[64]{};
    Game(QWidget* centralWidget, int gameMode, QGridLayout* gridLayout, MainWindow *MainWindow);
    void press(Block* pressed);
    Block* getBlock(int x, int y);
    Block* getBlock(const std::vector<int>& coord);
    King* getKing(const std::string& color);
    void setCastlingRook(Rook* rook);
    void performMovement(Move move);
    void undoLastMove();
    void performCastling(King* king, Block* target);
    void update();
    void setChosen(Block* block);

    int gameMode;
    bool move_done = false;
    std::vector<int> move_coord;

    void updateCheck();
    std::vector<int>* getAttacker() const;
    std::vector<bool> getCastling() const;


friend class Block;
};
#endif

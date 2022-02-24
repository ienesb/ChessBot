#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <QMouseEvent>
#include <QPixmap>

#include <iostream>
#include <vector>

#include "game.h"
#include "block.h"
#include "pieces.h"
#include "utils.h"

Game::Game(QWidget* centralWidget) {
    int i,j;
    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            this->board[8*i+j] = new Block(centralWidget, this, j + 1, 8 - i);
        }
    }
    for(i = 1; i < 9; i++){
        Pawn* wPawn = new Pawn("w", this->getBlock(i, 2), this);
        Pawn* bPawn = new Pawn("b", this->getBlock(i, 7), this);
        this->getBlock(i, 2)->setPiece(wPawn);
        this->getBlock(i, 7)->setPiece(bPawn);
        switch(i){
            case 1:
            case 8:{
                Rook* wRook = new Rook("w", this->getBlock(i, 1), this);
                Rook* bRook = new Rook("b", this->getBlock(i, 8), this);
                this->getBlock(i, 1)->setPiece(wRook);
                this->getBlock(i, 8)->setPiece(bRook);
                break;
            }
            case 2:
            case 7:{
                Knight* wKnight = new Knight("w", this->getBlock(i, 1), this);
                Knight* bKnight = new Knight("b", this->getBlock(i, 8), this);
                this->getBlock(i, 1)->setPiece(wKnight);
                this->getBlock(i, 8)->setPiece(bKnight);
                break;
            }
            case 3:
            case 6:{
                Bishop* wBishop = new Bishop("w", this->getBlock(i, 1), this);
                Bishop* bBishop = new Bishop("b", this->getBlock(i, 8), this);
                this->getBlock(i, 1)->setPiece(wBishop);
                this->getBlock(i, 8)->setPiece(bBishop);
                break;
            }
            case 4:{
                Queen* wQueen = new Queen("w", this->getBlock(i, 1), this);
                Queen* bQueen = new Queen("b", this->getBlock(i, 8), this);
                this->getBlock(i, 1)->setPiece(wQueen);
                this->getBlock(i, 8)->setPiece(bQueen);
                break;
            }
            case 5:{
                this->wKing = new King("w", this->getBlock(i, 1), this);
                this->bKing = new King("b", this->getBlock(i, 8), this);
                this->getBlock(i, 1)->setPiece(wKing);
                this->getBlock(i, 8)->setPiece(bKing);
                break;
            }
        }
    }
    this->chosen = nullptr;
    this->turn = "w";
    this->attackerCoord = new std::vector<int>(2);
    this->update();
}

void Game::press(Block *pressed) {

    if(this->chosen == nullptr){
        if(pressed->getPiece() != nullptr && pressed->getPiece()->getColor() == this->turn){
            chosen = pressed;
            pressed->isClicked = true;
        }
    }
    else{
        if(pressed == chosen){
            pressed->isClicked = false;
            chosen = nullptr;
        }
        else if(pressed->getPiece() != nullptr && pressed->getPiece()->getColor() == this->turn){
            chosen->isClicked = false;
            chosen = pressed;
            pressed->isClicked = true;
        }
        else{
            int code = chosen->getPiece()->checkMove(pressed);;

            if(code == 0){
                std::cout << "success\n";
                this->performMovement(chosen->getPiece(), pressed);
                chosen->isClicked = false;
                chosen = nullptr;
            }
            else{
                std::cout << "error " << code << "\n";
            }
        }
        this->updateCheck();
        if(this->isCheck){
            if(isCheckmate(getKing(this->turn), this)){
                std::cout << "Checkmate !!!\n" << "Game Over\n";
            }
        }
    }

    this->update();

}

Block* Game::getBlock(int x, int y){
    if(x >= 1 and y >= 1 and x < 9 and y < 9)
        return board[63-8*y+x];
    else
        return nullptr;
}

Block* Game::getBlock(const std::vector<int>& coord){
    if(!coord.empty()){
        int x = coord[0], y = coord[1];
        if(x >= 1 and y >= 1 and x < 9 and y < 9)
            return board[63-8*y+x];
    }
    return nullptr;
}

King* Game::getKing(const std::string& color){
    if(color == "w"){
        return this->wKing;
    }
    return this->bKing;
}

void Game::performMovement(Piece* piece, Block* target){
    piece->getBlock()->setPiece(nullptr);
    piece->setBlock(target);
    target->setPiece(piece);
    if(this->turn == "w"){
        this->turn = "b";
    }
    else{
        this->turn = "w";
    }
    this->update();
}

void Game::update(){
    int i;
    for(i = 0; i < 64; i++){
        this->board[i]->update();
    }
}

void Game::updateCheck(){
    *(this->attackerCoord) = isCheck_Game(this->turn, this);
    if(!this->attackerCoord->empty()){
        this->isCheck = true;
    }
    else this->isCheck = false;
}

bool Game::getCheck() const{
    return this->isCheck;
}

std::vector<int>* Game::getAttacker() const{
    return this->attackerCoord;
}


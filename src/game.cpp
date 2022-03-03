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
    this->castlingRook = nullptr;
    this->chosen = nullptr;
    this->turn = "w";
    this->attackerCoord = new std::vector<int>(2);
    this->wCastlingLeft = true;
    this->wCastlingRight = true;
    this->bCastlingLeft = true;
    this->bCastlingRight = true;
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

                this->updateCheck();
                if(this->isCheck){
                    std::cout << "CHECK " << this->turn << "\n";
                    if(isCheckmate(getKing(this->turn), this)){
                        std::cout << "Checkmate !!!\n" << "Game Over\n";
                    }
                }
            }
            else if (code == 1){
                std::cout << "success castling\n";
                this->performCastling(static_cast<King *>(chosen->getPiece()), pressed);
                chosen->isClicked = false;
                chosen = nullptr;

                this->updateCheck();
                if(this->isCheck){
                    std::cout << "CHECK " << this->turn << "\n";
                    if(isCheckmate(getKing(this->turn), this)){
                        std::cout << "Checkmate !!!\n" << "Game Over\n";
                    }
                }
            }
            else {
                std::cout << "error " << code << "\n";
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
    this->updateCastling(piece, target);

    piece->getBlock()->setPiece(nullptr);
    piece->setBlock(target);
    if (piece->name == "piyon"){
        auto targetCoord = target->getCoordinates();
        if (piece->getColor() == "w" and targetCoord[1] == 8) {
            auto queen = new Queen("w", this->getBlock(targetCoord[0], targetCoord[1]), this);
            target->setPiece(queen);
        }
        else if (piece->getColor() == "b" and targetCoord[1] == 1) {
            auto queen = new Queen("b", this->getBlock(targetCoord[0], targetCoord[1]), this);
            target->setPiece(queen);
        }
        else {
            target->setPiece(piece);
        }
    }
    else {
        target->setPiece(piece);
    }
    if(this->turn == "w"){
        this->turn = "b";
    }
    else{
        this->turn = "w";
    }
    this->update();
}

void Game::performCastling(King* king, Block* target) {
    this->updateCastling(king, target);
    king->getBlock()->setPiece(nullptr);
    king->setBlock(target);
    target->setPiece(king);
    auto targetCoord = target->getCoordinates();
    if (castlingRook->getBlock()->getCoordinates()[0] < targetCoord[0]){
       castlingRook->getBlock()->setPiece(nullptr);
       castlingRook->setBlock(this->getBlock(targetCoord[0]+1, targetCoord[1]));
       this->getBlock(targetCoord[0]+1, targetCoord[1])->setPiece(castlingRook);
    }
    else {
        castlingRook->getBlock()->setPiece(nullptr);
        castlingRook->setBlock(this->getBlock(targetCoord[0]-1, targetCoord[1]));
        this->getBlock(targetCoord[0]-1, targetCoord[1])->setPiece(castlingRook);
    }

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

std::vector<int>* Game::getAttacker() const{
    return this->attackerCoord;
}

void Game::updateCastling(Piece* piece, Block* target) {
    static bool neverEntered = true;
    if(piece->name == "kale" and neverEntered){
        Rook* rook = static_cast<Rook*>(piece);
        rook->isMoved = true;
        neverEntered = false;
    }
    else if(piece->name == "sah" and neverEntered){
        King* king = static_cast<King*>(piece);
        king->isMoved = true;
        neverEntered = false;
    }

    if(this->turn == "w"){
        if(isIn(target->getCoordinates(), this->bCastlingLeftCoords))
            this->bCastlingLeft = false;
        else if(isIn(target->getCoordinates(), this->bCastlingRightCoords))
            this->bCastlingRight = false;
    }
    else{
        if(isIn(target->getCoordinates(), this->wCastlingLeftCoords))
            this->wCastlingLeft = false;
        else if(isIn(target->getCoordinates(), this->wCastlingRightCoords))
            this->wCastlingRight = false;
    }
}

std::vector<bool> Game::getCastling() const{
    return std::vector<bool>{this->wCastlingLeft, this->wCastlingRight,
                             this->bCastlingLeft, this->bCastlingRight};
}

void Game::setCastlingRook(Rook* rook) {
    this->castlingRook = rook;
}

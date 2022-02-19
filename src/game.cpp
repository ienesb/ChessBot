#include <iostream>

#include "game.h"
#include "block.h"
#include "pieces.h"

Game::Game(QWidget* centralwidget) {
    int i,j;
    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            this->board[8*i+j] = new Block(centralwidget, this, j+1, 8-i);
        }
    }
    for(i = 1; i < 9; i++){
        Pawn* wPawn = (Pawn*) new Piece("w", this->getBlock(i, 2), this);
        Pawn* bPawn = (Pawn*) new Piece("b", this->getBlock(i, 7), this);
        this->getBlock(i, 2)->setPiece(wPawn);
        this->getBlock(i, 7)->setPiece(bPawn);
        switch(i){
            case 1:
            case 8:{
                Rook* wRook = (Rook*) new Piece("w", this->getBlock(i, 1), this);
                Rook* bRook = (Rook*) new Piece("b", this->getBlock(i, 8), this);
                this->getBlock(i, 1)->setPiece(wRook);
                this->getBlock(i, 8)->setPiece(bRook);
                break;
            }
            case 2:
            case 7:{
                Knight* wKnight = (Knight*) new Piece("w", this->getBlock(i, 1), this);
                Knight* bKnight = (Knight*) new Piece("b", this->getBlock(i, 8), this);
                this->getBlock(i, 1)->setPiece(wKnight);
                this->getBlock(i, 8)->setPiece(bKnight);
                break;
            }
            case 3:
            case 6:{
                Bishop* wBishop = (Bishop*) new Piece("w", this->getBlock(i, 1), this);
                Bishop* bBishop = (Bishop*) new Piece("b", this->getBlock(i, 8), this);
                this->getBlock(i, 1)->setPiece(wBishop);
                this->getBlock(i, 8)->setPiece(bBishop);
                break;
            }
            case 4:{
                Queen* wQueen = (Queen*) new Piece("w", this->getBlock(i, 1), this);
                this->bKing = (King*) new Piece("b", this->getBlock(i, 8), this);
                this->getBlock(i, 1)->setPiece(wQueen);
                this->getBlock(i, 8)->setPiece(bKing);
                break;
            }
            case 5:{
                this->wKing = (King*) new Piece("w", this->getBlock(i, 1), this);
                Queen* bQueen = (Queen*) new Piece("b", this->getBlock(i, 8), this);
                this->getBlock(i, 1)->setPiece(wKing);
                this->getBlock(i, 8)->setPiece(bQueen);
                break;
            }
        }
    }
    this->update();
}

void Game::press(Block *pressed) {

}

Block* Game::getBlock(int x, int y){
    return board[63-8*y+x];
}

King* Game::getKing(std::string color){
    if(color == "w"){
        return this->wKing;
    }
    return this->bKing;
}

void Game::performMovement(Piece* piece, Block* target){
    piece->getBlock()->setPiece(nullptr);
    piece->setBlock(target);
    target->setPiece(piece);
    this->update();
}

void Game::update(){
    int i;
    for(i = 0; i < 64; i++){
        this->board[i]->update();
    }
}

#include <iostream>

#include "game.h"
#include "block.h"
#include "pieces.h"

Game::Game() {

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

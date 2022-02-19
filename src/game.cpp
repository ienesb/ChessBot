#include <iostream>

#include "game.h"
#include "block.h"
#include "pieces.h"

Game::Game() {

}

void Game::press(Block *pressed) {

}

Block *Game::getBlock(int x, int y) {
    return nullptr;
}

Block* Game::getBlock(int x, int y){
    return board[63-8*y+x];
}

void Game::performMovement(Piece* piece, Block* target){
    piece->getBlock()->setPiece(nullptr);
    piece->setBlock(target);
    target->setPiece(piece);
}

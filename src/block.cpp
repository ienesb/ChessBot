#include <QtWidgets/QLabel>

#include <iostream>
#include <vector>

#include "game.h"
#include "block.h"
#include "pieces.h"

void Block::mousePressEvent(QMouseEvent *ev){
    this->game->press(this);
}

Block::Block(QDialog *dialog, Game* game, int x, int y):QLabel::QLabel(dialog){
    this->game = game;
    this->x = x;
    this->y = y;
    this->piece = nullptr;
           
}

Block::Block(QDialog *dialog, Game* game, int x, int y, Piece* piece):QLabel::QLabel(dialog){
    this->game = game;
    this->x = x;
    this->y = y;
    this->piece = piece;
           
}

void Block::setPiece(Piece* piece){
    this->piece = piece;
}

Piece* Block::getPiece(){
    return piece;
}

std::vector<int> Block::getCoordinates(){
    std::vector<int> coordinates{x,y};
    return coordinates;
}

std::string Block::getColor(){
    return color;
}

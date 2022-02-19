#include <iostream>
#include "block.h"

void Block::mousePressEvent(QMouseEvent *ev){
    this->game->press(this);
}

Block::Block(QDialog *Dialog, Game* game, int x, int y, Piece* piece=nullptr) : QLabel::QLabel(Dialog){
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

vector<int> Block::getCoordinates(){
    vector<int> coordinates{x,y};
    return coordinates;
}

std::string Block::getColor(){
    return color;
}

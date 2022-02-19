#include <iostream>
#include "block.h"

void Block::mousePressEvent(QMouseEvent *ev) {
    QLabel::mousePressEvent(ev);
}

Block::Block(QDialog *Dialog, Game *game, int x, int y, Piece *piece) {

}

void Block::setPiece(Piece *piece) {

}

Piece *Block::getPiece() {
    return nullptr;
}

std::vector<int> Block::getCoordinates() {
    return std::vector<int>();
}

std::string Block::getColor() {
    return std::string();
}

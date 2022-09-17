/*
tas oraya gidebilir mi?(kale duz gidebilir mi?) -> -1
arada baska tas var mi? -> -2
gitmek istedigi yerde kendi tasi var mi? -> -3
yaptigi hamle kendini mat ediyor mu? -> -4
bulundugu kareye mi gitmeye calisiyor? -> -5
*/

#include <iostream>
#include "game.h"
#include "block.h"
#include "pieces.h"
#include "utils.h"

#define KNIGHT 0
#define BISHOP 1
#define ROOK 2
#define QUEEN 3
#define KING 4
#define PAWN 5

Piece::Piece(std::string color, Block* block, Game* game) {
    this->color = color;
    if(color == "w"){
        this->qcolor = Qt::white;
    }
    else{
        this->qcolor = Qt::black;
    }
    this->block = block;
    this->game = game;
    this->isCaptured = false;
}

void Piece::setBlock(Block *block) {
    this->block = block;
}

Block *Piece::getBlock() {
    return this->block;
}

std::string Piece::getColor() {
    return this->color;
}

QColor Piece::getQColor() {
    return this->qcolor;
}

int Piece::checkMove(Block *target) {
    return checkMove_all(this, target);
}

Game *Piece::getGame() {
    return game;
}

Knight::Knight(std::string color, Block* block, Game* game):Piece::Piece(color, block, game){
    this->path = "../pngs/pieces/at.png";
    this->name = "at";
    this->image = QImage(this->path.c_str()); 
}

Bishop::Bishop(std::string color, Block* block, Game* game):Piece::Piece(color, block, game){
    this->path = "../pngs/pieces/fil.png";
    this->name = "fil";
    this->image = QImage(this->path.c_str()); 
}

Rook::Rook(std::string color, Block* block, Game* game):Piece::Piece(color, block, game){
    this->path = "../pngs/pieces/kale.png";
    this->name = "kale";
    this->image = QImage(this->path.c_str()); 
    this->isMoved = false;
}

Queen::Queen(std::string color, Block* block, Game* game):Piece::Piece(color, block, game){
    this->path = "../pngs/pieces/vezir.png";
    this->name = "vezir";
    this->image = QImage(this->path.c_str()); 
}

King::King(std::string color, Block* block, Game* game):Piece::Piece(color, block, game){
    this->path = "../pngs/pieces/sah.png";
    this->name = "sah";
    this->image = QImage(this->path.c_str()); 
    this->isMoved = false;
}

Pawn::Pawn(std::string color, Block* block, Game* game):Piece::Piece(color, block, game){
    this->path = "../pngs/pieces/piyon.png";
    this->name = "piyon";
    this->image = QImage(this->path.c_str()); 
}
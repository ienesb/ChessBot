/*
tas oraya gidebilir mi?(kale duz gidebilir mi?) -> -1
arada baska tas var mi? -> -2
gitmek istedigi yerde kendi tasi var mi? -> -3
yaptigi hamle kendini mat ediyor mu? -> -4
bulundugu kareye mi gitmeye calisiyor? -> -5
*/

// TODO:
//  consider castling in the future

#include <opencv2/opencv.hpp>
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

int Knight::checkMove(Block* target){
    return checkMove_all(this, target, KNIGHT);
}

int Bishop::checkMove(Block* target){
    return checkMove_all(this, target, BISHOP);
}

int Rook::checkMove(Block* target){
    return checkMove_all(this, target, ROOK);
}

int Queen::checkMove(Block* target){
    return checkMove_all(this, target, QUEEN);
}

int King::checkMove(Block* target){
    return checkMove_all(this, target, KING);
}

int Pawn::checkMove(Block* target){
    return checkMove_all(this, target, PAWN);
}

Piece::Piece(std::string color, Block* block, Game* game) {
    this->color = color;
    this->block = block;
    this->game = game;
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

int Piece::checkMove(Block *target) {
    return 0;
}

Game *Piece::getGame() {
    return game;
}

Knight::Knight(std::string color, Block* block, Game* game):Piece::Piece(color, block, game){
    this->path = "../pngs/pieces/at.png";
    this->name = "at";
    this->image = cv::imread("../pngs/pieces/at.png", 1); 
}

Bishop::Bishop(std::string color, Block* block, Game* game):Piece::Piece(color, block, game){
    this->path = "../pngs/pieces/fil.png";
    this->name = "fil";
    this->image = cv::imread("../pngs/pieces/fil.png", 1);
}

Rook::Rook(std::string color, Block* block, Game* game):Piece::Piece(color, block, game){
    this->path = "../pngs/pieces/kale.png";
    this->name = "kale";
    this->image = cv::imread("../pngs/pieces/kale.png", 1);
}

Queen::Queen(std::string color, Block* block, Game* game):Piece::Piece(color, block, game){
    this->path = "../pngs/pieces/vezir.png";
    this->name = "vezir";
    this->image = cv::imread("../pngs/pieces/vezir.png", 1);
}

King::King(std::string color, Block* block, Game* game):Piece::Piece(color, block, game){
    this->path = "../pngs/pieces/sah.png";
    this->name = "sah";
    this->image = cv::imread("../pngs/pieces/sah.png", 1);

}

Pawn::Pawn(std::string color, Block* block, Game* game):Piece::Piece(color, block, game){
    this->path = "../pngs/pieces/piyon.png";
    this->name = "piyon";
    this->image = cv::imread("../pngs/pieces/piyon.png", 1);
}
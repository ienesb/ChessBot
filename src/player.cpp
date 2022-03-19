#include "player.h"
#include "game.h"

Player::Player(std::string color, Game* game){
    this->color = color;
    this->game = game;
}

std::string Player::getColor(){
    return this->color;
}

Game* Player::getGame(){
    return this->game;
}

void Player::setPiece(Piece* piece){
    pieces.push_back(piece);
}

void Player::removePiece(Piece* piece){
    //remove piece from vector pieces if you want
}

std::vector<Piece *> Player::getPieces() {
    return this->pieces;
}

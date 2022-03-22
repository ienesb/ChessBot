#include "player.h"
#include "game.h"
#include "pieces.h"

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

void Player::printPieces(){
    for(Piece* p: pieces){
        std::cout << p->name << "\n";
    }
}

void Player::updatePieces(){
    std::vector<Piece*>::iterator i = pieces.begin();
    for(Piece* p: pieces){
        if(p->isCaptured){
            pieces.erase(i);
            capturedPieces.push_back(p);
        }
        i++; 
    }
    i = capturedPieces.begin();
    for(Piece* p: capturedPieces){
        if(!p->isCaptured){
            capturedPieces.erase(i);
            pieces.push_back(p);
        }
        i++; 
    }
}
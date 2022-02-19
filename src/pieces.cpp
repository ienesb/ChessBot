/*
taş oraya gidebilir mi?(kale düz gidebilir mi?) -> -1
arada başka taş var mı? -> -2
gitmek istediği yerde kendi taşı var mı? -> -3
yaptığı hamle kendini mat ediyor mu) -> -4
tahtanın dışına mı çıkmaya çalışıyor? -> -5
bulunduğu kareye mi gitmeye çalışıyor? -> -6
*/

/*
at      knight 0
fil     bishop 1
kale    rook 2
vezir   queen 3
sah     king 4
piyon   pawn 5
*/

// TODO: remove return false; from all methods of sub Piece classes

#include <iostream>
#include <vector>

#include "game.h"
#include "block.h"
#include "pieces.h"

#define KNIGHT 0
#define BISHOP 1
#define ROOK 2
#define QUEEN 3
#define KING 4
#define PAWN 5

bool isValid(std::vector<int>current, std::vector<int>target, int piece){
    switch (piece) {
        case KNIGHT:
            break;
        case BISHOP:
            break;
        case ROOK:
            if (current[0] == target[0]) return true;
            else if (current[1] == target[1]) return true;
            else return false;
        case QUEEN:
            break;
        case KING:
            break;
        case PAWN:
            break;
    }
    return false;
};
bool isSame(std::vector<int>current, std::vector<int>target){
    if ((current[0] == target[0]) && (current[1] == target[1])) return true;
    else return false;
}

bool isBlocked(std::vector<int>current, std::vector<int>target, int piece, Game *game) {
    switch (piece) {
        case KNIGHT:
            break;
        case BISHOP:
            break;
        case ROOK: //rook
            if (current[0] == target[0]) {
                if (current[1] < target[1]){
                    for(int i = current[1]+1; i<target[1]; i++){
                        if(game->getBlock(current[0],i)->getPiece()) return true;
                    }
                    return false;
                }
                else if(current[1] > target[1]){
                    for(int i = current[1]-1; i>target[1]; i--){
                        if(game->getBlock(current[0],i)->getPiece()) return true;
                    }
                    return false;
                }
            }
            else if (current[1] == target[1]) {
                if (current[0] < target[0]){
                    for(int i = current[0]+1; i<target[0]; i++){
                        if(game->getBlock(current[1],i)->getPiece()) return true;
                    }
                    return false;
                }
                else if(current[0] > target[0]){
                    for(int i = current[0]-1; i>target[0]; i--){
                        if(game->getBlock(current[1],i)->getPiece()) return true;
                    }
                    return false;
                }
            }
        case QUEEN:
            break;
        case KING:
            break;
        case PAWN:
            break;
    }
    return false;
};

bool isSameColor(std::vector<int>current, std::vector<int>target, Game *game){
    if(game->getBlock(current[0],current[1])->getPiece()->getColor() ==
    game->getBlock(target[0],target[1])->getPiece()->getColor())
        return true;

    else return false;
}

int Knight::checkMove(Block* target){
    auto coordinates(target->getCoordinates());
    return 0;
}

int Bishop::checkMove(Block* target){
    return 0;
}

int Rook::checkMove(Block* target){
    // getting coordinates
    auto currentCoord(getBlock()->getCoordinates());
    auto targetCoord(target->getCoordinates());
    // checking whether the move is valid
    if(!isValid(currentCoord, targetCoord, ROOK)) return -1;
    // checking whether the target position is the same as the current position
    if(isSame(currentCoord, targetCoord)) return -6;
    // checking whether a piece blocks the pathway
    if(isBlocked(currentCoord, targetCoord, ROOK, getGame())) return -2;
    // checking whether the target piece does not have the same color as the current piece.
    if(isSameColor(currentCoord, targetCoord, getGame())) return -3;
    return 0;
}

int Queen::checkMove(Block* target){
    return 0;
}

int King::checkMove(Block* target){
    return 0;
}

int Pawn::checkMove(Block* target){
    return 0;
}

Piece::Piece(std::string color, Block *block, Game* game) {
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
    return std::string();
}

int Piece::checkMove(Block *target) {
    return 0;
}

Game *Piece::getGame() {
    return game;
}

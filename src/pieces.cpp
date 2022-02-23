/*
tas oraya gidebilir mi?(kale duz gidebilir mi?) -> -1
arada baska tas var mi? -> -2
gitmek istedigi yerde kendi tasi var mi? -> -3
yaptigi hamle kendini mat ediyor mu? -> -4
bulundugu kareye mi gitmeye calisiyor? -> -5
*/

/*
at      knight 0
fil     bishop 1
kale    rook 2
vezir   queen 3
sah     king 4
piyon   pawn 5
*/

// TODO:
//  consider castling in the future

#include <opencv2/opencv.hpp>

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

bool isValid(std::vector<int>current, std::vector<int>target, const int piece, Game *game){
    switch (piece) {
        case KNIGHT:
            if ((abs(current[0] - target[0]) == 2) and (abs(current[1] - target[1]) == 1))
                return true;
            else if ((abs(current[0] - target[0]) == 1) and (abs(current[1] - target[1]) == 2))
                return true;
            else return false;
        case BISHOP:
            if (abs(current[0] - target[0]) == abs(current[1] - target[1])) return true;
            else return false;
        case ROOK:
            if ((current[0] == target[0]) or (current[1] == target[1])) return true;
            else return false;
        case QUEEN:
            if (((current[0] == target[0]) or (current[1] == target[1])) or
                    abs(current[0] - target[0]) == abs(current[1] - target[1])) return true;
            else return false;
        case KING:
            if (abs(current[0] - target[0]) == 1 and abs(current[1] - target[1]) == 1) return true;
            else if (((current[0] == target[0]) or (current[1] == target[1])) and
                     (abs(current[0]-target[0]+current[1]-target[1]) == 1)) return true;
            else return false;
        case PAWN:
            // WHITE PAWN
            if (game->getBlock(current[0],current[1])->getPiece()->getColor() == "w"){

                if ((current[0] == target[0]) and (target[1] - current[1] == 1)
                and game->getBlock(target[0], target[1])->getPiece() == nullptr) return true;

                else if (((current[0] == target[0]) and (target[1] - current[1] == 2)) and current[1] == 2)
                    return true;

                else if (((abs(current[0] - target[0]) == 1) and (target[1] - current[1] == 1))
                    and (game->getBlock(target[0], target[1])->getPiece() != nullptr)
                    and (game->getBlock(current[0], current[1])->getPiece()->getColor() !=
                    game->getBlock(target[0], target[1])->getPiece()->getColor())) return true;
                else return false;
            }
                // BLACK PAWN
            else if (game->getBlock(current[0],current[1])->getPiece()->getColor() == "b"){

                if ((current[0] == target[0]) and (target[1] - current[1] == -1)
                and game->getBlock(target[0], target[1])->getPiece() == nullptr) return true;

                else if (((current[0] == target[0]) and (target[1] - current[1] == -2)) and current[1] == 7)
                    return true;
                else if (((abs(current[0] - target[0]) == 1) and (target[1] - current[1] == -1))
                    and (game->getBlock(target[0], target[1])->getPiece() != nullptr)
                    and (game->getBlock(current[0], current[1])->getPiece()->getColor() !=
                    game->getBlock(target[0], target[1])->getPiece()->getColor())) return true;
                else return false;
            }
    }
}
bool isSame(std::vector<int>current, std::vector<int>target){
    if ((current[0] == target[0]) && (current[1] == target[1])) return true;
    else return false;
}

bool checkXY(int x, int y){
    if(x >= 1 and y >= 1 and x < 9 and y < 9)
        return true;
    return false;
}

bool isBlocked(std::vector<int>current, std::vector<int>target, const int piece, Game *game) {
    switch (piece) {
        case KNIGHT:
            return false;
        case BISHOP: {
            int x = current[0], y = current[1];
            // FORWARD, RIGHT
            if (current[0] < target[0] and current[1] < target[1]) {
                x++;
                y++;
                while (x != target[0] and y != target[1]){
                    if (checkXY(x, y) and game->getBlock(x, y)->getPiece()) return true;
                    x++;
                    y++;
                }
                return false;
            }
                // DOWNWARD, RIGHT
            else if (current[0] < target[0] and current[1] > target[1]) {
                x++;
                y--;
                while (x != target[0] and y != target[1]){
                    if (checkXY(x, y) and game->getBlock(x, y)->getPiece()) return true;
                    x++;
                    y--;
                }
                return false;
            }
                // FORWARD, LEFT
            else if (current[0] > target[0] and current[1] < target[1]) {
                x--;
                y++;
                while (x != target[0] and y != target[1]){
                    if (checkXY(x, y) and game->getBlock(x, y)->getPiece()) return true;
                    x--;
                    y++;
                }
                return false;
            }
                // DOWNWARD, LEFT
            else if (current[0] > target[0] and current[1] > target[1]) {
                x--;
                y--;
                while (x != target[0] and y != target[1]){
                    if (checkXY(x, y) and game->getBlock(x, y)->getPiece()) return true;
                    x--;
                    y--;
                }
                return false;
            }
        }
        case ROOK:
            // MOVEMENT IN Y AXIS
            if (current[0] == target[0]) {
                // FORWARD
                if (current[1] < target[1]){
                    for (int i = current[1]+1; i<target[1]; i++){
                        if (game->getBlock(current[0],i)->getPiece()) return true;
                    }
                    return false;
                }
                    // DOWNWARD
                else if (current[1] > target[1]){
                    for (int i = current[1]-1; i>target[1]; i--){
                        if (game->getBlock(current[0],i)->getPiece()) return true;
                    }
                    return false;
                }
            }
                // MOVEMENT IN X AXIS
            else if (current[1] == target[1]) {
                // RIGHT
                if (current[0] < target[0]){
                    for (int i = current[0]+1; i<target[0]; i++){
                        if (game->getBlock(i,current[1])->getPiece()) return true;
                    }
                    return false;
                }
                    // LEFT
                else if (current[0] > target[0]){
                    for (int i = current[0]-1; i>target[0]; i--){
                        if (game->getBlock(i,current[1])->getPiece()) return true;
                    }
                    return false;
                }
            }
        case QUEEN:
            // IF THE MOVEMENT IS OF ROOK
            if ((current[0] == target[0]) or (current[1] == target[1])){
                if (current[0] == target[0]) {
                    // FORWARD
                    if (current[1] < target[1]){
                        for (int i = current[1]+1; i<target[1]; i++){
                            if (game->getBlock(current[0],i)->getPiece()) return true;
                        }
                        return false;
                    }
                        // DOWNWARD
                    else if (current[1] > target[1]){
                        for (int i = current[1]-1; i>target[1]; i--){
                            if (game->getBlock(current[0],i)->getPiece()) return true;
                        }
                        return false;
                    }
                }
                    // MOVEMENT IN X AXIS
                else if (current[1] == target[1]) {
                    // RIGHT
                    if (current[0] < target[0]){
                        for (int i = current[0]+1; i<target[0]; i++){
                            if (game->getBlock(i,current[1])->getPiece()) return true;
                        }
                        return false;
                    }
                        // LEFT
                    else if (current[0] > target[0]){
                        for (int i = current[0]-1; i>target[0]; i--){
                            if (game->getBlock(i,current[1])->getPiece()) return true;
                        }
                        return false;
                    }
                }
            }
                // IF THE MOVEMENT IS OF BISHOP
            else if (abs(current[0] - target[0]) == abs(current[1] - target[1])){
                int x = current[0], y = current[1];
                // FORWARD, RIGHT
                if (current[0] < target[0] and current[1] < target[1]) {
                    x++;
                    y++;
                    while (x != target[0] and y != target[1]){
                        if (checkXY(x, y) and game->getBlock(x, y)->getPiece()) return true;
                        x++;
                        y++;
                    }
                    return false;
                }
                    // DOWNWARD, RIGHT
                else if (current[0] < target[0] and current[1] > target[1]) {
                    x++;
                    y--;
                    while (x != target[0] and y != target[1]){
                        if (checkXY(x, y) and game->getBlock(x, y)->getPiece()) return true;
                        x++;
                        y--;
                    }
                    return false;
                }
                    // FORWARD, LEFT
                else if (current[0] > target[0] and current[1] < target[1]) {
                    x--;
                    y++;
                    while (x != target[0] and y != target[1]){
                        if (checkXY(x, y) and game->getBlock(x, y)->getPiece()) return true;
                        x--;
                        y++;
                    }
                    return false;
                }
                    // DOWNWARD, LEFT
                else if (current[0] > target[0] and current[1] > target[1]) {
                    x--;
                    y--;
                    while (x != target[0] and y != target[1]){
                        if (checkXY(x, y) and game->getBlock(x, y)->getPiece()) return true;
                        x--;
                        y--;
                    }
                    return false;
                }
            }
        case KING:
            return false;
        case PAWN:
            if (game->getBlock(current[0],current[1])->getPiece()->getColor() == "w"){
                if (((current[0] == target[0]) and (target[1] - current[1] == 2)) and current[1] == 2)
                    if(game->getBlock(current[0], current[1]+1)->getPiece()) return true;
                return false;
            }
            else if (game->getBlock(current[0],current[1])->getPiece()->getColor() == "b")
                if (((current[0] == target[0]) and (target[1] - current[1] == -2)) and current[1] == 7)
                    if(game->getBlock(current[0], current[1]-1)->getPiece()) return true;
                return false;
    }

}

bool isSameColor(std::vector<int>current, std::vector<int>target, Game *game){
    if(game->getBlock(target[0],target[1])->getPiece() != nullptr){
        if(game->getBlock(current[0],current[1])->getPiece()->getColor() ==
           game->getBlock(target[0],target[1])->getPiece()->getColor())
            return true;
    }
    return false;
}

// It is for examining the check situation after movement.
Piece* tempGetPiece(int x, int y, std::vector<int>current, std::vector<int>target, Piece* currentPiece, Game* game){
    if(x == current[0] and y == current[1]){
        return nullptr;
    }
    else if(x == target[0] and y == target[1]){
        return currentPiece;
    }
    return game->getBlock(x,y)->getPiece();
}

bool isCheck(std::vector<int>current, std::vector<int>target, Game *game){
    auto king = game->getKing(game->getBlock(current[0],current[1])->getPiece()->getColor());
    auto kingCoord(king->getBlock()->getCoordinates());
    auto kingColor = king->getColor();
    auto currentPiece = game->getBlock(current[0],current[1])->getPiece();

    // Checking if the piece that moves is the king
    if(game->getBlock(current[0],current[1])->getPiece()->name == "sah")
        kingCoord = target;

    int x = kingCoord[0], y = kingCoord[1];
    // FORWARD
    y++;
    for (; y<=8; y++){
        if (checkXY(x, y) and tempGetPiece(x, y, current, target, currentPiece, game)) {
            if (typeid(tempGetPiece(x, y, current, target, currentPiece, game)).name() == typeid(Rook).name()
                and kingColor != tempGetPiece(x, y, current, target, currentPiece, game)->getColor())
                return true;
            else if (typeid(tempGetPiece(x, y, current, target, currentPiece, game)).name() == typeid(Queen).name()
                     and kingColor != tempGetPiece(x, y, current, target, currentPiece, game)->getColor())
                return true;
            break;
        }
    }
    y = kingCoord[1];
    // DOWNWARD
    y--;
    for (; y>=1; y--) {
        if (checkXY(x, y) and tempGetPiece(x, y, current, target, currentPiece, game)) {
            if (typeid(tempGetPiece(x, y, current, target, currentPiece, game)).name() == typeid(Rook).name()
                and kingColor != tempGetPiece(x, y, current, target, currentPiece, game)->getColor())
                return true;
            else if (typeid(tempGetPiece(x, y, current, target, currentPiece, game)).name() == typeid(Queen).name()
                     and kingColor != tempGetPiece(x, y, current, target, currentPiece, game)->getColor())
                return true;
            break;
        }
    }
    y = kingCoord[1];
    // RIGHT
    x++;
    for (; x<=8; x++){
        if (checkXY(x, y) and tempGetPiece(x, y, current, target, currentPiece, game)) {
            if (typeid(tempGetPiece(x, y, current, target, currentPiece, game)).name() == typeid(Rook).name()
                and kingColor != tempGetPiece(x, y, current, target, currentPiece, game)->getColor())
                return true;
            else if (typeid(tempGetPiece(x, y, current, target, currentPiece, game)).name() == typeid(Queen).name()
                     and kingColor != tempGetPiece(x, y, current, target, currentPiece, game)->getColor())
                return true;
            break;
        }
    }
    x = kingCoord[0];
    // LEFT
    x--;
    for (; x>=1; x--){
        if (checkXY(x, y) and tempGetPiece(x, y, current, target, currentPiece, game)) {
            if (typeid(tempGetPiece(x, y, current, target, currentPiece, game)).name() == typeid(Rook).name()
                and kingColor != tempGetPiece(x, y, current, target, currentPiece, game)->getColor())
                return true;
            else if (typeid(tempGetPiece(x, y, current, target, currentPiece, game)).name() == typeid(Queen).name()
                     and kingColor != tempGetPiece(x, y, current, target, currentPiece, game)->getColor())
                return true;
            break;
        }
    }
    x = kingCoord[0];
    y = kingCoord[1];
    // FORWARD, RIGHT
    x++;
    y++;
    if (checkXY(x, y) and tempGetPiece(x, y, current, target, currentPiece, game)){
        if (typeid(tempGetPiece(x, y, current, target, currentPiece, game)).name() == typeid(Pawn).name()
            and kingColor != tempGetPiece(x, y, current, target, currentPiece, game)->getColor()){
            return true;
        }
    }
    x = kingCoord[0];
    y = kingCoord[1];
    while (x != 9 and y != 9) {
        x++;
        y++;
        if (checkXY(x, y) and tempGetPiece(x, y, current, target, currentPiece, game)) {
            if (tempGetPiece(x, y, current, target, currentPiece, game)->name == "fil"
                and kingColor != tempGetPiece(x, y, current, target, currentPiece, game)->getColor())
                return true;
//            auto idk = tempGetPiece(x, y, current, target, currentPiece, game);
//            std::cout << "queen? = " << typeid(tempGetPiece(x, y, current, target, currentPiece, game)).name() << typeid(Queen).name() << "\n";
//            std::cout << "not same color? = " << kingColor << tempGetPiece(x, y, current, target, currentPiece, game)->getColor() << "\n";
            if (tempGetPiece(x, y, current, target, currentPiece, game)->name == "vezir"
                     and kingColor != tempGetPiece(x, y, current, target, currentPiece, game)->getColor())
                return true;
            break;
        }
    }
    x = kingCoord[0];
    y = kingCoord[1];
    // FORWARD, LEFT
    x--;
    y++;
    if (checkXY(x, y) and tempGetPiece(x, y, current, target, currentPiece, game)){
        if (tempGetPiece(x, y, current, target, currentPiece, game)->name == "piyon"
            and kingColor != tempGetPiece(x, y, current, target, currentPiece, game)->getColor()){
            return true;
        }
    }
    x = kingCoord[0];
    y = kingCoord[1];
    while (x != 0 and y != 9) {
        x--;
        y++;
        if (checkXY(x, y) and tempGetPiece(x, y, current, target, currentPiece, game)) {
            if (tempGetPiece(x, y, current, target, currentPiece, game)->name == "fil"
                and kingColor != tempGetPiece(x, y, current, target, currentPiece, game)->getColor())
                return true;
            else if (tempGetPiece(x, y, current, target, currentPiece, game)->name == "vezir"
                     and kingColor != tempGetPiece(x, y, current, target, currentPiece, game)->getColor())
                return true;
            break;
        }
    }
    x = kingCoord[0];
    y = kingCoord[1];
    // DOWNWARD, RIGHT
    x++;
    y--;
    if (checkXY(x, y) and tempGetPiece(x, y, current, target, currentPiece, game)){
        if (tempGetPiece(x, y, current, target, currentPiece, game)->name == "piyon"
            and kingColor != tempGetPiece(x, y, current, target, currentPiece, game)->getColor()){
            return true;
        }
    }
    x = kingCoord[0];
    y = kingCoord[1];
    while (x != 9 and y != 0) {
        x++;
        y--;
        if (checkXY(x, y) and tempGetPiece(x, y, current, target, currentPiece, game)) {
            if (tempGetPiece(x, y, current, target, currentPiece, game)->name == "fil"
                and kingColor != tempGetPiece(x, y, current, target, currentPiece, game)->getColor())
                return true;
            else if (tempGetPiece(x, y, current, target, currentPiece, game)->name == "vezir"
                     and kingColor != tempGetPiece(x, y, current, target, currentPiece, game)->getColor())
                return true;
            break;
        }
    }
    x = kingCoord[0];
    y = kingCoord[1];
    // DOWNWARD, LEFT
    x--;
    y--;
    if (checkXY(x, y) and tempGetPiece(x, y, current, target, currentPiece, game)){
        if (tempGetPiece(x, y, current, target, currentPiece, game)->name == "piyon"
            and kingColor != tempGetPiece(x, y, current, target, currentPiece, game)->getColor()){
            return true;
        }
    }
    x = kingCoord[0];
    y = kingCoord[1];
    while (x != 0 and y != 0) {
        x--;
        y--;
        if (checkXY(x, y) and tempGetPiece(x, y, current, target, currentPiece, game)) {
            if (tempGetPiece(x, y, current, target, currentPiece, game)->name == "fil"
                and kingColor != tempGetPiece(x, y, current, target, currentPiece, game)->getColor())
                return true;
            else if (tempGetPiece(x, y, current, target, currentPiece, game)->name == "vezir"
                     and kingColor != tempGetPiece(x, y, current, target, currentPiece, game)->getColor())
                return true;
            break;
        }
    }
    x = kingCoord[0];
    y = kingCoord[1];

    int x_move, y_move;

    // 1 FORWARD, 2 RIGHT
    x_move = 2;
    y_move = 1;

    if (checkXY(x+x_move, y+y_move) and tempGetPiece(x+x_move, y+y_move, current, target, currentPiece, game)) {
        if (tempGetPiece(x+x_move, y+y_move, current, target, currentPiece, game)->name == "at"
            and kingColor != tempGetPiece(x+x_move, y+y_move, current, target, currentPiece, game)->getColor())
            return true;
    }
    // 1 FORWARD, 2 LEFT
    x_move = -2;
    y_move = 1;
    if (checkXY(x+x_move, y+y_move) and tempGetPiece(x+x_move, y+y_move, current, target, currentPiece, game)) {
        if (tempGetPiece(x+x_move, y+y_move, current, target, currentPiece, game)->name == "at"
            and kingColor != tempGetPiece(x+x_move, y+y_move, current, target, currentPiece, game)->getColor())
            return true;
    }
    // 1 DOWNWARD, 2 RIGHT
    x_move = 2;
    y_move = -1;
    if (checkXY(x+x_move, y+y_move) and tempGetPiece(x+x_move, y+y_move, current, target, currentPiece, game)) {
        if (tempGetPiece(x+x_move, y+y_move, current, target, currentPiece, game)->name == "at"
            and kingColor != tempGetPiece(x+x_move, y+y_move, current, target, currentPiece, game)->getColor())
            return true;
    }
    // 1 DOWNWARD, 2 LEFT
    x_move = -2;
    y_move = -1;
    if (checkXY(x+x_move, y+y_move) and tempGetPiece(x+x_move, y+y_move, current, target, currentPiece, game)) {
        if (tempGetPiece(x+x_move, y+y_move, current, target, currentPiece, game)->name == "at"
            and kingColor != tempGetPiece(x+x_move, y+y_move, current, target, currentPiece, game)->getColor())
            return true;
    }
    // 2 FORWARD, 1 RIGHT
    x_move = 1;
    y_move = 2;
    if (checkXY(x+x_move, y+y_move) and tempGetPiece(x+x_move, y+y_move, current, target, currentPiece, game)) {
        if (tempGetPiece(x+x_move, y+y_move, current, target, currentPiece, game)->name == "at"
            and kingColor != tempGetPiece(x+x_move, y+y_move, current, target, currentPiece, game)->getColor())
            return true;
    }
    // 2 FORWARD, 1 LEFT
    x_move = -1;
    y_move = 2;
    if (checkXY(x+x_move, y+y_move) and tempGetPiece(x+x_move, y+y_move, current, target, currentPiece, game)) {
        if (tempGetPiece(x+x_move, y+y_move, current, target, currentPiece, game)->name == "at"
            and kingColor != tempGetPiece(x+x_move, y+y_move, current, target, currentPiece, game)->getColor())
            return true;
    }
    // 2 DOWNWARD, 1 RIGHT
    x_move = 1;
    y_move = -2;
    if (checkXY(x+x_move, y+y_move) and tempGetPiece(x+x_move, y+y_move, current, target, currentPiece, game)) {
        if (tempGetPiece(x+x_move, y+y_move, current, target, currentPiece, game)->name == "at"
            and kingColor != tempGetPiece(x+x_move, y+y_move, current, target, currentPiece, game)->getColor())
            return true;
    }
    // 2 DOWNWARD, 1 LEFT
    x_move = -1;
    y_move = -2;
    if (checkXY(x+x_move, y+y_move) and tempGetPiece(x+x_move, y+y_move, current, target, currentPiece, game)) {
        if (tempGetPiece(x+x_move, y+y_move, current, target, currentPiece, game)->name == "at"
            and kingColor != tempGetPiece(x+x_move, y+y_move, current, target, currentPiece, game)->getColor())
            return true;
    }
    return false;
}

int checkMove_all(Piece* piece,Block* target, const int identifier){
    // getting coordinates
    auto currentCoord(piece->getBlock()->getCoordinates());
    auto targetCoord(target->getCoordinates());
    // checking whether the move is valid
    if(!isValid(currentCoord, targetCoord, identifier, piece->getGame())) return -1;
    // checking whether the target position is the same as the current position
    if(isSame(currentCoord, targetCoord)) return -5;
    // checking whether the target piece does not have the same kingColor as the current piece.
    if(isSameColor(currentCoord, targetCoord, piece->getGame())) return -3;
    // checking whether a piece blocks the pathway
    if(isBlocked(currentCoord, targetCoord, identifier, piece->getGame())) return -2;
    // checking whether the movement causes check
    if(isCheck(currentCoord, targetCoord, piece->getGame())) return -4;
    return 0;
}

int Knight::checkMove(Block* target){
    // unique number to identify piece
    const int identifier = KNIGHT;
    return checkMove_all(this, target, identifier);
}

int Bishop::checkMove(Block* target){
    // unique number to identify piece
    const int identifier = BISHOP;
    return checkMove_all(this, target, identifier);
}

int Rook::checkMove(Block* target){
    // unique number to identify piece
    const int identifier = ROOK;
    return checkMove_all(this, target, identifier);
}

int Queen::checkMove(Block* target){
    // unique number to identify piece
    const int identifier = QUEEN;
    return checkMove_all(this, target, identifier);
}

int King::checkMove(Block* target){
    // unique number to identify piece
    const int identifier = KING;
    return checkMove_all(this, target, identifier);
}

int Pawn::checkMove(Block* target){
    // unique number to identify piece
    const int identifier = PAWN;
    return checkMove_all(this, target, identifier);
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
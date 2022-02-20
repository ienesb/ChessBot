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
            if (current[0] - target[0] == current[1] - target[1]) return true;
            else return false;
        case ROOK:
            if ((current[0] == target[0]) or (current[1] == target[1])) return true;
            else return false;
        case QUEEN:
            if (((current[0] == target[0]) or (current[1] == target[1])) or
                (current[0] - target[0] == current[1] - target[1])) return true;
            else return false;
        case KING:
            if (((abs(current[0] - target[0]) == 1) and (abs(current[1] - target[1]) == 1))
                and (current[0] - target[0] == current[1] - target[1])) return true;
            else if (((current[0] == target[0]) or (current[1] == target[1])) and
                     (abs(current[0]-target[0]+current[1]-target[1]) == 1)) return true;
            else return false;
        case PAWN:
            // WHITE PAWN
            if (game->getBlock(current[0],current[1])->getPiece()->getColor() == "w"){
                if ((current[0] == target[0]) and (target[1] - current[1] == 1)) return true;
                else if (((current[0] == target[0]) and (target[1] - current[1] == 2)) and current[1] == 2)
                    return true;
                else if (((abs(current[0] - target[0]) == 1) and (target[1] - current[1] == 1))
                         and (game->getBlock(current[0], current[1])->getPiece()->getColor() !=
                              game->getBlock(target[0], target[1])->getPiece()->getColor())) return true;
                else return false;
            }
                // BLACK PAWN
            else if (game->getBlock(current[0],current[1])->getPiece()->getColor() == "b"){
                if ((current[0] == target[0]) and (target[1] - current[1] == -1)) return true;
                else if (((current[0] == target[0]) and (target[1] - current[1] == -2)) and current[1] == 7)
                    return true;
                else if (((abs(current[0] - target[0]) == 1) and (target[1] - current[1] == -1))
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

bool isBlocked(std::vector<int>current, std::vector<int>target, const int piece, Game *game) {
    switch (piece) {
        case KNIGHT:
            return false;
        case BISHOP: {
            int x = current[0], y = current[1];
            // FORWARD, RIGHT
            if (current[0] < target[0] and current[1] < target[1]) {
                do {
                    x++;
                    y++;
                    if (game->getBlock(x, y)->getPiece()) return true;
                }while (x != target[0] and y != target[1]);
                return false;
            }
                // DOWNWARD, RIGHT
            else if (current[0] < target[0] and current[1] > target[1]) {
                do {
                    x++;
                    y--;
                    if (game->getBlock(x, y)->getPiece()) return true;
                }while (x != target[0] and y != target[1]);
                return false;
            }
                // FORWARD, LEFT
            else if (current[0] > target[0] and current[1] < target[1]) {
                do {
                    x--;
                    y++;
                    if (game->getBlock(x, y)->getPiece()) return true;
                }while (x != target[0] and y != target[1]);
                return false;
            }
                // DOWNWARD, LEFT
            else if (current[0] > target[0] and current[1] > target[1]) {
                do {
                    x--;
                    y--;
                    if (game->getBlock(x, y)->getPiece()) return true;
                }while (x != target[0] and y != target[1]);
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
                        if (game->getBlock(current[1],i)->getPiece()) return true;
                    }
                    return false;
                }
                    // LEFT
                else if (current[0] > target[0]){
                    for (int i = current[0]-1; i>target[0]; i--){
                        if (game->getBlock(current[1],i)->getPiece()) return true;
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
                            if (game->getBlock(current[1],i)->getPiece()) return true;
                        }
                        return false;
                    }
                        // LEFT
                    else if (current[0] > target[0]){
                        for (int i = current[0]-1; i>target[0]; i--){
                            if (game->getBlock(current[1],i)->getPiece()) return true;
                        }
                        return false;
                    }
                }
            }
                // IF THE MOVEMENT IS OF BISHOP
            else if (current[0] - target[0] == current[1] - target[1]){
                int x = current[0], y = current[1];
                // FORWARD, RIGHT
                if (current[0] < target[0] and current[1] < target[1]) {
                    do {
                        x++;
                        y++;
                        if (game->getBlock(x, y)->getPiece()) return true;
                    }while (x != target[0] and y != target[1]);
                    return false;
                }
                    // DOWNWARD, RIGHT
                else if (current[0] < target[0] and current[1] > target[1]) {
                    do {
                        x++;
                        y--;
                        if (game->getBlock(x, y)->getPiece()) return true;
                    }while (x != target[0] and y != target[1]);
                    return false;
                }
                    // FORWARD, LEFT
                else if (current[0] > target[0] and current[1] < target[1]) {
                    do {
                        x--;
                        y++;
                        if (game->getBlock(x, y)->getPiece()) return true;
                    }while (x != target[0] and y != target[1]);
                    return false;
                }
                    // DOWNWARD, LEFT
                else if (current[0] > target[0] and current[1] > target[1]) {
                    do {
                        x--;
                        y--;
                        if (game->getBlock(x, y)->getPiece()) return true;
                    }while (x != target[0] and y != target[1]);
                    return false;
                }
            }
        case KING:
            return false;
        case PAWN:
            if (game->getBlock(current[0],current[1])->getPiece()->getColor() == "w"){
                if (((current[0] == target[0]) and (target[1] - current[1] == 2)) and current[1] == 1)
                    if(game->getBlock(current[0], current[1]+1)->getPiece()) return true;
                return false;
            }
            else if (game->getBlock(current[0],current[1])->getPiece()->getColor() == "b")
                if (((current[0] == target[0]) and (target[1] - current[1] == -2)) and current[1] == 7)
                    if(game->getBlock(current[0], current[1]+1)->getPiece()) return true;
            return false;
    }

}

bool isSameColor(std::vector<int>current, std::vector<int>target, Game *game){
    if(game->getBlock(current[0],current[1])->getPiece()->getColor() ==
       game->getBlock(target[0],target[1])->getPiece()->getColor())
        return true;
    else return false;
}

bool isCheck(std::vector<int>current, std::vector<int>target, Game *game){
    auto king = game->getKing(game->getBlock(current[0],current[1])->getPiece()->getColor());
    auto kingCoord(king->getBlock()->getCoordinates());
    auto kingColor = king->getColor();
    int x = kingCoord[0], y = kingCoord[1];
    bool temp = true;
    // FORWARD
    y++;
    for (; y<=8; y++){
        if (game->getBlock(x,y)->getPiece()) {
            if (typeid(game->getBlock(x, y)->getPiece()).name() == typeid(Rook).name()
                and kingColor != game->getBlock(x, y)->getPiece()->getColor())
                return true;
            else if (typeid(game->getBlock(x, y)->getPiece()).name() == typeid(Queen).name()
                     and kingColor != game->getBlock(x, y)->getPiece()->getColor())
                return true;
            break;
        }
    }
    y = kingCoord[1];
    // DOWNWARD
    y--;
    for (; y>=1; y--) {
        if (game->getBlock(x, y)->getPiece()) {
            if (typeid(game->getBlock(x, y)->getPiece()).name() == typeid(Rook).name()
                and kingColor != game->getBlock(x, y)->getPiece()->getColor())
                return true;
            else if (typeid(game->getBlock(x, y)->getPiece()).name() == typeid(Queen).name()
                     and kingColor != game->getBlock(x, y)->getPiece()->getColor())
                return true;
            break;
        }
    }
    y = kingCoord[1];
    // RIGHT
    x++;
    for (; x<=8; x++){
        if (game->getBlock(x, y)->getPiece()) {
            if (typeid(game->getBlock(x, y)->getPiece()).name() == typeid(Rook).name()
                and kingColor != game->getBlock(x, y)->getPiece()->getColor())
                return true;
            else if (typeid(game->getBlock(x, y)->getPiece()).name() == typeid(Queen).name()
                     and kingColor != game->getBlock(x, y)->getPiece()->getColor())
                return true;
            break;
        }
    }
    x = kingCoord[0];
    // LEFT
    x--;
    for (; x>=1; x--){
        if (game->getBlock(x, y)->getPiece()) {
            if (typeid(game->getBlock(x, y)->getPiece()).name() == typeid(Rook).name()
                and kingColor != game->getBlock(x, y)->getPiece()->getColor())
                return true;
            else if (typeid(game->getBlock(x, y)->getPiece()).name() == typeid(Queen).name()
                     and kingColor != game->getBlock(x, y)->getPiece()->getColor())
                return true;
            break;
        }
    }
    x = kingCoord[0];
    // FORWARD, RIGHT
    x++;
    y++;
    if (game->getBlock(x, y)->getPiece()){
        if (typeid(game->getBlock(x, y)->getPiece()).name() == typeid(Pawn).name()
            and kingColor != game->getBlock(x, y)->getPiece()->getColor()){
            return true;
        }
    }
    while (x != 9 and y != 9) {
        x++;
        y++;
        if (game->getBlock(x, y)->getPiece()) {
            if (typeid(game->getBlock(x, y)->getPiece()).name() == typeid(Bishop).name()
                and kingColor != game->getBlock(x, y)->getPiece()->getColor())
                return true;
            else if (typeid(game->getBlock(x, y)->getPiece()).name() == typeid(Queen).name()
                     and kingColor != game->getBlock(x, y)->getPiece()->getColor())
                return true;
            break;
        }
    }
    x = kingCoord[0];
    y = kingCoord[1];
    // FORWARD, LEFT
    x--;
    y++;
    if (game->getBlock(x, y)->getPiece()){
        if (typeid(game->getBlock(x, y)->getPiece()).name() == typeid(Pawn).name()
            and kingColor != game->getBlock(x, y)->getPiece()->getColor()){
            return true;
        }
    }
    while (x != 0 and y != 9) {
        x--;
        y++;
        if (game->getBlock(x, y)->getPiece()) {
            if (typeid(game->getBlock(x, y)->getPiece()).name() == typeid(Bishop).name()
                and kingColor != game->getBlock(x, y)->getPiece()->getColor())
                return true;
            else if (typeid(game->getBlock(x, y)->getPiece()).name() == typeid(Queen).name()
                     and kingColor != game->getBlock(x, y)->getPiece()->getColor())
                return true;
            break;
        }
    }
    x = kingCoord[0];
    y = kingCoord[1];
    // DOWNWARD, RIGHT
    x++;
    y--;
    if (game->getBlock(x, y)->getPiece()){
        if (typeid(game->getBlock(x, y)->getPiece()).name() == typeid(Pawn).name()
            and kingColor != game->getBlock(x, y)->getPiece()->getColor()){
            return true;
        }
    }
    while (x != 9 and y != 0) {
        x++;
        y--;
        if (game->getBlock(x, y)->getPiece()) {
            if (typeid(game->getBlock(x, y)->getPiece()).name() == typeid(Bishop).name()
                and kingColor != game->getBlock(x, y)->getPiece()->getColor())
                return true;
            else if (typeid(game->getBlock(x, y)->getPiece()).name() == typeid(Queen).name()
                     and kingColor != game->getBlock(x, y)->getPiece()->getColor())
                return true;
            break;
        }
    }
    x = kingCoord[0];
    y = kingCoord[1];
    // DOWNWARD, LEFT
    x--;
    y--;
    if (game->getBlock(x, y)->getPiece()){
        if (typeid(game->getBlock(x, y)->getPiece()).name() == typeid(Pawn).name()
            and kingColor != game->getBlock(x, y)->getPiece()->getColor()){
            return true;
        }
    }
    while (x != 0 and y != 0) {
        x--;
        y--;
        if (game->getBlock(x, y)->getPiece()) {
            if (typeid(game->getBlock(x, y)->getPiece()).name() == typeid(Bishop).name()
                and kingColor != game->getBlock(x, y)->getPiece()->getColor())
                return true;
            else if (typeid(game->getBlock(x, y)->getPiece()).name() == typeid(Queen).name()
                     and kingColor != game->getBlock(x, y)->getPiece()->getColor())
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
    if (game->getBlock(x+x_move, y+y_move)->getPiece()) {
        if (typeid(game->getBlock(x+x_move, x+x_move)->getPiece()).name() == typeid(Knight).name()
            and kingColor != game->getBlock(x, y)->getPiece()->getColor())
            return true;
    }
    // 1 FORWARD, 2 LEFT
    x_move = -2;
    y_move = 1;
    if (game->getBlock(x+x_move, y+y_move)->getPiece()) {
        if (typeid(game->getBlock(x+x_move, x+x_move)->getPiece()).name() == typeid(Knight).name()
            and kingColor != game->getBlock(x, y)->getPiece()->getColor())
            return true;
    }
    // 1 DOWNWARD, 2 RIGHT
    x_move = 2;
    y_move = -1;
    if (game->getBlock(x+x_move, y+y_move)->getPiece()) {
        if (typeid(game->getBlock(x+x_move, x+x_move)->getPiece()).name() == typeid(Knight).name()
            and kingColor != game->getBlock(x, y)->getPiece()->getColor())
            return true;
    }
    // 1 DOWNWARD, 2 LEFT
    x_move = -2;
    y_move = -1;
    if (game->getBlock(x+x_move, y+y_move)->getPiece()) {
        if (typeid(game->getBlock(x+x_move, x+x_move)->getPiece()).name() == typeid(Knight).name()
            and kingColor != game->getBlock(x, y)->getPiece()->getColor())
            return true;
    }
    // 2 FORWARD, 1 RIGHT
    x_move = 1;
    y_move = 2;
    if (game->getBlock(x+x_move, y+y_move)->getPiece()) {
        if (typeid(game->getBlock(x+x_move, x+x_move)->getPiece()).name() == typeid(Knight).name()
            and kingColor != game->getBlock(x, y)->getPiece()->getColor())
            return true;
    }
    // 2 FORWARD, 1 LEFT
    x_move = -1;
    y_move = 2;
    if (game->getBlock(x+x_move, y+y_move)->getPiece()) {
        if (typeid(game->getBlock(x+x_move, x+x_move)->getPiece()).name() == typeid(Knight).name()
            and kingColor != game->getBlock(x, y)->getPiece()->getColor())
            return true;
    }
    // 2 DOWNWARD, 1 RIGHT
    x_move = 1;
    y_move = -2;
    if (game->getBlock(x+x_move, y+y_move)->getPiece()) {
        if (typeid(game->getBlock(x+x_move, x+x_move)->getPiece()).name() == typeid(Knight).name()
            and kingColor != game->getBlock(x, y)->getPiece()->getColor())
            return true;
    }
    // 2 DOWNWARD, 1 LEFT
    x_move = -1;
    y_move = -2;
    if (game->getBlock(x+x_move, y+y_move)->getPiece()) {
        if (typeid(game->getBlock(x+x_move, x+x_move)->getPiece()).name() == typeid(Knight).name()
            and kingColor != game->getBlock(x, y)->getPiece()->getColor())
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
    checkMove_all(this, target, identifier);
    return 0;
}

int Bishop::checkMove(Block* target){
    // unique number to identify piece
    const int identifier = BISHOP;
    checkMove_all(this, target, identifier);
    return 0;
}

int Rook::checkMove(Block* target){
    // unique number to identify piece
    const int identifier = ROOK;
    checkMove_all(this, target, identifier);
    return 0;
}

int Queen::checkMove(Block* target){
    // unique number to identify piece
    const int identifier = QUEEN;
    checkMove_all(this, target, identifier);
    return 0;
}

int King::checkMove(Block* target){
    // unique number to identify piece
    const int identifier = KING;
    checkMove_all(this, target, identifier);
    return 0;
}

int Pawn::checkMove(Block* target){
    // unique number to identify piece
    const int identifier = PAWN;
    checkMove_all(this, target, identifier);
    return 0;
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
}

Bishop::Bishop(std::string color, Block* block, Game* game):Piece::Piece(color, block, game){
    this->path = "../pngs/pieces/fil.png";
}

Rook::Rook(std::string color, Block* block, Game* game):Piece::Piece(color, block, game){
    this->path = "../pngs/pieces/kale.png";
}

Queen::Queen(std::string color, Block* block, Game* game):Piece::Piece(color, block, game){
    this->path = "../pngs/pieces/vezir.png";
}

King::King(std::string color, Block* block, Game* game):Piece::Piece(color, block, game){
    this->path = "../pngs/pieces/sah.png";
}

Pawn::Pawn(std::string color, Block* block, Game* game):Piece::Piece(color, block, game){
    this->path = "../pngs/pieces/piyon.png";
}
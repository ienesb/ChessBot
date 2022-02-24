#include "utils.h"

#define KNIGHT 0
#define BISHOP 1
#define ROOK 2
#define QUEEN 3
#define KING 4
#define PAWN 5

static bool checkXY(int x, int y){
    if(x >= 1 and y >= 1 and x < 9 and y < 9)
        return true;
    return false;
}

// It is for examining the check situation after movement.
static Piece* tempGetPiece(int x, int y, std::vector<int>current, std::vector<int>target, Piece* currentPiece, Game* game){
    if(x == current[0] and y == current[1]){
        return nullptr;
    }
    else if(x == target[0] and y == target[1]){
        return currentPiece;
    }
    return game->getBlock(x,y)->getPiece();
}

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

bool isBlocked(std::vector<int>current, std::vector<int>target, const int piece, Game *game){
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
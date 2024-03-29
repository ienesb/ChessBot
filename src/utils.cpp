#include "utils.h"

#define KNIGHT 0
#define BISHOP 1
#define ROOK 2
#define QUEEN 3
#define KING 4
#define PAWN 5

static std::map<std::string, int> pieceMap { {"at", 0}, {"fil", 1}, {"kale", 2},
                                             {"vezir", 3}, {"sah", 4}, {"piyon", 5}};

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

static bool isValid(std::vector<int>current, std::vector<int>target, const int piece, Game *game){
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
        if (current[0] == target[0] or current[1] == target[1]) return true;
        else return false;
    case QUEEN:
        if (((current[0] == target[0]) or (current[1] == target[1])) or
                abs(current[0] - target[0]) == abs(current[1] - target[1])) return true;
        else return false;
    case KING:
        if (abs(current[0] - target[0]) == 1 and abs(current[1] - target[1]) == 1) return true;
        else if ((current[0] == target[0] or current[1] == target[1]) and
                 (abs(current[0]-target[0]+current[1]-target[1]) == 1)) return true;
        else if (abs(current[0] - target[0]) == 2 and current[1] == target[1]){
            if (current[1] == 1 and game->getBlock(current)->getPiece()->getColor() == "w"){
                if(!static_cast<King *>(game->getBlock(current[0], current[1])->getPiece())->isMoved)
                    return true;
            }
            else if (current[1] == 8 and game->getBlock(current)->getPiece()->getColor() == "b"){
                if(!static_cast<King *>(game->getBlock(current[0], current[1])->getPiece())->isMoved)
                    return true;
            }
        }
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
        else {
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
    default:
        return false;
    }
}

static bool isSame(std::vector<int>current, std::vector<int>target){
    if ((current[0] == target[0]) && (current[1] == target[1])) return true;
    else return false;
}

static bool isBlocked(std::vector<int>current, std::vector<int>target, const int piece, Game *game){
    switch (piece) {
    case KNIGHT:
        return false;
    case BISHOP: {
        int x = current[0], y = current[1];
        // FORWARD, RIGHT
        if (current[0] < target[0] and current[1] < target[1]) {
            while (++x != target[0] and ++y != target[1]){
                if (checkXY(x, y) and game->getBlock(x, y)->getPiece()) return true;
            }
            return false;
        }
        // DOWNWARD, RIGHT
        else if (current[0] < target[0] and current[1] > target[1]) {
            while (++x != target[0] and --y != target[1]){
                if (checkXY(x, y) and game->getBlock(x, y)->getPiece()) return true;
            }
            return false;
        }
        // FORWARD, LEFT
        else if (current[0] > target[0] and current[1] < target[1]) {
            while (--x != target[0] and ++y != target[1]){
                if (checkXY(x, y) and game->getBlock(x, y)->getPiece()) return true;
            }
            return false;
        }
        // DOWNWARD, LEFT
        else if (current[0] > target[0] and current[1] > target[1]) {
            while (--x != target[0] and --y != target[1]){
                if (checkXY(x, y) and game->getBlock(x, y)->getPiece()) return true;
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
                while (++x != target[0] and ++y != target[1]){
                    if (checkXY(x, y) and game->getBlock(x, y)->getPiece()) return true;
                }
                return false;
            }
            // DOWNWARD, RIGHT
            else if (current[0] < target[0] and current[1] > target[1]) {
                while (++x != target[0] and --y != target[1]){
                    if (checkXY(x, y) and game->getBlock(x, y)->getPiece()) return true;
                }
                return false;
            }
            // FORWARD, LEFT
            else if (current[0] > target[0] and current[1] < target[1]) {
                while (--x != target[0] and ++y != target[1]){
                    if (checkXY(x, y) and game->getBlock(x, y)->getPiece()) return true;
                }
                return false;
            }
            // DOWNWARD, LEFT
            else if (current[0] > target[0] and current[1] > target[1]) {
                while (--x != target[0] and --y != target[1]){
                    if (checkXY(x, y) and game->getBlock(x, y)->getPiece()) return true;
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
    default:
        return false;
    }
}

static bool isSameColor(std::vector<int>current, std::vector<int>target, Game *game){
    if(game->getBlock(target[0],target[1])->getPiece() != nullptr){
        if(game->getBlock(current[0],current[1])->getPiece()->getColor() ==
                game->getBlock(target[0],target[1])->getPiece()->getColor())
            return true;
    }
    return false;
}

// It is for checkMove_all().
static bool isCheck(std::vector<int>current, std::vector<int>target, Game *game){
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
            if (tempGetPiece(x, y, current, target, currentPiece, game)->name == "kale"
                    and kingColor != tempGetPiece(x, y, current, target, currentPiece, game)->getColor())
                return true;
            else if (tempGetPiece(x, y, current, target, currentPiece, game)->name == "vezir"
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
            if (tempGetPiece(x, y, current, target, currentPiece, game)->name == "kale"
                    and kingColor != tempGetPiece(x, y, current, target, currentPiece, game)->getColor())
                return true;
            else if (tempGetPiece(x, y, current, target, currentPiece, game)->name == "vezir"
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
            if (tempGetPiece(x, y, current, target, currentPiece, game)->name == "kale"
                    and kingColor != tempGetPiece(x, y, current, target, currentPiece, game)->getColor())
                return true;
            else if (tempGetPiece(x, y, current, target, currentPiece, game)->name == "vezir"
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
            if (tempGetPiece(x, y, current, target, currentPiece, game)->name == "kale"
                    and kingColor != tempGetPiece(x, y, current, target, currentPiece, game)->getColor())
                return true;
            else if (tempGetPiece(x, y, current, target, currentPiece, game)->name == "vezir"
                     and kingColor != tempGetPiece(x, y, current, target, currentPiece, game)->getColor())
                return true;
            break;
        }
    }
    x = kingCoord[0];
    // FORWARD, RIGHT
    x++;
    y++;
    if (checkXY(x, y) and tempGetPiece(x, y, current, target, currentPiece, game)){
        if (tempGetPiece(x, y, current, target, currentPiece, game)->name == "piyon"
                and tempGetPiece(x, y, current, target, currentPiece, game)->getColor() == "b"
                and kingColor != tempGetPiece(x, y, current, target, currentPiece, game)->getColor()){
            return true;
        }
    }
    x = kingCoord[0];
    y = kingCoord[1];
    while (++x != 9 and ++y != 9) {
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
                and tempGetPiece(x, y, current, target, currentPiece, game)->getColor() == "b"
                and kingColor != tempGetPiece(x, y, current, target, currentPiece, game)->getColor()){
            return true;
        }
    }
    x = kingCoord[0];
    y = kingCoord[1];
    while (--x != 0 and ++y != 9) {
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
                and tempGetPiece(x, y, current, target, currentPiece, game)->getColor() == "w"
                and kingColor != tempGetPiece(x, y, current, target, currentPiece, game)->getColor()){
            return true;
        }
    }
    x = kingCoord[0];
    y = kingCoord[1];
    while (++x != 9 and --y != 0) {
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
                and tempGetPiece(x, y, current, target, currentPiece, game)->getColor() == "w"
                and kingColor != tempGetPiece(x, y, current, target, currentPiece, game)->getColor()){
            return true;
        }
    }
    x = kingCoord[0];
    y = kingCoord[1];
    while (--x != 0 and --y != 0) {
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

static int checkMove_all(Piece* piece, int x, int y){
    const int identifier = pieceMap[piece->name];
    // checking whether the piece is NULL
    if (!piece) return -7;
    // getting coordinates
    auto currentCoord(piece->getBlock()->getCoordinates());
    const std::vector<int>targetCoord = {x, y};
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

static bool isBlockEscapable(int x, int y, King* king, Game* game){
    std::string kingColor = king->getColor();
    if (checkXY(x, y) and !game->getBlock(x,y)->getPiece() and !checkMove_all(king, x, y))
        return true;
    else if (checkXY(x, y) and game->getBlock(x,y)->getPiece() and kingColor != game->getBlock(x,y)->getPiece()->getColor()
             and !checkMove_all(king, x, y))
        return true;
    return false;
}

static bool isEscapable(King* king, Game* game){
    auto kingCoord(king->getBlock()->getCoordinates());
    int x = kingCoord[0], y = kingCoord[1];
    // FORWARD
    y++;
    if(isBlockEscapable(x, y, king, game))
        return true;
    y = kingCoord[1];
    // DOWNWARD
    y--;
    if(isBlockEscapable(x, y, king, game))
        return true;
    y = kingCoord[1];
    // RIGHT
    x++;
    if(isBlockEscapable(x, y, king, game))
        return true;
    x = kingCoord[0];
    // LEFT
    x--;
    if(isBlockEscapable(x, y, king, game))
        return true;
    x = kingCoord[0];
    // FORWARD, RIGHT
    x++;
    y++;
    if(isBlockEscapable(x, y, king, game))
        return true;
    x = kingCoord[0];
    y = kingCoord[1];
    // FORWARD, LEFT
    x--;
    y++;
    if(isBlockEscapable(x, y, king, game))
        return true;
    x = kingCoord[0];
    y = kingCoord[1];
    // DOWNWARD, RIGHT
    x++;
    y--;
    if(isBlockEscapable(x, y, king, game))
        return true;
    x = kingCoord[0];
    y = kingCoord[1];
    // DOWNWARD, LEFT
    x--;
    y--;
    if(isBlockEscapable(x, y, king, game))
        return true;
    return false;
}

static bool isBlockBlockable(int emptyBlock_x, int emptyBlock_y, King* king, Game* game){
    std::string kingColor = king->getColor();
    int x = emptyBlock_x, y = emptyBlock_y;
    // FORWARD
    // BLACK PAWN
    y++;
    if (checkXY(x, y) and game->getBlock(x,y)->getPiece()){
        if (kingColor == "b" and game->getBlock(x,y)->getPiece()->name == "piyon"
                and kingColor == game->getBlock(x,y)->getPiece()->getColor()
                and !checkMove_all(game->getBlock(x,y)->getPiece(), emptyBlock_x, emptyBlock_y)){
            return true;
        }

    }
    else if (checkXY(x, y+1) and game->getBlock(x,y+1)->getPiece()){
        if (kingColor == "b" and game->getBlock(x,y+1)->getPiece()->name == "piyon"
                and kingColor == game->getBlock(x,y+1)->getPiece()->getColor() and y+1 == 7
                and !checkMove_all(game->getBlock(x,y+1)->getPiece(), emptyBlock_x, emptyBlock_y)){
            return true;
        }
    }
    y = emptyBlock_y;
    y++;
    for (; y<=8; y++){
        if (checkXY(x, y) and game->getBlock(x,y)->getPiece()){
            if (game->getBlock(x,y)->getPiece()->name == "kale"
                    and kingColor == game->getBlock(x,y)->getPiece()->getColor()
                    and !checkMove_all(game->getBlock(x,y)->getPiece(), emptyBlock_x, emptyBlock_y))
                return true;
            else if (game->getBlock(x,y)->getPiece()->name == "vezir"
                     and kingColor == game->getBlock(x,y)->getPiece()->getColor()
                     and !checkMove_all(game->getBlock(x,y)->getPiece(), emptyBlock_x, emptyBlock_y))
                return true;
            break;
        }
    }
    y = emptyBlock_y;
    // DOWNWARD
    // WHITE PAWN
    y--;
    if (checkXY(x, y) and game->getBlock(x,y)->getPiece()){
        if (kingColor == "w" and game->getBlock(x,y)->getPiece()->name == "piyon"
                and kingColor == game->getBlock(x,y)->getPiece()->getColor()
                and !checkMove_all(game->getBlock(x,y)->getPiece(), emptyBlock_x, emptyBlock_y)){
            return true;
        }

    }
    else if (checkXY(x, y-1) and game->getBlock(x,y-1)->getPiece()){
        if (kingColor == "w" and game->getBlock(x,y-1)->getPiece()->name == "piyon"
                and kingColor == game->getBlock(x,y-1)->getPiece()->getColor() and y-1 == 2
                and !checkMove_all(game->getBlock(x,y-1)->getPiece(), emptyBlock_x, emptyBlock_y)){
            return true;
        }
    }
    y = emptyBlock_y;
    y--;
    for (; y>=1; y--){
        if (checkXY(x, y) and game->getBlock(x,y)->getPiece()){
            if (game->getBlock(x,y)->getPiece()->name == "kale"
                    and kingColor == game->getBlock(x,y)->getPiece()->getColor()
                    and !checkMove_all(game->getBlock(x,y)->getPiece(), emptyBlock_x, emptyBlock_y))
                return true;
            else if (game->getBlock(x,y)->getPiece()->name == "vezir"
                     and kingColor == game->getBlock(x,y)->getPiece()->getColor()
                     and !checkMove_all(game->getBlock(x,y)->getPiece(), emptyBlock_x, emptyBlock_y))
                return true;
            break;
        }
    }
    y = emptyBlock_y;
    // RIGHT
    x++;
    for (; x<=8; x++){
        if (checkXY(x, y) and game->getBlock(x,y)->getPiece()){
            if (game->getBlock(x,y)->getPiece()->name == "kale"
                    and kingColor == game->getBlock(x,y)->getPiece()->getColor()
                    and !checkMove_all(game->getBlock(x,y)->getPiece(), emptyBlock_x, emptyBlock_y))
                return true;
            else if (game->getBlock(x,y)->getPiece()->name == "vezir"
                     and kingColor == game->getBlock(x,y)->getPiece()->getColor()
                     and !checkMove_all(game->getBlock(x,y)->getPiece(), emptyBlock_x, emptyBlock_y))
                return true;
            break;
        }
    }
    x = emptyBlock_x;
    // LEFT
    x--;
    for (; x>=1; x--){
        if (checkXY(x, y) and game->getBlock(x,y)->getPiece()){
            if (game->getBlock(x,y)->getPiece()->name == "kale"
                    and kingColor == game->getBlock(x,y)->getPiece()->getColor()
                    and !checkMove_all(game->getBlock(x,y)->getPiece(), emptyBlock_x, emptyBlock_y))
                return true;
            else if (game->getBlock(x,y)->getPiece()->name == "vezir"
                     and kingColor == game->getBlock(x,y)->getPiece()->getColor()
                     and !checkMove_all(game->getBlock(x,y)->getPiece(), emptyBlock_x, emptyBlock_y))
                return true;
            break;
        }
    }
    x = emptyBlock_x;
    // FORWARD, RIGHT
    while (++x != 9 and ++y != 9){
        if (checkXY(x, y) and game->getBlock(x,y)->getPiece()){
            if (game->getBlock(x,y)->getPiece()->name == "fil"
                    and kingColor == game->getBlock(x,y)->getPiece()->getColor()
                    and !checkMove_all(game->getBlock(x,y)->getPiece(), emptyBlock_x, emptyBlock_y))
                return true;
            if (game->getBlock(x,y)->getPiece()->name == "vezir"
                    and kingColor == game->getBlock(x,y)->getPiece()->getColor()
                    and !checkMove_all(game->getBlock(x,y)->getPiece(), emptyBlock_x, emptyBlock_y))
                return true;
            break;
        }
    }
    x = emptyBlock_x;
    y = emptyBlock_y;
    // FORWARD, LEFT
    while (--x != 0 and ++y != 9) {
        if (checkXY(x, y) and game->getBlock(x,y)->getPiece()){
            if (game->getBlock(x,y)->getPiece()->name == "fil"
                    and kingColor == game->getBlock(x,y)->getPiece()->getColor()
                    and !checkMove_all(game->getBlock(x,y)->getPiece(), emptyBlock_x, emptyBlock_y))
                return true;
            else if (game->getBlock(x,y)->getPiece()->name == "vezir"
                     and kingColor == game->getBlock(x,y)->getPiece()->getColor()
                     and !checkMove_all(game->getBlock(x,y)->getPiece(), emptyBlock_x, emptyBlock_y))
                return true;
            break;
        }
    }
    x = emptyBlock_x;
    y = emptyBlock_y;
    // DOWNWARD, RIGHT
    while (++x != 9 and --y != 0) {
        if (checkXY(x, y) and game->getBlock(x,y)->getPiece()){
            if (game->getBlock(x,y)->getPiece()->name == "fil"
                    and kingColor == game->getBlock(x,y)->getPiece()->getColor()
                    and !checkMove_all(game->getBlock(x,y)->getPiece(), emptyBlock_x, emptyBlock_y))
                return true;
            else if (game->getBlock(x,y)->getPiece()->name == "vezir"
                     and kingColor == game->getBlock(x,y)->getPiece()->getColor()
                     and !checkMove_all(game->getBlock(x,y)->getPiece(), emptyBlock_x, emptyBlock_y))
                return true;
            break;
        }
    }
    x = emptyBlock_x;
    y = emptyBlock_y;
    // DOWNWARD, LEFT
    while (--x != 0 and --y != 0) {
        if (checkXY(x, y) and game->getBlock(x,y)->getPiece()){
            if (game->getBlock(x,y)->getPiece()->name == "fil"
                    and kingColor == game->getBlock(x,y)->getPiece()->getColor()
                    and !checkMove_all(game->getBlock(x,y)->getPiece(), emptyBlock_x, emptyBlock_y))
                return true;
            else if (game->getBlock(x,y)->getPiece()->name == "vezir"
                     and kingColor == game->getBlock(x,y)->getPiece()->getColor()
                     and !checkMove_all(game->getBlock(x,y)->getPiece(), emptyBlock_x, emptyBlock_y))
                return true;
            break;
        }
    }
    x = emptyBlock_x;
    y = emptyBlock_y;

    int x_move, y_move;

    // 1 FORWARD, 2 RIGHT
    x_move = 2;
    y_move = 1;
    if (checkXY(x+x_move, y+y_move) and game->getBlock(x+x_move,y+y_move)->getPiece()) {
        if (game->getBlock(x+x_move,y+y_move)->getPiece()->name == "at"
                and kingColor == game->getBlock(x+x_move,y+y_move)->getPiece()->getColor()
                and !checkMove_all(game->getBlock(x+x_move,y+y_move)->getPiece(), emptyBlock_x, emptyBlock_y))
            return true;
    }
    // 1 FORWARD, 2 LEFT
    x_move = -2;
    y_move = 1;
    if (checkXY(x+x_move, y+y_move) and game->getBlock(x+x_move,y+y_move)->getPiece()) {
        if (game->getBlock(x+x_move,y+y_move)->getPiece()->name == "at"
                and kingColor == game->getBlock(x+x_move,y+y_move)->getPiece()->getColor()
                and !checkMove_all(game->getBlock(x+x_move,y+y_move)->getPiece(), emptyBlock_x, emptyBlock_y))
            return true;
    }
    // 1 DOWNWARD, 2 RIGHT
    x_move = 2;
    y_move = -1;
    if (checkXY(x+x_move, y+y_move) and game->getBlock(x+x_move,y+y_move)->getPiece()) {
        if (game->getBlock(x+x_move,y+y_move)->getPiece()->name == "at"
                and kingColor == game->getBlock(x+x_move,y+y_move)->getPiece()->getColor()
                and !checkMove_all(game->getBlock(x+x_move,y+y_move)->getPiece(), emptyBlock_x, emptyBlock_y))
            return true;
    }
    // 1 DOWNWARD, 2 LEFT
    x_move = -2;
    y_move = -1;
    if (checkXY(x+x_move, y+y_move) and game->getBlock(x+x_move,y+y_move)->getPiece()) {
        if (game->getBlock(x+x_move,y+y_move)->getPiece()->name == "at"
                and kingColor == game->getBlock(x+x_move,y+y_move)->getPiece()->getColor()
                and !checkMove_all(game->getBlock(x+x_move,y+y_move)->getPiece(), emptyBlock_x, emptyBlock_y))
            return true;
    }
    // 2 FORWARD, 1 RIGHT
    x_move = 1;
    y_move = 2;
    if (checkXY(x+x_move, y+y_move) and game->getBlock(x+x_move,y+y_move)->getPiece()) {
        if (game->getBlock(x+x_move,y+y_move)->getPiece()->name == "at"
                and kingColor == game->getBlock(x+x_move,y+y_move)->getPiece()->getColor()
                and !checkMove_all(game->getBlock(x+x_move,y+y_move)->getPiece(), emptyBlock_x, emptyBlock_y))
            return true;
    }
    // 2 FORWARD, 1 LEFT
    x_move = -1;
    y_move = 2;
    if (checkXY(x+x_move, y+y_move) and game->getBlock(x+x_move,y+y_move)->getPiece()) {
        if (game->getBlock(x+x_move,y+y_move)->getPiece()->name == "at"
                and kingColor == game->getBlock(x+x_move,y+y_move)->getPiece()->getColor()
                and !checkMove_all(game->getBlock(x+x_move,y+y_move)->getPiece(), emptyBlock_x, emptyBlock_y))
            return true;
    }
    // 2 DOWNWARD, 1 RIGHT
    x_move = 1;
    y_move = -2;
    if (checkXY(x+x_move, y+y_move) and game->getBlock(x+x_move,y+y_move)->getPiece()) {
        if (game->getBlock(x+x_move,y+y_move)->getPiece()->name == "at"
                and kingColor == game->getBlock(x+x_move,y+y_move)->getPiece()->getColor()
                and !checkMove_all(game->getBlock(x+x_move,y+y_move)->getPiece(), emptyBlock_x, emptyBlock_y))
            return true;
    }
    // 2 DOWNWARD, 1 LEFT
    x_move = -1;
    y_move = -2;
    if (checkXY(x+x_move, y+y_move) and game->getBlock(x+x_move,y+y_move)->getPiece()) {
        if (game->getBlock(x+x_move,y+y_move)->getPiece()->name == "at"
                and kingColor == game->getBlock(x+x_move,y+y_move)->getPiece()->getColor()
                and !checkMove_all(game->getBlock(x+x_move,y+y_move)->getPiece(), emptyBlock_x, emptyBlock_y))
            return true;
    }
    return false;
}

static bool isBlockable(King* king, Game* game){
    std::vector<int> attackerCoord = *(game->getAttacker());
    if(game->getBlock(attackerCoord)->getPiece()->name != "at"){
        auto kingCoord(king->getBlock()->getCoordinates());
        auto kingColor = king->getColor();
        // Finding out what direction the path between the king and the attacker has
        // Crosswise direction (BISHOP MOVEMENT):
        if (abs(kingCoord[0] - attackerCoord[0]) == abs(kingCoord[1] - attackerCoord[1])){
            int x = kingCoord[0], y = kingCoord[1];
            // FORWARD, RIGHT
            if (kingCoord[0] < attackerCoord[0] and kingCoord[1] < attackerCoord[1]){
                while (++x != attackerCoord[0] and ++y != attackerCoord[1]){
                    if (isBlockBlockable(x, y, king, game)) return true;
                }
            }
            // DOWNWARD, RIGHT
            else if (kingCoord[0] < attackerCoord[0] and kingCoord[1] > attackerCoord[1]){
                while (++x != attackerCoord[0] and --y != attackerCoord[1]){
                    if (isBlockBlockable(x, y, king, game)) return true;
                }
            }
            // FORWARD, LEFT
            else if (kingCoord[0] > attackerCoord[0] and kingCoord[1] < attackerCoord[1]){
                while (--x != attackerCoord[0] and ++y != attackerCoord[1]){
                    if (isBlockBlockable(x, y, king, game)) return true;
                }
            }
            // DOWNWARD, LEFT
            else if (kingCoord[0] > attackerCoord[0] and kingCoord[1] > attackerCoord[1]){
                while (--x != attackerCoord[0] and --y != attackerCoord[1]){
                    if (isBlockBlockable(x, y, king, game)) return true;
                }
            }
        }
        // Straight direction (ROOK MOVEMENT):
        else if (kingCoord[0] == attackerCoord[0] or kingCoord[1] == attackerCoord[1]){
            // MOVEMENT IN Y AXIS
            if (kingCoord[0] == attackerCoord[0]) {
                // FORWARD
                if (kingCoord[1] < attackerCoord[1]){
                    for (int i = kingCoord[1]+1; i<attackerCoord[1]; i++){
                        if (isBlockBlockable(kingCoord[0], i, king, game)) return true;
                    }
                }
                // DOWNWARD
                else if (kingCoord[1] > attackerCoord[1]){
                    for (int i = kingCoord[1]-1; i>attackerCoord[1]; i--){
                        if (isBlockBlockable(kingCoord[0], i, king, game)) return true;
                    }
                }
            }
            // MOVEMENT IN X AXIS
            else if (kingCoord[1] == attackerCoord[1]){
                // RIGHT
                if (kingCoord[0] < attackerCoord[0]){
                    for (int i = kingCoord[0]+1; i<attackerCoord[0]; i++){
                        if (isBlockBlockable(i, kingCoord[1], king, game)) return true;
                    }
                }
                // LEFT
                else if (kingCoord[0] > attackerCoord[0]){
                    for (int i = kingCoord[0]-1; i>attackerCoord[0]; i--){
                        if (isBlockBlockable(i, kingCoord[1], king, game)) return true;
                    }
                }
            }
        }
    }
    return false;
}

static bool isAttackerEatable(Game* game){
    auto attackerCoord = *(game->getAttacker());
    int x = attackerCoord[0], y = attackerCoord[1];
    std::string attackerColor = game->getBlock(x, y)->getColor();
    // FORWARD
    y++;
    for (; y<=8; y++){
        if (checkXY(x, y) and game->getBlock(x,y)->getPiece()) {
            if (game->getBlock(x,y)->getPiece()->name == "kale"
                    and attackerColor != game->getBlock(x,y)->getPiece()->getColor()
                    and !checkMove_all(game->getBlock(x,y)->getPiece(), attackerCoord[0], attackerCoord[1]))
                return true;
            else if (game->getBlock(x,y)->getPiece()->name == "vezir"
                     and attackerColor != game->getBlock(x,y)->getPiece()->getColor()
                     and !checkMove_all(game->getBlock(x,y)->getPiece(), attackerCoord[0], attackerCoord[1]))
                return true;
            break;
        }
    }
    y = attackerCoord[1];
    // DOWNWARD
    y--;
    for (; y>=1; y--) {
        if (checkXY(x, y) and game->getBlock(x,y)->getPiece()) {
            if (game->getBlock(x,y)->getPiece()->name == "kale"
                    and attackerColor != game->getBlock(x,y)->getPiece()->getColor()
                    and !checkMove_all(game->getBlock(x,y)->getPiece(), attackerCoord[0], attackerCoord[1]))
                return true;
            else if (game->getBlock(x,y)->getPiece()->name == "vezir"
                     and attackerColor != game->getBlock(x,y)->getPiece()->getColor()
                     and !checkMove_all(game->getBlock(x,y)->getPiece(), attackerCoord[0], attackerCoord[1]))
                return true;
            break;
        }
    }
    y = attackerCoord[1];
    // RIGHT
    x++;
    for (; x<=8; x++){
        if (checkXY(x, y) and game->getBlock(x,y)->getPiece()) {
            if (game->getBlock(x,y)->getPiece()->name == "kale"
                    and attackerColor != game->getBlock(x,y)->getPiece()->getColor()
                    and !checkMove_all(game->getBlock(x,y)->getPiece(), attackerCoord[0], attackerCoord[1]))
                return true;
            else if (game->getBlock(x,y)->getPiece()->name == "vezir"
                     and attackerColor != game->getBlock(x,y)->getPiece()->getColor()
                     and !checkMove_all(game->getBlock(x,y)->getPiece(), attackerCoord[0], attackerCoord[1]))
                return true;
            break;
        }
    }
    x = attackerCoord[0];
    // LEFT
    x--;
    for (; x>=1; x--){
        if (checkXY(x, y) and game->getBlock(x,y)->getPiece()) {
            if (game->getBlock(x,y)->getPiece()->name == "kale"
                    and attackerColor != game->getBlock(x,y)->getPiece()->getColor()
                    and !checkMove_all(game->getBlock(x,y)->getPiece(), attackerCoord[0], attackerCoord[1]))
                return true;
            else if (game->getBlock(x,y)->getPiece()->name == "vezir"
                     and attackerColor != game->getBlock(x,y)->getPiece()->getColor()
                     and !checkMove_all(game->getBlock(x,y)->getPiece(), attackerCoord[0], attackerCoord[1]))
                return true;
            break;
        }
    }
    x = attackerCoord[0];
    // FORWARD, RIGHT
    x++;
    y++;
    if (checkXY(x, y) and game->getBlock(x,y)->getPiece()){
        if (game->getBlock(x,y)->getPiece()->name == "piyon"
                and game->getBlock(x,y)->getPiece()->getColor() == "b"
                and attackerColor != game->getBlock(x,y)->getPiece()->getColor()
                and !checkMove_all(game->getBlock(x,y)->getPiece(), attackerCoord[0], attackerCoord[1])){
            return true;
        }
    }
    x = attackerCoord[0];
    y = attackerCoord[1];
    while (++x != 9 and ++y != 9) {
        if (checkXY(x, y) and game->getBlock(x,y)->getPiece()) {
            if (game->getBlock(x,y)->getPiece()->name == "fil"
                    and attackerColor != game->getBlock(x,y)->getPiece()->getColor()
                    and !checkMove_all(game->getBlock(x,y)->getPiece(), attackerCoord[0], attackerCoord[1]))
                return true;
            if (game->getBlock(x,y)->getPiece()->name == "vezir"
                    and attackerColor != game->getBlock(x,y)->getPiece()->getColor()
                    and !checkMove_all(game->getBlock(x,y)->getPiece(), attackerCoord[0], attackerCoord[1]))
                return true;
            break;
        }
    }
    x = attackerCoord[0];
    y = attackerCoord[1];
    // FORWARD, LEFT
    x--;
    y++;
    if (checkXY(x, y) and game->getBlock(x,y)->getPiece()){
        if (game->getBlock(x,y)->getPiece()->name == "piyon"
                and game->getBlock(x,y)->getPiece()->getColor() == "b"
                and attackerColor != game->getBlock(x,y)->getPiece()->getColor()
                and !checkMove_all(game->getBlock(x,y)->getPiece(), attackerCoord[0], attackerCoord[1])){
            return true;
        }
    }
    x = attackerCoord[0];
    y = attackerCoord[1];
    while (--x != 0 and ++y != 9) {
        if (checkXY(x, y) and game->getBlock(x,y)->getPiece()) {
            if (game->getBlock(x,y)->getPiece()->name == "fil"
                    and attackerColor != game->getBlock(x,y)->getPiece()->getColor()
                    and !checkMove_all(game->getBlock(x,y)->getPiece(), attackerCoord[0], attackerCoord[1]))
                return true;
            else if (game->getBlock(x,y)->getPiece()->name == "vezir"
                     and attackerColor != game->getBlock(x,y)->getPiece()->getColor()
                     and !checkMove_all(game->getBlock(x,y)->getPiece(), attackerCoord[0], attackerCoord[1]))
                return true;
            break;
        }
    }
    x = attackerCoord[0];
    y = attackerCoord[1];
    // DOWNWARD, RIGHT
    x++;
    y--;
    if (checkXY(x, y) and game->getBlock(x,y)->getPiece()){
        if (game->getBlock(x,y)->getPiece()->name == "piyon"
                and game->getBlock(x,y)->getPiece()->getColor() == "w"
                and attackerColor != game->getBlock(x,y)->getPiece()->getColor()
                and !checkMove_all(game->getBlock(x,y)->getPiece(), attackerCoord[0], attackerCoord[1])){
            return true;
        }
    }
    x = attackerCoord[0];
    y = attackerCoord[1];
    while (++x != 9 and --y != 0) {
        if (checkXY(x, y) and game->getBlock(x,y)->getPiece()) {
            if (game->getBlock(x,y)->getPiece()->name == "fil"
                    and attackerColor != game->getBlock(x,y)->getPiece()->getColor()
                    and !checkMove_all(game->getBlock(x,y)->getPiece(), attackerCoord[0], attackerCoord[1]))
                return true;
            else if (game->getBlock(x,y)->getPiece()->name == "vezir"
                     and attackerColor != game->getBlock(x,y)->getPiece()->getColor()
                     and !checkMove_all(game->getBlock(x,y)->getPiece(), attackerCoord[0], attackerCoord[1]))
                return true;
            break;
        }
    }
    x = attackerCoord[0];
    y = attackerCoord[1];
    // DOWNWARD, LEFT
    x--;
    y--;
    if (checkXY(x, y) and game->getBlock(x,y)->getPiece()){
        if (game->getBlock(x,y)->getPiece()->name == "piyon"
                and game->getBlock(x,y)->getPiece()->getColor() == "w"
                and attackerColor != game->getBlock(x,y)->getPiece()->getColor()
                and !checkMove_all(game->getBlock(x,y)->getPiece(), attackerCoord[0], attackerCoord[1])){
            return true;
        }
    }
    x = attackerCoord[0];
    y = attackerCoord[1];
    while (--x != 0 and --y != 0) {
        if (checkXY(x, y) and game->getBlock(x,y)->getPiece()) {
            if (game->getBlock(x,y)->getPiece()->name == "fil"
                    and attackerColor != game->getBlock(x,y)->getPiece()->getColor()
                    and !checkMove_all(game->getBlock(x,y)->getPiece(), attackerCoord[0], attackerCoord[1]))
                return true;
            else if (game->getBlock(x,y)->getPiece()->name == "vezir"
                     and attackerColor != game->getBlock(x,y)->getPiece()->getColor()
                     and !checkMove_all(game->getBlock(x,y)->getPiece(), attackerCoord[0], attackerCoord[1]))
                return true;
            break;
        }
    }
    x = attackerCoord[0];
    y = attackerCoord[1];

    int x_move, y_move;

    // 1 FORWARD, 2 RIGHT
    x_move = 2;
    y_move = 1;

    if (checkXY(x+x_move, y+y_move) and game->getBlock(x+x_move,y+y_move)->getPiece()) {
        if (game->getBlock(x+x_move,y+y_move)->getPiece()->name == "at"
                and attackerColor != game->getBlock(x+x_move,y+y_move)->getPiece()->getColor()
                and !checkMove_all(game->getBlock(x+x_move,y+y_move)->getPiece(), attackerCoord[0], attackerCoord[1]))
            return true;
    }
    // 1 FORWARD, 2 LEFT
    x_move = -2;
    y_move = 1;
    if (checkXY(x+x_move, y+y_move) and game->getBlock(x+x_move,y+y_move)->getPiece()) {
        if (game->getBlock(x+x_move,y+y_move)->getPiece()->name == "at"
                and attackerColor != game->getBlock(x+x_move,y+y_move)->getPiece()->getColor()
                and !checkMove_all(game->getBlock(x+x_move,y+y_move)->getPiece(), attackerCoord[0], attackerCoord[1]))
            return true;
    }
    // 1 DOWNWARD, 2 RIGHT
    x_move = 2;
    y_move = -1;
    if (checkXY(x+x_move, y+y_move) and game->getBlock(x+x_move,y+y_move)->getPiece()) {
        if (game->getBlock(x+x_move,y+y_move)->getPiece()->name == "at"
                and attackerColor != game->getBlock(x+x_move,y+y_move)->getPiece()->getColor()
                and !checkMove_all(game->getBlock(x+x_move,y+y_move)->getPiece(), attackerCoord[0], attackerCoord[1]))
            return true;
    }
    // 1 DOWNWARD, 2 LEFT
    x_move = -2;
    y_move = -1;
    if (checkXY(x+x_move, y+y_move) and game->getBlock(x+x_move,y+y_move)->getPiece()) {
        if (game->getBlock(x+x_move,y+y_move)->getPiece()->name == "at"
                and attackerColor != game->getBlock(x+x_move,y+y_move)->getPiece()->getColor()
                and !checkMove_all(game->getBlock(x+x_move,y+y_move)->getPiece(), attackerCoord[0], attackerCoord[1]))
            return true;
    }
    // 2 FORWARD, 1 RIGHT
    x_move = 1;
    y_move = 2;
    if (checkXY(x+x_move, y+y_move) and game->getBlock(x+x_move,y+y_move)->getPiece()) {
        if (game->getBlock(x+x_move,y+y_move)->getPiece()->name == "at"
                and attackerColor != game->getBlock(x+x_move,y+y_move)->getPiece()->getColor()
                and !checkMove_all(game->getBlock(x+x_move,y+y_move)->getPiece(), attackerCoord[0], attackerCoord[1]))
            return true;
    }
    // 2 FORWARD, 1 LEFT
    x_move = -1;
    y_move = 2;
    if (checkXY(x+x_move, y+y_move) and game->getBlock(x+x_move,y+y_move)->getPiece()) {
        if (game->getBlock(x+x_move,y+y_move)->getPiece()->name == "at"
                and attackerColor != game->getBlock(x+x_move,y+y_move)->getPiece()->getColor()
                and !checkMove_all(game->getBlock(x+x_move,y+y_move)->getPiece(), attackerCoord[0], attackerCoord[1]))
            return true;
    }
    // 2 DOWNWARD, 1 RIGHT
    x_move = 1;
    y_move = -2;
    if (checkXY(x+x_move, y+y_move) and game->getBlock(x+x_move,y+y_move)->getPiece()) {
        if (game->getBlock(x+x_move,y+y_move)->getPiece()->name == "at"
                and attackerColor != game->getBlock(x+x_move,y+y_move)->getPiece()->getColor()
                and !checkMove_all(game->getBlock(x+x_move,y+y_move)->getPiece(), attackerCoord[0], attackerCoord[1]))
            return true;
    }
    // 2 DOWNWARD, 1 LEFT
    x_move = -1;
    y_move = -2;
    if (checkXY(x+x_move, y+y_move) and game->getBlock(x+x_move,y+y_move)->getPiece()) {
        if (game->getBlock(x+x_move,y+y_move)->getPiece()->name == "at"
                and attackerColor != game->getBlock(x+x_move,y+y_move)->getPiece()->getColor()
                and !checkMove_all(game->getBlock(x+x_move,y+y_move)->getPiece(), attackerCoord[0], attackerCoord[1]))
            return true;
    }
    return false;
}

static std::vector<int> checkCastling(King* king, Block* target, Game* game) {
    std::string turn = king->getColor();
    auto kingCoord = king->getBlock()->getCoordinates();
    auto targetCoord = target->getCoordinates();
    /*
     * wCastlingLeft = game->getCastling()[0]
     * wCastlingRight = game->getCastling()[1]
     * bCastlingLeft = game->getCastling()[2]
     * bCastlingRight = game->getCastling()[3]
     */
    if (turn == "w") {
        // LEFT
        if (kingCoord[0] - targetCoord[0] == 2 and game->getCastling()[0]) {
            if (game->getBlock(1, 1)->getPiece()) {
                Rook *rook = static_cast<Rook *>(game->getBlock(1, 1)->getPiece());
                auto rookCoord = rook->getBlock()->getCoordinates();
                if (!king->isMoved and !rook->isMoved
                        and !checkMove_all(king, targetCoord[0], targetCoord[1])) {
                    for (int i = kingCoord[0] - 1; i > rookCoord[0]; i--) {
                        if (game->getBlock(i, kingCoord[1])->getPiece()) return std::vector<int>{};
                    }
                    return std::vector<int>{1, 1};
                }
            }
        }
        // RIGHT
        else if (kingCoord[0] - targetCoord[0] == -2 and game->getCastling()[1]) {
            if (game->getBlock(8, 1)->getPiece()) {
                Rook *rook = static_cast<Rook *>(game->getBlock(8, 1)->getPiece());
                auto rookCoord = rook->getBlock()->getCoordinates();
                if (!king->isMoved and !rook->isMoved
                        and !checkMove_all(king, targetCoord[0], targetCoord[1])) {
                    for (int i = kingCoord[0] + 1; i < rookCoord[0]; i++) {
                        if (game->getBlock(i, kingCoord[1])->getPiece()) return std::vector<int>{};
                    }
                    return std::vector<int>{8, 1};
                }
            }
        }
    }
    else {
        // LEFT
        if (kingCoord[0] - targetCoord[0] == 2 and game->getCastling()[2]) {
            if (game->getBlock(1, 8)->getPiece()) {
                Rook *rook = static_cast<Rook *>(game->getBlock(1, 8)->getPiece());
                auto rookCoord = rook->getBlock()->getCoordinates();
                if (!king->isMoved and !rook->isMoved
                        and !checkMove_all(king, targetCoord[0], targetCoord[1])) {
                    for (int i = kingCoord[0] - 1; i > rookCoord[0]; i--) {
                        if (game->getBlock(i, kingCoord[1])->getPiece()) return std::vector<int>{};
                    }
                    return std::vector<int>{1, 8};
                }
            }
        }
        // RIGHT
        else if (kingCoord[0] - targetCoord[0] == -2 and game->getCastling()[3]) {
            if (game->getBlock(8, 8)->getPiece()) {
                Rook *rook = static_cast<Rook *>(game->getBlock(8, 8)->getPiece());
                auto rookCoord = rook->getBlock()->getCoordinates();
                if (!king->isMoved and !rook->isMoved
                        and !checkMove_all(king, targetCoord[0], targetCoord[1])) {
                    for (int i = kingCoord[0] + 1; i < rookCoord[0]; i++) {
                        if (game->getBlock(i, kingCoord[1])->getPiece()) return std::vector<int>{};
                    }
                    return std::vector<int>{8, 8};
                }
            }
        }
    }
    return std::vector<int>{};
}

int checkMove_all(Piece* piece, Block* target){
    std::map<std::string, int> pieceMap { {"at", 0}, {"fil", 1}, {"kale", 2}, {"vezir", 3}, {"sah", 4}, {"piyon", 5}};
    const int identifier = pieceMap[piece->name];
    // checking whether the target or piece is NULL
    if (!target or !piece) return -7;
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
    // checking castling
    if(piece->name == "sah" and abs(currentCoord[0] - targetCoord[0]) == 2){
        auto rookCoord = checkCastling(static_cast<King *>(piece), target, piece->getGame());
        if(rookCoord.empty()) return -6;
        else {
            auto game = piece->getGame();
            game->setCastlingRook(static_cast<Rook *>(game->getBlock(rookCoord)->getPiece()));
            return 1;
        }
    }
    return 0;
}

// It is used for Game class
// If there is a check, it returns a vector contains the coordinates of the attacker,
// If not, it returns an empty vector. You can check whether a vector is empty by "vector.empty()"
std::vector<int> isCheck_Game(const std::string& kingColor, Game *game){
    auto king = game->getKing(kingColor);
    auto kingCoord(king->getBlock()->getCoordinates());

    int x = kingCoord[0], y = kingCoord[1];
    // FORWARD
    y++;
    for (; y<=8; y++){
        if (checkXY(x, y) and game->getBlock(x,y)->getPiece()) {
            if (game->getBlock(x,y)->getPiece()->name == "kale"
                    and kingColor != game->getBlock(x,y)->getPiece()->getColor())
                return std::vector<int>{x, y};
            else if (game->getBlock(x,y)->getPiece()->name == "vezir"
                     and kingColor != game->getBlock(x,y)->getPiece()->getColor())
                return std::vector<int>{x, y};
            break;
        }
    }
    y = kingCoord[1];
    // DOWNWARD
    y--;
    for (; y>=1; y--) {
        if (checkXY(x, y) and game->getBlock(x,y)->getPiece()) {
            if (game->getBlock(x,y)->getPiece()->name == "kale"
                    and kingColor != game->getBlock(x,y)->getPiece()->getColor())
                return std::vector<int>{x, y};
            else if (game->getBlock(x,y)->getPiece()->name == "vezir"
                     and kingColor != game->getBlock(x,y)->getPiece()->getColor())
                return std::vector<int>{x, y};
            break;
        }
    }
    y = kingCoord[1];
    // RIGHT
    x++;
    for (; x<=8; x++){
        if (checkXY(x, y) and game->getBlock(x,y)->getPiece()) {
            if (game->getBlock(x,y)->getPiece()->name == "kale"
                    and kingColor != game->getBlock(x,y)->getPiece()->getColor())
                return std::vector<int>{x, y};
            else if (game->getBlock(x,y)->getPiece()->name == "vezir"
                     and kingColor != game->getBlock(x,y)->getPiece()->getColor())
                return std::vector<int>{x, y};
            break;
        }
    }
    x = kingCoord[0];
    // LEFT
    x--;
    for (; x>=1; x--){
        if (checkXY(x, y) and game->getBlock(x,y)->getPiece()) {
            if (game->getBlock(x,y)->getPiece()->name == "kale"
                    and kingColor != game->getBlock(x,y)->getPiece()->getColor())
                return std::vector<int>{x, y};
            else if (game->getBlock(x,y)->getPiece()->name == "vezir"
                     and kingColor != game->getBlock(x,y)->getPiece()->getColor())
                return std::vector<int>{x, y};
            break;
        }
    }
    x = kingCoord[0];
    // FORWARD, RIGHT
    x++;
    y++;
    if (checkXY(x, y) and game->getBlock(x,y)->getPiece()){
        if (game->getBlock(x,y)->getPiece()->name == "piyon"
                and game->getBlock(x,y)->getPiece()->getColor() == "b"
                and kingColor != game->getBlock(x,y)->getPiece()->getColor()){
            return std::vector<int>{x, y};
        }
    }
    x = kingCoord[0];
    y = kingCoord[1];
    while (++x != 9 and ++y != 9) {
        if (checkXY(x, y) and game->getBlock(x,y)->getPiece()) {
            if (game->getBlock(x,y)->getPiece()->name == "fil"
                    and kingColor != game->getBlock(x,y)->getPiece()->getColor())
                return std::vector<int>{x, y};
            if (game->getBlock(x,y)->getPiece()->name == "vezir"
                    and kingColor != game->getBlock(x,y)->getPiece()->getColor())
                return std::vector<int>{x, y};
            break;
        }
    }
    x = kingCoord[0];
    y = kingCoord[1];
    // FORWARD, LEFT
    x--;
    y++;
    if (checkXY(x, y) and game->getBlock(x,y)->getPiece()){
        if (game->getBlock(x,y)->getPiece()->name == "piyon"
                and game->getBlock(x,y)->getPiece()->getColor() == "b"
                and kingColor != game->getBlock(x,y)->getPiece()->getColor()){
            return std::vector<int>{x, y};
        }
    }
    x = kingCoord[0];
    y = kingCoord[1];
    while (--x != 0 and ++y != 9) {
        if (checkXY(x, y) and game->getBlock(x,y)->getPiece()) {
            if (game->getBlock(x,y)->getPiece()->name == "fil"
                    and kingColor != game->getBlock(x,y)->getPiece()->getColor())
                return std::vector<int>{x, y};
            else if (game->getBlock(x,y)->getPiece()->name == "vezir"
                     and kingColor != game->getBlock(x,y)->getPiece()->getColor())
                return std::vector<int>{x, y};
            break;
        }
    }
    x = kingCoord[0];
    y = kingCoord[1];
    // DOWNWARD, RIGHT
    x++;
    y--;
    if (checkXY(x, y) and game->getBlock(x,y)->getPiece()){
        if (game->getBlock(x,y)->getPiece()->name == "piyon"
                and game->getBlock(x,y)->getPiece()->getColor() == "w"
                and kingColor != game->getBlock(x,y)->getPiece()->getColor()){
            return std::vector<int>{x, y};
        }
    }
    x = kingCoord[0];
    y = kingCoord[1];
    while (++x != 9 and --y != 0) {
        if (checkXY(x, y) and game->getBlock(x,y)->getPiece()) {
            if (game->getBlock(x,y)->getPiece()->name == "fil"
                    and kingColor != game->getBlock(x,y)->getPiece()->getColor())
                return std::vector<int>{x, y};
            else if (game->getBlock(x,y)->getPiece()->name == "vezir"
                     and kingColor != game->getBlock(x,y)->getPiece()->getColor())
                return std::vector<int>{x, y};
            break;
        }
    }
    x = kingCoord[0];
    y = kingCoord[1];
    // DOWNWARD, LEFT
    x--;
    y--;
    if (checkXY(x, y) and game->getBlock(x,y)->getPiece()){
        if (game->getBlock(x,y)->getPiece()->name == "piyon"
                and game->getBlock(x,y)->getPiece()->getColor() == "w"
                and kingColor != game->getBlock(x,y)->getPiece()->getColor()){
            return std::vector<int>{x, y};
        }
    }
    x = kingCoord[0];
    y = kingCoord[1];
    while (--x != 0 and --y != 0) {
        if (checkXY(x, y) and game->getBlock(x,y)->getPiece()) {
            if (game->getBlock(x,y)->getPiece()->name == "fil"
                    and kingColor != game->getBlock(x,y)->getPiece()->getColor())
                return std::vector<int>{x, y};
            else if (game->getBlock(x,y)->getPiece()->name == "vezir"
                     and kingColor != game->getBlock(x,y)->getPiece()->getColor())
                return std::vector<int>{x, y};
            break;
        }
    }
    x = kingCoord[0];
    y = kingCoord[1];

    int x_move, y_move;

    // 1 FORWARD, 2 RIGHT
    x_move = 2;
    y_move = 1;

    if (checkXY(x+x_move, y+y_move) and game->getBlock(x+x_move,y+y_move)->getPiece()) {
        if (game->getBlock(x+x_move,y+y_move)->getPiece()->name == "at"
                and kingColor != game->getBlock(x+x_move,y+y_move)->getPiece()->getColor())
            return std::vector<int>{x+x_move, y+y_move};
    }
    // 1 FORWARD, 2 LEFT
    x_move = -2;
    y_move = 1;
    if (checkXY(x+x_move, y+y_move) and game->getBlock(x+x_move,y+y_move)->getPiece()) {
        if (game->getBlock(x+x_move,y+y_move)->getPiece()->name == "at"
                and kingColor != game->getBlock(x+x_move,y+y_move)->getPiece()->getColor())
            return std::vector<int>{x+x_move, y+y_move};
    }
    // 1 DOWNWARD, 2 RIGHT
    x_move = 2;
    y_move = -1;
    if (checkXY(x+x_move, y+y_move) and game->getBlock(x+x_move,y+y_move)->getPiece()) {
        if (game->getBlock(x+x_move,y+y_move)->getPiece()->name == "at"
                and kingColor != game->getBlock(x+x_move,y+y_move)->getPiece()->getColor())
            return std::vector<int>{x+x_move, y+y_move};
    }
    // 1 DOWNWARD, 2 LEFT
    x_move = -2;
    y_move = -1;
    if (checkXY(x+x_move, y+y_move) and game->getBlock(x+x_move,y+y_move)->getPiece()) {
        if (game->getBlock(x+x_move,y+y_move)->getPiece()->name == "at"
                and kingColor != game->getBlock(x+x_move,y+y_move)->getPiece()->getColor())
            return std::vector<int>{x+x_move, y+y_move};
    }
    // 2 FORWARD, 1 RIGHT
    x_move = 1;
    y_move = 2;
    if (checkXY(x+x_move, y+y_move) and game->getBlock(x+x_move,y+y_move)->getPiece()) {
        if (game->getBlock(x+x_move,y+y_move)->getPiece()->name == "at"
                and kingColor != game->getBlock(x+x_move,y+y_move)->getPiece()->getColor())
            return std::vector<int>{x+x_move, y+y_move};
    }
    // 2 FORWARD, 1 LEFT
    x_move = -1;
    y_move = 2;
    if (checkXY(x+x_move, y+y_move) and game->getBlock(x+x_move,y+y_move)->getPiece()) {
        if (game->getBlock(x+x_move,y+y_move)->getPiece()->name == "at"
                and kingColor != game->getBlock(x+x_move,y+y_move)->getPiece()->getColor())
            return std::vector<int>{x+x_move, y+y_move};
    }
    // 2 DOWNWARD, 1 RIGHT
    x_move = 1;
    y_move = -2;
    if (checkXY(x+x_move, y+y_move) and game->getBlock(x+x_move,y+y_move)->getPiece()) {
        if (game->getBlock(x+x_move,y+y_move)->getPiece()->name == "at"
                and kingColor != game->getBlock(x+x_move,y+y_move)->getPiece()->getColor())
            return std::vector<int>{x+x_move, y+y_move};
    }
    // 2 DOWNWARD, 1 LEFT
    x_move = -1;
    y_move = -2;
    if (checkXY(x+x_move, y+y_move) and game->getBlock(x+x_move,y+y_move)->getPiece()) {
        if (game->getBlock(x+x_move,y+y_move)->getPiece()->name == "at"
                and kingColor != game->getBlock(x+x_move,y+y_move)->getPiece()->getColor())
            return std::vector<int>{x+x_move, y+y_move};
    }
    return std::vector<int>{};
}

bool isCheckmate(King* king, Game* game) {
    /*
    isCheckmate():
    In case of the attacker is a queen, bishop, rook, or pawn:
    1. Find the possible escape blocks for the King.
        a) For every direction with radius 1, check whether the king is blocked by its own pieces.
        b) Count those with the pieces not colored in the King's color as escapable block.
        c) If there is an escapable block: return false;
        d) If not: continue;
    2. Find and locate the attacker using getAttacker() method in Game class.

    // In case of the attacker is a knight, skip the 3rd step.
    3. Check whether the path between the king and the attacker can be blocked.
        a) For every empty blocks between the king and the attacker,
        check in every direction whether there is a suitable piece that can block the path.
        b) If yes: return false;
        c) If not: continue;
    4. Check if the attacker can be eaten by a player's piece.
        a) Likewise in isCheck(), check in every direction if the attacker can be eaten by an appropriate piece.
        b) If yes: return false;
        c) If not: return true;
     */
    if(isEscapable(king, game)) return false;
    if(isBlockable(king, game)) return false;
    if(isAttackerEatable(game)) return false;
    return true;
}

bool isIn(const std::vector<int>& x, const std::vector<std::vector<int>>& v){
    for(auto& i: v){
        if(i == x) return true;
    }
    return false;
}

std::vector<Move> listMoves(std::vector<Piece*> pieces){
    int x, y;
    std::vector<Move> package;
    try {
        if (pieces.empty()) throw 500;
    }
    catch (int error) {
        std::cout << "[ERR: " << error << "] " << "std::vector<Piece*> pieces cannot be empty.\n";
    }
    auto game = pieces[0]->getGame();

    for(auto& piece : pieces){
        auto pieceCoord = piece->getBlock()->getCoordinates();
        x = pieceCoord[0], y = pieceCoord[1];
        switch (pieceMap[piece->name]) {
        case KNIGHT:
            // 1 FORWARD, 2 RIGHT
            x = pieceCoord[0] + 2, y = pieceCoord[1] + 1;
            if(checkMove_all(piece, game->getBlock(x, y)) == 0){
                package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
            }
            // 1 FORWARD, 2 LEFT
            x = pieceCoord[0] - 2, y = pieceCoord[1] + 1;
            if(checkMove_all(piece, game->getBlock(x, y)) == 0){
                package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
            }
            // 1 DOWNWARD, 2 RIGHT
            x = pieceCoord[0] + 2, y = pieceCoord[1] - 1;
            if(checkMove_all(piece, game->getBlock(x, y)) == 0){
                package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
            }
            // 1 DOWNWARD, 2 LEFT
            x = pieceCoord[0] - 2, y = pieceCoord[1] - 1;
            if(checkMove_all(piece, game->getBlock(x, y)) == 0){
                package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
            }
            // 2 FORWARD, 1 RIGHT
            x = pieceCoord[0] + 1, y = pieceCoord[1] + 2;
            if(checkMove_all(piece, game->getBlock(x, y)) == 0){
                package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
            }
            // 2 FORWARD, 1 LEFT
            x = pieceCoord[0] - 1, y = pieceCoord[1] + 2;
            if(checkMove_all(piece, game->getBlock(x, y)) == 0){
                package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
            }
            // 2 DOWNWARD, 1 RIGHT
            x = pieceCoord[0] + 1, y = pieceCoord[1] - 2;
            if(checkMove_all(piece, game->getBlock(x, y)) == 0){
                package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
            }
            // 2 DOWNWARD, 1 LEFT
            x = pieceCoord[0] - 1, y = pieceCoord[1] - 2;
            if(checkMove_all(piece, game->getBlock(x, y)) == 0){
                package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
            }
            break;
        case BISHOP:
            // FORWARD, RIGHT
            while (++x != 9 and ++y != 9) {
                if(checkMove_all(piece, game->getBlock(x, y)) == 0) {
                    package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
                }
                else break;
            }
            x = pieceCoord[0], y = pieceCoord[1];
            // FORWARD, LEFT
            while (--x != 0 and ++y != 9) {
                if(checkMove_all(piece, game->getBlock(x, y)) == 0) {
                    package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
                }
                else break;
            }
            x = pieceCoord[0], y = pieceCoord[1];
            // DOWNWARD, RIGHT
            while (++x != 9 and --y != 0) {
                if(checkMove_all(piece, game->getBlock(x, y)) == 0) {
                    package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
                }
                else break;
            }
            x = pieceCoord[0], y = pieceCoord[1];
            // DOWNWARD, LEFT
            while (--x != 0 and --y != 0) {
                if(checkMove_all(piece, game->getBlock(x, y)) == 0) {
                    package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
                }
                else break;
            }
            break;
        case ROOK:
            // FORWARD
            while (++y != 9){
                if(checkMove_all(piece, game->getBlock(x, y)) == 0) {
                    package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
                }
                else break;
            }
            y = pieceCoord[1];
            // DOWNWARD
            while (--y != 0) {
                if(checkMove_all(piece, game->getBlock(x, y)) == 0) {
                    package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
                }
                else break;
            }
            y = pieceCoord[1];
            // RIGHT
            while (++x != 9) {
                if(checkMove_all(piece, game->getBlock(x, y)) == 0) {
                    package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
                }
                else break;
            }
            x = pieceCoord[0];
            // LEFT
            while (--x != 0){
                if(checkMove_all(piece, game->getBlock(x, y)) == 0) {
                    package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
                }
                else break;
            }
            break;
        case QUEEN:
            // FORWARD, RIGHT
            while (++x != 9 and ++y != 9) {
                if(checkMove_all(piece, game->getBlock(x, y)) == 0) {
                    package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
                }
                else break;
            }
            x = pieceCoord[0], y = pieceCoord[1];
            // FORWARD, LEFT
            while (--x != 0 and ++y != 9) {
                if(checkMove_all(piece, game->getBlock(x, y)) == 0) {
                    package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
                }
                else break;
            }
            x = pieceCoord[0], y = pieceCoord[1];
            // DOWNWARD, RIGHT
            while (++x != 9 and --y != 0) {
                if(checkMove_all(piece, game->getBlock(x, y)) == 0) {
                    package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
                }
                else break;
            }
            x = pieceCoord[0], y = pieceCoord[1];
            // DOWNWARD, LEFT
            while (--x != 0 and --y != 0) {
                if(checkMove_all(piece, game->getBlock(x, y)) == 0) {
                    package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
                }
                else break;
            }
            x = pieceCoord[0], y = pieceCoord[1];
            // FORWARD
            while (++y != 9){
                if(checkMove_all(piece, game->getBlock(x, y)) == 0) {
                    package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
                }
                else break;
            }
            y = pieceCoord[1];
            // DOWNWARD
            while (--y != 0) {
                if(checkMove_all(piece, game->getBlock(x, y)) == 0) {
                    package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
                }
                else break;
            }
            y = pieceCoord[1];
            // RIGHT
            while (++x != 9) {
                if(checkMove_all(piece, game->getBlock(x, y)) == 0) {
                    package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
                }
                else break;
            }
            x = pieceCoord[0];
            // LEFT
            while (--x != 0){
                if(checkMove_all(piece, game->getBlock(x, y)) == 0) {
                    package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
                }
                else break;
            }
            break;
        case KING:
            // FORWARD, RIGHT
            x = pieceCoord[0] + 1, y = pieceCoord[1] + 1;
            if(checkMove_all(piece, game->getBlock(x, y)) == 0) {
                package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
            }
            // FORWARD, LEFT
            x = pieceCoord[0] - 1, y = pieceCoord[1] + 1;
            if(checkMove_all(piece, game->getBlock(x, y)) == 0) {
                package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
            }
            // DOWNWARD, RIGHT
            x = pieceCoord[0] + 1, y = pieceCoord[1] - 1;
            if(checkMove_all(piece, game->getBlock(x, y)) == 0) {
                package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
            }
            // DOWNWARD, LEFT
            x = pieceCoord[0] - 1, y = pieceCoord[1] - 1;
            if(checkMove_all(piece, game->getBlock(x, y)) == 0) {
                package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
            }
            // FORWARD
            x = pieceCoord[0], y = pieceCoord[1] + 1;
            if(checkMove_all(piece, game->getBlock(x, y)) == 0) {
                package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
            }
            // DOWNWARD
            y = pieceCoord[1] - 1;
            if(checkMove_all(piece, game->getBlock(x, y)) == 0) {
                package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
            }
            // RIGHT
            x = pieceCoord[0] + 1, y = pieceCoord[1];
            if(checkMove_all(piece, game->getBlock(x, y)) == 0) {
                package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
            }
            // LEFT
            x = pieceCoord[0] - 1;
            if(checkMove_all(piece, game->getBlock(x, y)) == 0) {
                package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
            }
            // RIGHT CASTLING
            x = pieceCoord[0] + 2;
            if(checkMove_all(piece, game->getBlock(x, y)) == 1)
                package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
            // LEFT CASTLING
            x = pieceCoord[0] - 2;
            if(checkMove_all(piece, game->getBlock(x, y)) == 1)
                package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
            break;
        case PAWN:
            // WHITE PAWN
            if (piece->getColor() == "w") {
                // FORWARD, RIGHT
                x = pieceCoord[0] + 1, y = pieceCoord[1] + 1;
                if(checkMove_all(piece, game->getBlock(x, y)) == 0) {
                    package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
                }
                // FORWARD, LEFT
                x = pieceCoord[0] - 1, y = pieceCoord[1] + 1;
                if(checkMove_all(piece, game->getBlock(x, y)) == 0) {
                    package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
                }
                // FORWARD
                x = pieceCoord[0], y = pieceCoord[1] + 1;
                if(checkMove_all(piece, game->getBlock(x, y)) == 0) {
                    package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
                }
                // FORWARD 2
                x = pieceCoord[0], y = pieceCoord[1] + 2;
                if(checkMove_all(piece, game->getBlock(x, y)) == 0) {
                    package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
                }
            }
            // BLACK PAWN
            else {
                // DOWNWARD, RIGHT
                x = pieceCoord[0] + 1, y = pieceCoord[1] - 1;
                if(checkMove_all(piece, game->getBlock(x, y)) == 0) {
                    package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
                }
                // DOWNWARD, LEFT
                x = pieceCoord[0] - 1, y = pieceCoord[1] - 1;
                if(checkMove_all(piece, game->getBlock(x, y)) == 0) {
                    package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
                }
                // DOWNWARD
                y = pieceCoord[1] - 1;
                if(checkMove_all(piece, game->getBlock(x, y)) == 0) {
                    package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
                }
                // DOWNWARD 2
                y = pieceCoord[1] - 2;
                if(checkMove_all(piece, game->getBlock(x, y)) == 0) {
                    package.push_back(Move{.target = game->getBlock(x, y), .piece = piece});
                }
            }
            break;
        }
    }
    return package;
}


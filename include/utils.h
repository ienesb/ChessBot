#ifndef CHESSBOT_UTILS_H
#define CHESSBOT_UTILS_H

#include <vector>
#include "game.h"

int checkMove_all(Piece* piece, Block* target);
std::vector<int> isCheck_Game(const std::string& kingColor, Game *game);
bool isCheckmate(King* king, Game* game);
bool checkCastling(King* king, Rook* rook, Game* game);
bool isIn(const std::vector<int>& x, const std::vector<std::vector<int>>& v);

#endif //CHESSBOT_UTILS_H

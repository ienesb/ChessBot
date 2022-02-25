#ifndef CHESSBOT_UTILS_H
#define CHESSBOT_UTILS_H

#include <vector>
#include "game.h"

bool isValid(std::vector<int>current, std::vector<int>target, int piece, Game *game);
bool isSame(std::vector<int>current, std::vector<int>target);
bool isBlocked(std::vector<int>current, std::vector<int>target, int piece, Game *game);
bool isSameColor(std::vector<int>current, std::vector<int>target, Game *game);
bool isCheck(std::vector<int>current, std::vector<int>target, Game *game);
int checkMove_all(Piece* piece, Block* target);
int checkMove_all(Piece* piece, int x, int y);
std::vector<int> isCheck_Game(const std::string& kingColor, Game *game);
bool isCheckmate(King* king, Game* game);

#endif //CHESSBOT_UTILS_H

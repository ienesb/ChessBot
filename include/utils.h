#ifndef CHESSBOT_UTILS_H
#define CHESSBOT_UTILS_H

#include <vector>
#include "game.h"

bool isValid(std::vector<int>current, std::vector<int>target, int piece, Game *game);
bool isSame(std::vector<int>current, std::vector<int>target);
bool isBlocked(std::vector<int>current, std::vector<int>target, int piece, Game *game);
bool isSameColor(std::vector<int>current, std::vector<int>target, Game *game);
bool isCheck(std::vector<int>current, std::vector<int>target, Game *game);

#endif //CHESSBOT_UTILS_H

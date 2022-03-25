#ifndef UTILS
#define UTILS

#include <vector>
#include "game.h"
#include "move.h"

int checkMove_all(Piece* piece, Block* target);
std::vector<int> isCheck_Game(const std::string& kingColor, Game *game);
bool isCheckmate(King* king, Game* game);
bool isIn(const std::vector<int>& x, const std::vector<std::vector<int>>& v);
std::vector<Move> listMoves(std::vector<Piece*> pieces);

#endif

#include "player.h"
#include "game.h"
#include "pieces.h"
#include "move.h"
#include "utils.h"

Player::Player(std::string color, Game* game, std::string type){
    this->color = color;
    this->game = game;
    this->type = type;
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


std::vector<Move> Player::listAllMoves(){
    return listMoves(this->getPieces());
}

Move Player::getBestMove(std::vector<Move> moves){
    Move bestMove;
    int result = 0;
    int prediction;
    std::string cmd;
    for(Move m: moves){
        cmd = "python inference.py";
        prediction = this->exec(cmd.c_str());
        if(prediction > result){
            result = prediction;
            bestMove = m;
        }
    }
    return bestMove;
}

std::string Player::encode(Move move){
    this->game->performMovement(move);
    std::string result = getBinaryBoard();
    this->game->undoLastMove();
    return result;
}

int Player::exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return atoi(result.c_str());
}

std::string Player::getBinaryBoard(){
    Block* block;
    Piece* piece;
    char* c = (char*) malloc(sizeof(char)*12*64);

    for(int i = 0; i < 12*64; i++){
        c[i] = '0';
    }

    for(int x = 1; x <= 8; x++){
        for(int y = 1; y <= 8; y++){

            block = this->game->getBlock(y, x);
            piece = block->getPiece();

            if(piece == nullptr){
                continue;
            }
            else if (piece->getColor() == "w"){
                if(piece->name == "piyon"){
                    c[((x-1)*8+y-1)+64*0] = '1';
                }
                else if(piece->name == "at"){
                    c[((x-1)*8+y-1)+64*1] = '1';
                }
                else if(piece->name == "fil"){
                    c[((x-1)*8+y-1)+64*2] = '1';
                }
                else if(piece->name == "kale"){
                    c[((x-1)*8+y-1)+64*3] = '1';
                }
                else if(piece->name == "vezir"){
                    c[((x-1)*8+y-1)+64*4] = '1';
                }
                else if(piece->name == "sah"){
                    c[((x-1)*8+y-1)+64*5] = '1';
                }   
            }

            else if (piece->getColor() == "b"){
                if(piece->name == "piyon"){
                    c[((x-1)*8+y-1)+64*6] = '1';
                }
                else if(piece->name == "at"){
                    c[((x-1)*8+y-1)+64*7] = '1';
                }
                else if(piece->name == "fil"){
                    c[((x-1)*8+y-1)+64*8] = '1';
                }
                else if(piece->name == "kale"){
                    c[((x-1)*8+y-1)+64*9] = '1';
                }
                else if(piece->name == "vezir"){
                    c[((x-1)*8+y-1)+64*10] = '1';
                }
                else if(piece->name == "sah"){
                    c[((x-1)*8+y-1)+64*11] = '1';
                }   
            }
        } 
    }
    std::string result(c);
    return result;
}
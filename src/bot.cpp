#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

#include "bot.h"
#include "move.h"
#include "utils.h"

Bot::Bot(std::string color, Game* game, std::string modelPath):Player::Player(color, game){

}

std::vector<Move> Bot::listAllMoves(){
    return listMoves(this->getPieces());
}

Move Bot::getBestMove(std::vector<Move> moves){
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

std::string Bot::encode(Move move){
    this->game->performMovement(move);
    std::string result = getBinaryBoard();
    this->game->undoLastMove();
    return result;
}

int Bot::exec(const char* cmd) {
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

std::string Bot::getBinaryBoard(){
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
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <bits/stdc++.h>

#include "game.h"
#include "ui.h"
#include "pieces.h"
#include "block.h"
 
using std::filesystem::directory_iterator;

void performMovement(Game* game, std::string side, std::string pieceName, int targetX, int targetY){
    Block* block;
    Block* targetBlock;
    Piece* piece;
    if(targetX == 0 && targetY == 0){
        King* king;
        king = game->getKing(side);
        block = king->getBlock();
        if(side == "w"){
            targetY = 1;
        }
        else{
            targetY = 8;
        }
        for(int x: {3,7}){
            targetBlock = game->getBlock(x, targetY);
            int code = king->checkMove(targetBlock);
            if(code == 1){
                game->performCastling(king, targetBlock);
                return;
            }
        }
    }
    targetBlock = game->getBlock(targetX, targetY);
    for(int x = 1; x <= 8; x++){
        for(int y = 1; y <= 8; y++){
            block = game->getBlock(x, y); 
            piece = block->getPiece();
            if(piece != nullptr && piece->getColor() == side && piece->name == pieceName && piece->checkMove(targetBlock) == 0){
                game->performMovement(piece, targetBlock);
                return;
            }
        }
    }
}

void parseNotation(std::string n){    
}

void getBinaryBoard(Game* game, char* c){
    Block* block;
    Piece* piece;

    for(int i = 0; i < 12*64; i++){
        c[i] = '0';
    }

    for(int x = 1; x <= 8; x++){
        for(int y = 1; y <= 8; y++){

            block = game->getBlock(y, x);
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
}

std::vector<std::string> simple_tokenizer(std::string s){
    std::stringstream ss(s);
    std::string word;
    std::vector<std::string> data;
    while (ss >> word) {
        data.push_back(word);
    }
    return data;
}


int main(int argc, char *argv[]){
    
    QApplication app(argc, argv);
    QMainWindow mainWindow;
    
    Game* game;
    char* c;
    c = (char*) malloc(sizeof(char)*12*64);
    GameUi ui;
    int i, targetX, targetY;
    std::string path = "../ai/games/", text, pieceName, turn, inputData, outputData;
    std::vector<std::string> data;
    std::ofstream writefile("data.txt");

    for (const auto & file : directory_iterator(path)){
        std::cout << file.path() << std::endl;
        std::ifstream readfile(file.path());   
        
        ui.setupUi(&mainWindow);
        
        i = 0;
        while (getline (readfile, text)) {
            data = simple_tokenizer(text);

            if(data[0] == "P"){
                pieceName = "piyon";
            }
            else if(data[0] == "N"){
                pieceName = "at";
            }
            else if(data[0] == "B"){
                pieceName = "fil";
            }
            else if(data[0] == "R"){
                pieceName = "kale";
            }
            else if(data[0] == "Q"){
                pieceName = "vezir";
            }
            else if(data[0] == "K"){
                pieceName = "sah";
            }

            targetX = stoi(data[1]);
            targetY = stoi(data[2]);
            if(i%2==0){
                turn = "w";
            }
            else{
                turn = "b";
            }
            performMovement(ui.game, turn, pieceName, targetX, targetY);
            getBinaryBoard(ui.game, c);
            inputData.assign(c, 12*64);
            outputData = data[4];
            writefile << inputData << ", ";
            writefile << outputData << "\n";
            i++;
        }
    }

    writefile.close();
    return 0;
}
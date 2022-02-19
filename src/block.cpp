#include <QtWidgets/QLabel>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <vector>

#include "game.h"
#include "block.h"
#include "pieces.h"

void Block::mousePressEvent(QMouseEvent *ev){
    this->game->press(this);
}

Block::Block(QDialog *dialog, Game* game, int x, int y):QLabel::QLabel(dialog){
    this->game = game;
    this->x = x;
    this->y = y;
    this->piece = nullptr;
    if((x+y)%2 == 0){
        this->path = "pngs/base/black.png";
    }
    else{
        this->path = "pngs/base/white.png";
    }
    
           
}

Block::Block(QDialog *dialog, Game* game, int x, int y, Piece* piece):QLabel::QLabel(dialog){
    this->game = game;
    this->x = x;
    this->y = y;
    this->piece = piece;
    if((x+y)%2 == 0){
        this->path = "pngs/base/black.png";
    }
    else{
        this->path = "pngs/base/white.png";
    }
           
}

void Block::setPiece(Piece* piece){
    this->piece = piece;
}

Piece* Block::getPiece(){
    return piece;
}

std::vector<int> Block::getCoordinates(){
    std::vector<int> coordinates{x,y};
    return coordinates;
}

std::string Block::getColor(){
    return color;
}

void Block::update(){
    if(this->piece == nullptr){
        if(this->isClicked){
            QPixmap image(Block.clickedPath);
        }
        else{
            QPixmap image(this->path);
        }
    }
    else{
        Mat baseImage, pieceImage;
        if(this->isClicked){
            baseImage = imread(Block.clickedPath ,1);
        }
        else{
            baseImage = imread(this->path ,1);
        }

        pieceImage = imread(this->piece->path ,1);
        
        if(this->piece->color == "w"){
            baseImage.setTo(255, pieceImage==255);
        }
        else{
            baseImage.setTo(0, pieceImage==255);
        }
        
        imwrite(".temppng.png", baseImage);
        QPixmap image(".temppng.png");

    }
    this->setPixmap(image);
}

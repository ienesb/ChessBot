#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <QMouseEvent>
#include <QPixmap>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <sstream>
#include <vector>

#include "game.h"
#include "block.h"
#include "pieces.h"


void Block::mousePressEvent(QMouseEvent *ev){
    this->game->press(this);
}

Block::Block(QWidget* widget, Game* game, int x, int y):QLabel::QLabel(widget){
    this->game = game;
    this->x = x;
    this->y = y;
    this->piece = nullptr;
    this->isClicked = false;
    
    if((x+y)%2 == 0){
        this->path = "../pngs/base/black.png";
    }
    else{
        this->path = "../pngs/base/white.png";
    }
    this->clickedPath = "../pngs/base/red.png";
    
    this->setGeometry(QRect((x-1)*SIZE, (8-y)*SIZE, SIZE, SIZE));

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
    QPixmap* image;
    if(this->piece == nullptr){
        if(this->isClicked){
            image = new QPixmap(this->clickedPath.c_str());
        }
        else{
            image = new QPixmap(this->path.c_str());
        }
    }
    else{
        cv::Mat baseImage, pieceImage;
        if(this->isClicked){
            baseImage = cv::imread(this->clickedPath ,1);
        }
        else{
            baseImage = cv::imread(this->path ,1);
        }

        pieceImage = cv::imread(this->piece->path ,1);
        
        if(this->piece->getColor() == "w"){
            baseImage.setTo(255, pieceImage==255);
        }
        else{
            baseImage.setTo(0, pieceImage==255);
        }

        cv::resize(baseImage, baseImage, cv::Size(SIZE, SIZE), cv::INTER_LINEAR);

        cv::imwrite(".temppng.png", baseImage);
        image = new QPixmap(".temppng.png");

    }
    this->setPixmap(*image);
}

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
    
    this->whitePath = "../pngs/base/white.png";
    this->whiteImage = cv::imread("../pngs/base/white.png", 1); 
    this->blackPath = "../pngs/base/black.png";
    this->blackImage = cv::imread("../pngs/base/black.png", 1);
    this->clickedPath = "../pngs/base/red.png";
    this->clickedImage = cv::imread("../pngs/base/red.png", 1);

    this->name = std::to_string(x) + "-" + std::to_string(y) + ".png";

    if ((x+y)%2 == 0){
        this->color = "b";
    }
    else{
        this->color = "w";
    }
    
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
        else if(this->color == "w"){
            image = new QPixmap(this->whitePath.c_str());
        }
        else{
            image = new QPixmap(this->blackPath.c_str());
        }
    }
    else{
        cv::Mat baseImage, pieceImage;
        if(this->isClicked){
            baseImage = this->clickedImage;
        }
        else if(this->color == "w"){
            baseImage = this->whiteImage;
        }
        else{
            baseImage = this->blackImage;
        }

        // pieceImage = cv::imread(this->piece->path ,1);
        if(this->piece->name == "kale"){
            if(this->piece->getColor() == "w"){
                baseImage.setTo(255, cv::imread("../pngs/pieces/kale.png", 1)==255);
            }
            else{
                baseImage.setTo(0, cv::imread("../pngs/pieces/kale.png", 1)==255);
            }
        }
        else if(this->piece->name == "piyon"){
            if(this->piece->getColor() == "w"){
                baseImage.setTo(255, cv::imread("../pngs/pieces/piyon.png", 1)==255);
            }
            else{
                baseImage.setTo(0, cv::imread("../pngs/pieces/piyon.png", 1)==255);
            }
        }
        else{
            if(this->piece->getColor() == "w"){
                baseImage.setTo(255, this->piece->image==255);
            }
            else{
                baseImage.setTo(0, this->piece->image==255);
            }

        }
        
        
        cv::resize(baseImage, baseImage, cv::Size(SIZE, SIZE), cv::INTER_LINEAR);

        cv::imwrite(name, baseImage);
        image = new QPixmap(name.c_str());

    }
    this->setPixmap(*image);
}

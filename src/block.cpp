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
    this->blackPath = "../pngs/base/black.png";
    this->clickedPath = "../pngs/base/red.png";

    this->name = std::to_string(x) + "-" + std::to_string(y) + ".png";

    if ((x+y)%2 == 0){
        this->color = "b";
    }
    else{
        this->color = "w";
    }
    
    this->setGeometry(QRect((x-1)*SIZE, (8-y)*SIZE, SIZE, SIZE));

}

Block::~Block(){
    remove(name.c_str());
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
        cv::Mat baseImage;

        if(this->isClicked){
            baseImage = cv::imread(this->clickedPath, 1);
        }
        else if(this->color == "w"){
            baseImage = cv::imread(this->whitePath, 1);
        }
        else{
            baseImage = cv::imread(this->blackPath, 1);
        }
        
        if(this->piece->getColor() == "w"){
            baseImage.setTo(255, this->piece->image==255);
        }
        else{
            baseImage.setTo(0, this->piece->image==255);
        }

        cv::resize(baseImage, baseImage, cv::Size(SIZE, SIZE), cv::INTER_LINEAR);

        cv::imwrite(name, baseImage);
        image = new QPixmap(name.c_str());

    }
    this->setPixmap(*image);
}

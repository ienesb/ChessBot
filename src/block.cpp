#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
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
        this->path = "pngs/base/black.png";
    }
    else{
        this->path = "pngs/base/white.png";
    }
    this->clickedPath = "pngs/base/red.png";
    
    // std::stringstream ss;  
    // std::string strX, strY;
    // ss << x;  
    // ss >> strX;  
    // ss << y;  
    // ss >> strY; 

    // this->setObjectName(QString::fromUtf8(strX + "-" + strY));
    this->setGeometry(QRect(x*20, (8-y)*20, 20, 20));

}

Block::Block(QWidget* widget, Game* game, int x, int y, Piece* piece):QLabel::QLabel(widget){
    this->game = game;
    this->x = x;
    this->y = y;
    this->piece = piece;
    this->isClicked = false;

    if((x+y)%2 == 0){
        this->path = "pngs/base/black.png";
    }
    else{
        this->path = "pngs/base/white.png";
    }
    this->clickedPath = "pngs/base/red.png";

    // std::stringstream ss;  
    // std::string strX, strY;
    // ss >> strX;  
    // ss << y;  
    // ss >> strY; 

    // this->setObjectName(QString::fromUtf8(strX + "-" + strY));
    this->setGeometry(QRect(x*20, (8-y)*20, 20, 20));
           
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
    std::cout << this->clickedPath << "\n";
    if(this->piece == nullptr){
        if(this->isClicked){
            QPixmap image(*clickedPath);
        }
        else{
            QPixmap image(this->path);
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
        
        cv::imwrite(".temppng.png", baseImage);
        QPixmap image(".temppng.png");

    }
    this->setPixmap(image);
}

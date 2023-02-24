#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <QMouseEvent>
#include <QPixmap>

#include <iostream>
#include <sstream>
#include <vector>

#include "block.h"
#include "pieces.h"
#include "game.h"


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

    if(this->isClicked){
        image = new QPixmap(this->clickedPath.c_str());
    }
    else if(this->color == "w"){
        image = new QPixmap(this->whitePath.c_str());
    }
    else{
        image = new QPixmap(this->blackPath.c_str());
    }
    
    if(this->piece != nullptr){
        
        QRgb rgb = QColor("black").rgb();
        QPixmap mask = QPixmap::fromImage(this->piece->image.createMaskFromColor(rgb));
        QPainter p(image);
        p.setClipRegion(QRegion(mask));
        p.setBrush(this->piece->getQColor());
        p.drawEllipse(0, 0, 200, 200);  
    }
    this->setPixmap((*image).scaled(SIZE, SIZE));
}

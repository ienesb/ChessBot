#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <QMouseEvent>
#include <QPixmap>

#include <iostream>
#include <vector>
#include <string>

#include "button.h"

void Button::mousePressEvent(QMouseEvent *ev){

}

Button::Button(QWidget* widget, QMainWindow* mainWindow, QApplication* app, std::string type):QLabel::QLabel(widget){
    this->app = app;
    this->mainWindow = mainWindow;
    this->type = type;
}

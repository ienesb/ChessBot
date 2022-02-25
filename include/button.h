#ifndef BUTTON
#define BUTTON

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

class Button : public QLabel{
    public:
    QApplication* app;
    QMainWindow* mainWindow;
    std::string type;
    void mousePressEvent(QMouseEvent *ev);
    Button(QWidget* widget,QMainWindow* mainWindow, QApplication* app, std::string type);

};

#endif
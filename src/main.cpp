#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

#include <iostream>

#include "block.h"
#include "pieces.h"
#include "ui.h"
#include "game.h"
#include "mainUi.h"
#include "main.h"

void startMenu(QMainWindow* mainWindow, QApplication* app){
    Window ui;
    ui.setupUi(mainWindow, app);
    mainWindow->show();
}

void startGame(QMainWindow* mainWindow, QApplication* app, int numberOfPlayers){
    GameUi ui;
    ui.setupUi(mainWindow, numberOfPlayers);
    mainWindow->show();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow mainWindow;

    startMenu(&mainWindow, &app);
    
    return app.exec();
}
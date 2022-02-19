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

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow mainWindow;
    GameUi ui;
    ui.setupUi(&mainWindow);

    mainWindow.show();
    return app.exec();
}
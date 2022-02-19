#ifndef UI
#define UI 

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <QMouseEvent>
#include <QPixmap>

#include "game.h"

class GameUi{
    public:
    Game* game;
    QWidget *centralwidget;
    QLabel *label;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow);
    void retranslateUi(QMainWindow *MainWindow);

};

#endif
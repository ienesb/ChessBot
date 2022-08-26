#ifndef MAINUI
#define MAINUI

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <QMouseEvent>
#include <QPixmap>

#include "button.h"

class Window{
public:
    QWidget* centralwidget;
    QLabel* base;
    Button* coop;
    Button* singleplayer;
    Button* multiplayer;
    Button* exit;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow, QApplication *app);
    void retranslateUi(QMainWindow *MainWindow);
};

#endif
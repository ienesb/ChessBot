#ifndef UI
#define UI 

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QMouseEvent>
#include <QPixmap>
#include <QtWidgets/QGridLayout>


class MainWindow;

#include "game.h"

class GameUi{
    public:
    Game* game;
    QWidget *centralwidget;
    QLabel *label;
    QStatusBar *statusbar;
    QGridLayout *gridLayout;
    QGridLayout *gridLayoutCentral;

    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_8;

    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *verticalSpacer_7;
    QSpacerItem *verticalSpacer_8;

    QPushButton *bt_back_game;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;

    Game* setupUi(MainWindow *MainWindow, int gameMode);
//    void retranslateUi(QMainWindow *MainWindow);

};

#endif

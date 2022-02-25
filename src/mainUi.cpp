#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <QMouseEvent>
#include <QPixmap>

#include <iostream>
#include <string>

#include "mainUi.h"
#include "button.h" 


void Window::setupUi(QMainWindow *MainWindow, QApplication *app){
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(400, 300);
    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    base = new QLabel(centralwidget);
    base->setObjectName(QString::fromUtf8("base"));
    base->setGeometry(QRect(0, 0, 400, 300));
    player1 = new Button(centralwidget, MainWindow, app, "player1");
    player1->setObjectName(QString::fromUtf8("player1"));
    player1->setGeometry(QRect(170, 110, 58, 18));
    player2 = new Button(centralwidget, MainWindow, app, "player2");
    player2->setObjectName(QString::fromUtf8("player2"));
    player2->setGeometry(QRect(170, 170, 58, 18));
    exit = new Button(centralwidget, MainWindow, app, "exit");
    exit->setObjectName(QString::fromUtf8("exit"));
    exit->setGeometry(QRect(170, 220, 58, 18));
    MainWindow->setCentralWidget(centralwidget);
    statusbar = new QStatusBar(MainWindow);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    MainWindow->setStatusBar(statusbar);


    retranslateUi(MainWindow);

    QMetaObject::connectSlotsByName(MainWindow);
} // setupUi

void Window::retranslateUi(QMainWindow *MainWindow){
    MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
    std::string baseName{"../pngs/mainmenu/base.png"};
    std::string player1Name{"../pngs/mainmenu/player1.png"};
    std::string player2Name{"../pngs/mainmenu/player2.png"};
    std::string exitName{"../pngs/mainmenu/exit.png"};
    
    QPixmap* baseImage;
    QPixmap* player1Image;
    QPixmap* player2Image;
    QPixmap* exitImage;

    baseImage = new QPixmap(baseName.c_str());
    player1Image = new QPixmap(player1Name.c_str());
    player2Image = new QPixmap(player2Name.c_str());
    exitImage = new QPixmap(exitName.c_str());
    
    base->setPixmap(*baseImage);
    player1->setPixmap(*player1Image);
    player2->setPixmap(*player2Image);
    exit->setPixmap(*exitImage);
} // retranslateUi

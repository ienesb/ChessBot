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
    
    coop = new Button(centralwidget, MainWindow, app, "coop");
    coop->setObjectName(QString::fromUtf8("coop"));
    coop->setGeometry(QRect(100, 30, 208, 50));

    singleplayer = new Button(centralwidget, MainWindow, app, "singleplayer");
    singleplayer->setObjectName(QString::fromUtf8("singleplayer"));
    singleplayer->setGeometry(QRect(100, 90, 208, 50));

    multiplayer = new Button(centralwidget, MainWindow, app, "multiplayer");
    multiplayer->setObjectName(QString::fromUtf8("multiplayer"));
    multiplayer->setGeometry(QRect(100, 150, 208, 50));

    exit = new Button(centralwidget, MainWindow, app, "exit");
    exit->setObjectName(QString::fromUtf8("exit"));
    exit->setGeometry(QRect(100, 210, 208, 50));

    
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
    std::string coopName{"../pngs/mainmenu/co-op.png"};
    std::string singleplayerName{"../pngs/mainmenu/singleplayer.png"};
    std::string multiplayerName{"../pngs/mainmenu/multiplayer.png"};
    std::string exitName{"../pngs/mainmenu/exit.png"};
    
    QPixmap* baseImage;
    QPixmap* coopImage;
    QPixmap* singleplayerImage;
    QPixmap* multiplayerImage;
    QPixmap* exitImage;

    baseImage = new QPixmap(baseName.c_str());
    coopImage = new QPixmap(coopName.c_str());
    singleplayerImage = new QPixmap(singleplayerName.c_str());
    multiplayerImage = new QPixmap(multiplayerName.c_str());
    exitImage = new QPixmap(exitName.c_str());
    
    base->setPixmap(*baseImage);
    coop->setPixmap(*coopImage);
    multiplayer->setPixmap(*singleplayerImage);
    singleplayer->setPixmap(*multiplayerImage);
    exit->setPixmap(*exitImage);
} // retranslateUi

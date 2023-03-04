//#include <QtCore/QVariant>
//#include <QtWidgets/QApplication>
//#include <QtWidgets/QLabel>
//#include <QtWidgets/QMainWindow>
//#include <QtWidgets/QGridLayout>
//#include <QtWidgets/QPushButton>
//#include <QtWidgets/QSpacerItem>
//#include <QtWidgets/QStatusBar>
//#include <QtWidgets/QWidget>
//#include <QMouseEvent>
//#include <QPixmap>

#include "game.h"
#include "ui.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"

Game* GameUi::setupUi(MainWindow *MainWindow, int gameMode){
//    if (MainWindow->objectName().isEmpty())
//        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
//    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
//    MainWindow->resize(SIZE*8+50, SIZE*8+50);
//    MainWindow->setSizePolicy(sizePolicy);
//    MainWindow->setMinimumSize(QSize(SIZE*8+50+100, SIZE*8+50));
//    MainWindow->setWindowTitle(QString::fromUtf8("ChessBot"));
//    QIcon icon;
//    QString iconThemeName = QString::fromUtf8("applications-games");
//    if (QIcon::hasThemeIcon(iconThemeName)) {
//        icon = QIcon::fromTheme(iconThemeName);
//    }
//    else {
//        icon.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
//    }
//    centralwidget = new QWidget(MainWindow);
//    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));

    MainWindow->ui->stackedWidget->removeWidget(MainWindow->game_w);
    delete MainWindow->game_w;
    MainWindow->game_w = new QWidget();
    MainWindow->ui->stackedWidget->addWidget(MainWindow->game_w);
    QWidget* game_widget = MainWindow->game_w;
    gridLayout = new QGridLayout();
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    gridLayout->setVerticalSpacing(0);
    gridLayout->setHorizontalSpacing(0);

    this->game = new Game(game_widget, gameMode, gridLayout, MainWindow);

    QSizePolicy sizePolicy_bt(QSizePolicy::Expanding, QSizePolicy::Expanding);
    bt_back_game = new QPushButton(game_widget);
    bt_back_game->setObjectName(QString::fromUtf8("bt_back_game"));
    sizePolicy_bt.setHeightForWidth(bt_back_game->sizePolicy().hasHeightForWidth());
    bt_back_game->setText("Back");
    bt_back_game->setSizePolicy(sizePolicy_bt);
    bt_back_game->setMinimumSize(QSize(90, 30));
    bt_back_game->setStyleSheet(QString::fromUtf8("background-color: rgb(154, 153, 150); color: white; "));
    QObject::connect(bt_back_game, &QPushButton::clicked, MainWindow, &MainWindow::bt_back_game_clicked);

    verticalSpacer_7 = new QSpacerItem(20, 289, QSizePolicy::Minimum, QSizePolicy::Expanding);
    verticalSpacer_8 = new QSpacerItem(20, 289, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout = new QVBoxLayout();
    verticalLayout->setSpacing(15);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    verticalLayout->addItem(verticalSpacer_7);
    verticalLayout->addWidget(bt_back_game);
    verticalLayout->addItem(verticalSpacer_8);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setSpacing(20);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    horizontalLayout->addLayout(gridLayout);
    horizontalLayout->addLayout(verticalLayout);

    delete game_widget->layout();
    gridLayoutCentral = new QGridLayout(game_widget);
    gridLayoutCentral->setObjectName(QString::fromUtf8("gridLayoutCentral"));

    horizontalSpacer_8 = new QSpacerItem(119, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    gridLayoutCentral->addItem(horizontalSpacer_8, 1, 2, 1, 1);
    verticalSpacer_5 = new QSpacerItem(20, 139, QSizePolicy::Minimum, QSizePolicy::Expanding);
    gridLayoutCentral->addItem(verticalSpacer_5, 0, 1, 1, 1);
    verticalSpacer_6 = new QSpacerItem(20, 139, QSizePolicy::Minimum, QSizePolicy::Expanding);
    gridLayoutCentral->addItem(verticalSpacer_6, 2, 1, 1, 1);
    horizontalSpacer_7 = new QSpacerItem(119, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    gridLayoutCentral->addItem(horizontalSpacer_7, 1, 0, 1, 1);
    gridLayoutCentral->addLayout(horizontalLayout, 1, 1, 1, 1);
    
    MainWindow->ui->stackedWidget->setCurrentWidget(game_widget);
//    MainWindow->setCentralWidget(centralwidget);
//    statusbar = new QStatusBar(MainWindow);
//    statusbar->setObjectName(QString::fromUtf8("statusbar"));
//    MainWindow->setStatusBar(statusbar);

//    retranslateUi(MainWindow);

    //QMetaObject::connectSlotsByName(MainWindow);

    return this->game;
} // setupUi

//void GameUi::retranslateUi(QMainWindow *MainWindow){
//    //MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
//} // retranslateUi

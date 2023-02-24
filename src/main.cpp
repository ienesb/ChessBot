#include "mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QObject::connect(&w, &MainWindow::quit_app, &a, &QApplication::quit);
    return a.exec();
}

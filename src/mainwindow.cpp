#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ui.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bt_single_clicked()
{

}


void MainWindow::on_bt_exit_clicked()
{
    emit this->quit_app();
}


void MainWindow::on_bt_local_clicked()
{
    GameUi ui;
    ui.setupUi(this, 2);
    this->show();
}

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ui.h"
#include "server.h"
#include "client.h"
#include <QMovie>
#include <QClipboard>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
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
    ui.setupUi(this, 1);
    this->show();
}


void MainWindow::on_bt_online_clicked()
{
    // Go to online page
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_bt_back_online_clicked()
{
    // Go to main page
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_bt_host_clicked()
{
    // Go to host page
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_bt_back_host_clicked()
{
    // Go to online page
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_bt_start_server_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    Server* server = new Server(ui->line_host_port->text());
    QString ngrok_command = "ngrok tcp " +
            QString::number(server->get_server_port());
    ui->label_server_port->setText(ngrok_command);
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(ngrok_command);
    QMovie *movie = new QMovie("../pngs/Loading_icon.gif");
    movie->setScaledSize(QSize(50,50));
    ui->label_load->setMovie(movie);
    ui->label_load->show();
    movie->start();
}


void MainWindow::on_bt_join_clicked()
{
    // Go to join page
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_bt_back_join_clicked()
{
    // Go to online page
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_bt_join_server_clicked()
{
    QString str_port = ui->line_join_port->text();
    quint16 server_port = str_port.toUShort();
    Client* client = new Client(ui->line_join_add->text(),
                                server_port);
    client->doConnect();
}


#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ui.h"
#include <QMovie>
#include <QClipboard>
#include <QTextCodec>
#include <QAbstractSocket>


void delay(int msec = 150)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Setting default widget to show up first
    ui->stackedWidget->setCurrentIndex(0);
    client = new Client(this);
    server = new Server(this);
    game_w = new QWidget();
    game = nullptr;
    isDataCame = false;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete client;
    delete server;
    delete game;
}

void MainWindow::start_server_game()
{
    GameUi ui;
    gameMode = 2;
    game = ui.setupUi(this, gameMode);
//    this->show();
    online_game_loop(server->get_socket());
}

void MainWindow::online_game_loop(QTcpSocket* socket)
{
    socket->setReadBufferSize(7);
    QString str_send_data;
    std::vector<int> data{};
    std::vector<int>& coord = game->move_coord;
    exit_game_loop = false;

    while (!exit_game_loop)
    {
        if(isDataCame)
        {
            if(socket->isReadable()){
                QByteArray raw_data = socket->readAll();
                QString str_read_data = QTextCodec::codecForName("UTF-8")->
                        toUnicode(raw_data);

                if(str_send_data != str_read_data && raw_data.size() == 7){
                    qDebug() << "send message:" << str_read_data;


                    foreach(QString data_loop, str_read_data.split(";"))
                    {
                        data.push_back(data_loop.toInt());
                    }

                    game->setChosen(game->getBlock(
                                        data[0], data[1]));
                    game->press(game->getBlock(
                                    data[2], data[3]));
                    data.clear();
                    isDataCame = false;
                    str_send_data = str_read_data;
                }
            }
        }
        else if(game->move_done)
        {

            str_send_data = "";
            for(auto& i: coord){
                str_send_data = str_send_data + QString::number(i) + ";";
            }
            str_send_data.chop(1);

            QByteArray message;
            message.prepend(str_send_data.toUtf8());
            message.resize(7);

            qDebug() << "send message:" << message;

            socket->write(message);
            socket->flush();
            game->move_done = false;
        }
        delay();
    }
    bt_back_game_clicked();
}

void MainWindow::start_client_game()
{
    GameUi ui;
    gameMode = 3;
    game = ui.setupUi(this, gameMode);
//    this->show();
    online_game_loop(client->get_socket());
}

void MainWindow::on_bt_single_clicked()
{
    GameUi ui;
    gameMode = 0;
    game = ui.setupUi(this, gameMode);
//    this->show();
}


void MainWindow::on_bt_exit_clicked()
{
    emit this->quit_app();
}


void MainWindow::on_bt_local_clicked()
{
    GameUi ui;
    gameMode = 1;
    game = ui.setupUi(this, gameMode);
//    this->show();
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

    server->listen(ui->line_host_port->text().toUShort());

    QString ngrok_command = "ngrok tcp " +
            QString::number(server->get_server_port());
    ui->label_server_port->setText(ngrok_command);

    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(ngrok_command);

    QMovie *movie = new QMovie(":/pngs/Loading_icon.gif");
    movie->setScaledSize(QSize(50,50));
    ui->label_load->setMovie(movie);
    ui->label_load->show();
    movie->start();
}

void MainWindow::on_bt_back_host_wait_clicked()
{
    // Go to host page
    server->get_server()->close();
    ui->stackedWidget->setCurrentIndex(2);
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
    client->host_addr = ui->line_join_add->text();
    client->host_port = ui->line_join_port->text().toUShort();

    ui->stackedWidget->setCurrentIndex(5);

    QMovie *movie = new QMovie(":/pngs/Loading_icon.gif");
    movie->setScaledSize(QSize(50,50));
    ui->label_join_load->setMovie(movie);
    ui->label_join_load->show();
    movie->start();

    client->doConnect();
}

void MainWindow::on_bt_back_join_wait_clicked()
{
    // Go to join page
    ui->stackedWidget->setCurrentIndex(4);
    client->get_socket()->close();
}

void MainWindow::bt_back_game_clicked(){
    if(gameMode == 2){
        if(server->get_socket()->state() == QAbstractSocket::ConnectedState){
            server->get_socket()->close();
        }

    }
    else if(gameMode == 3){
        if(client->get_socket()->state() == QAbstractSocket::ConnectedState){
            client->get_socket()->close();
        }
    }
    ui->stackedWidget->setCurrentIndex(0);
}





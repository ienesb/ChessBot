#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ui.h"
#include <QMovie>
#include <QClipboard>
#include <QTextCodec>

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
    game = ui.setupUi(this, 2);
    this->show();
    online_game_loop(server->get_socket());
}

void MainWindow::online_game_loop(QTcpSocket* socket)
{
    socket->setReadBufferSize(7);
    QString str_data;
    QString data_loop;
    std::vector<int> data{};
    std::vector<int>& coord = game->move_coord;
    while (true)
    {
        if(isDataCame)
        {

            QByteArray raw_data = socket->readAll();
            QString str = QTextCodec::codecForName("UTF-8")->
                    toUnicode(raw_data);
//            QByteArray buffer;
//            QDataStream socketStream(socket);
//            socketStream.setVersion(QDataStream::Qt_5_15);

//            socketStream.startTransaction();
//            socketStream >> buffer;
//            if(!socketStream.commitTransaction())
//            {
//                QString sss = QString("%1 :: Waiting for more data to come..").arg(socket->socketDescriptor());
//                return;
//            }

//            // QString header = buffer.mid(0);
//            // QString str_data = header.split(",")[0].split(":")[1];

            if(str_data != str && raw_data.size() == 7){
            qDebug() << "send message:" << str;

            foreach(data_loop, str.split(";"))
            {
                data.push_back(data_loop.toInt());
            }

            game->setChosen(game->getBlock(
                                data[0], data[1]));
            game->press(game->getBlock(
                                data[2], data[3]));
            data.clear();
            isDataCame = false;
            str_data = str;
            }

        }
        else if(game->move_done)
        {

            str_data = "";
            for(auto& i: coord){
                str_data = str_data + QString::number(i) + ";";
            }
            str_data.chop(1);
//            QDataStream socketStream(socket);
//            socketStream.setVersion(QDataStream::Qt_5_15);

            QByteArray message;
            message.prepend(str_data.toUtf8());
            message.resize(7);
            qDebug() << "send message:" << message;

//            QByteArray byteArray = str.toUtf8();
//            byteArray.prepend(header);

            //socketStream.setVersion(QDataStream::Qt_5_15);
            //socketStream << message;
            socket->write(message);
            socket->flush();
//            socket->write(str_data.toUtf8());
//            socket->flush();
//            socket->waitForBytesWritten(3000);
//            socket->close();
            game->move_done = false;
        }
        delay();
    }

}

void MainWindow::start_client_game()
{
    GameUi ui;
    game = ui.setupUi(this, 3);
    this->show();
    online_game_loop(client->get_socket());
}


//void MainWindow::client_readyRead()
//{
//    QByteArray raw_data = client->get_socket()->readAll();
//    QString data = QTextCodec::codecForName("UTF-8")->
//            toUnicode(raw_data);
//    if(data == "CHESSBOT TEST SERVER"){
//        GameUi ui;
//        ui.setupUi(this, 3);
//        this->show();
//    }
//    client->get_socket()->write("CHESSBOT TEST CLIENT");
//    qInfo() << data;
//}

void MainWindow::on_bt_single_clicked()
{
    GameUi ui;
    game = ui.setupUi(this, 0);
    this->show();
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

    server->listen(ui->line_host_port->text().toUShort());

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

    QMovie *movie = new QMovie("../pngs/Loading_icon.gif");
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






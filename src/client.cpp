#include "client.h"
#include "mainwindow.h"

Client::Client(MainWindow *window,
               QObject *parent)
    : QObject{parent}
{
    this->window = window;
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

QTcpSocket* Client::get_socket()
{
    return socket;
}

void Client::doConnect(){

    qDebug() << "connecting...";

    socket->connectToHost(this->host_addr, this->host_port);

    if(!socket->waitForConnected(5000))
    {
        qDebug() << "Error: " << socket->errorString();
    }
}

void Client::connected()
{
    qDebug() << "connected...";
    window->start_client_game();
}

void Client::disconnected()
{
    qDebug() << "disconnected...";
    window->isDataCame = false;
    window->exit_game_loop = true;
    socket->close();
}

void Client::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
}

void Client::readyRead()
{
    window->isDataCame = true;
}

#include "client.h"
#include "mainwindow.h"

Client::Client(MainWindow *window,
               QObject *parent)
    : QObject{parent}
{
    this->window = window;
}

QTcpSocket* Client::get_socket()
{
    return socket;
}

void Client::doConnect(){
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    qDebug() << "connecting...";

    // this is not blocking call
    socket->connectToHost(this->host_addr, this->host_port);
    // we need to wait...
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
}

void Client::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
}

void Client::readyRead()
{
//    qDebug() << "reading...";

//    // read the data from the socket
//    qDebug() << socket->readAll();
    window->isDataCame = true;
}

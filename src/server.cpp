#include "server.h"
#include "mainwindow.h"

Server::Server(MainWindow *window,
               QObject *parent)
    : QObject{parent}
{
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
    this->window = window;
}

void Server::listen(quint16 host_port)
{
    if(!server->listen(QHostAddress::LocalHost, host_port))
    {
        qDebug() << "Server could not start!";
    }
    else
    {
        qDebug() << "Server started!";
    }
}

quint16 Server::get_server_port()
{
    return server->serverPort();
}

QTcpServer* Server::get_server()
{
    return server;
}

QTcpSocket* Server::get_socket()
{
    return socket;
}

void Server::newConnection()
{
    qDebug() << "meow";
    socket = server->nextPendingConnection();
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    window->start_server_game();
}

void Server::disconnected()
{
    qDebug() << "disconnected...";
    window->isDataCame = false;
    window->exit_game_loop = true;
//    socket->deleteLater();
}

void Server::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
}

void Server::readyRead()
{
    window->isDataCame = true;
}


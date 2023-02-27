#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>
#include <QTextCodec>

class MainWindow;

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(MainWindow *window = nullptr,
                    QObject *parent = nullptr);
    quint16 get_server_port();
    QTcpServer* get_server();
    QTcpSocket* get_socket();
    void listen(quint16 host_port);

public slots:
    void newConnection();
//    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
signals:

private:
    QTcpServer *server;
    QTcpSocket *socket;
    MainWindow *window;
};

#endif // SERVER_H

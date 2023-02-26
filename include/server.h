#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QString host_port = "",
                    QObject *parent = nullptr);
    quint16 get_server_port();

public slots:
    void newConnection();

signals:

private:
    QTcpServer *server;
};

#endif // SERVER_H

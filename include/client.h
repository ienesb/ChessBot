#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QString host_addr = "",
                    quint16 host_port = 0,
                    QObject *parent = nullptr);
    void doConnect();
public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
signals:
private:
    QTcpSocket *socket;
    QString host_addr;
    quint16 host_port;

};

#endif // CLIENT_H

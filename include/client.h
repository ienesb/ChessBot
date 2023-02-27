#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>

class MainWindow;

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(MainWindow *window = nullptr,
                    QObject *parent = nullptr);
    void doConnect();
    QTcpSocket* get_socket();
    QString host_addr;
    quint16 host_port;
public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
signals:
    void send_readyRead();
private:
    QTcpSocket *socket;
    MainWindow *window;
};

#endif // CLIENT_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "server.h"
#include "client.h"
#include "ui.h"
#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool isDataCame;

    void start_server_game();
    void start_client_game();
    void online_game_loop(QTcpSocket* socket);

signals:
    void quit_app();

public slots:
    void bt_back_game_clicked();

private slots:
    void on_bt_exit_clicked();

    void on_bt_single_clicked();

    void on_bt_local_clicked();

    void on_bt_online_clicked();

    void on_bt_back_online_clicked();

    void on_bt_host_clicked();

    void on_bt_back_host_clicked();

    void on_bt_start_server_clicked();

    void on_bt_join_clicked();

    void on_bt_back_join_clicked();

    void on_bt_join_server_clicked();

    void on_bt_back_join_wait_clicked();

    void on_bt_back_host_wait_clicked();

private:
    Ui::MainWindow *ui;
    Server* server;
    Client* client;
    Game* game;
    QWidget* game_w;
    int gameMode;
    bool exit_game_loop = false;

friend class Client;
friend class Server;
friend class GameUi;
};
#endif // MAINWINDOW_H

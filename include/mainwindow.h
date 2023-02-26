#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void quit_app();

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

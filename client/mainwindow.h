#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QtNetwork/QTcpSocket>
#include <QTextEdit>
#include <QDebug>
#include <QMessageBox>
#include <QTextCursor>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private slots:
    void on_btn_send_clicked();
    void sendMessage();
    void revData();
    void connecterror();
    void on_btn_contrl_clicked();
    void movetoEnd();

    void on_btn_clear_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *tcpClient;
    QByteArray all_msg;
    int btn_flag;
};

#endif // MAINWINDOW_H

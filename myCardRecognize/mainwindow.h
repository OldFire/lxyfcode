#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QImage>
#include <QBuffer>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QVariant>
#include <QJsonArray>
#include <QByteArray>
#include <QMessageBox>
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
 protected:
    void keyPressEvent(QKeyEvent * event);

private slots:
    void on_btn_PostReq_clicked();

    void on_btn_GetReq_clicked();

    void on_btn_selectFile_clicked();

    void finishedSlot(QNetworkReply *reply);

    void finishedGet(QNetworkReply *reply);

    void replyErrprSlot();

    void movetoEnd();

    QString getIdCardNumber(QString &data);

    void on_btn_refresh_clicked();

    void on_btn_send_clicked();

private:
    Ui::MainWindow *ui;
    QString FileName;
    QNetworkAccessManager *nam;
    QNetworkRequest *request;

    QNetworkAccessManager *m_accessManager;
    QString all_msg;

};

#endif // MAINWINDOW_H

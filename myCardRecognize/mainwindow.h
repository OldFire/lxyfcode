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
    void on_btn_PostReq_clicked();

    void on_btn_GetReq_clicked();

    void on_btn_selectFile_clicked();

    void finishedSlot(QNetworkReply *reply);
    void replyErrprSlot();

    QString getIdCardNumber(QString &data);

private:
    Ui::MainWindow *ui;
    QString FileName;
    QNetworkAccessManager *nam;
    QNetworkRequest *request;
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->btn_selectFile->setFocus();
    nam = new QNetworkAccessManager(this);
       QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(finishedSlot(QNetworkReply*)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete nam;
}


// QString >> QJson
QJsonObject MainWindow::getJsonObjectFromString(const QString jsonString){
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toLocal8Bit().data());
    if( jsonDocument.isNull() ){
        qDebug()<< "===> please check the string "<< jsonString.toLocal8Bit().data();
    }
    QJsonObject jsonObject = jsonDocument.object();
    return jsonObject;
}

// QJson >> QString
QString MainWindow::getStringFromJsonObject(const QJsonObject& jsonObject){
    return QString(QJsonDocument(jsonObject).toJson());
}

void MainWindow::finishedSlot(QNetworkReply *reply)
{

    if (reply->error() == QNetworkReply::NoError)
         {
             QByteArray bytes = reply->readAll();


             this->getJsonObjectFromString(QString(bytes));

             QString string = QString::fromUtf8(bytes);

             ui->edt_ResData ->setText(string.toUtf8());
         }
         else
         {
             qDebug()<<"handle errors here";
             QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
             //statusCodeV是HTTP服务器的相应码，reply->error()是Qt定义的错误码，可以参考QT的文档
             qDebug( "found error ....code: %d %d\n", statusCodeV.toInt(), (int)reply->error());
             qDebug(qPrintable(reply->errorString()));
         }
         reply->deleteLater();
}

void MainWindow::replyErrprSlot()
{
    qDebug()<<"is  error!";
}

void MainWindow::on_btn_PostReq_clicked()
{
    QImage image(FileName);
        QByteArray ba;
        QBuffer buf(&ba);
        image.save(&buf,"jpg",20);
        QByteArray hexed = ba.toBase64();
        buf.close();

        QUrl myurl("http://ocrcp.market.alicloudapi.com/rest/160601/ocr/ocr_vehicle_plate.json");
        request = new QNetworkRequest(myurl);


       request->setUrl(myurl);
       request->setRawHeader("Content-Type","application/x-www-form-urlencoded; charset=utf-8");
       request->setRawHeader("Accept","application/json");
       request->setRawHeader("Authorization","APPCODE a31ff1330a354694ae17ab6defe32a78");

        QByteArray mybody="{ \
                       \"inputs\": [ \
                       {\
                           \"image\": { \
                               \"dataType\": 50,  \
                               \"dataValue\":\""+ hexed +  \
                       "\"}, \
                           \"configure\": { \
                               \"dataType\": 50, \
                               \"dataValue\": \"{\\\"multi_crop\\\":false}\" \
                           } \
                       }] \
                   }";



        QNetworkReply* reply = nam->post(*request,mybody );
        connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(replyErrprSlot()));

}

void MainWindow::on_btn_GetReq_clicked()
{

}

void MainWindow::on_btn_selectFile_clicked()
{
    ui->edt_filePath->clear();
    FileName =QFileDialog::getOpenFileName(NULL,"Open Image", "./", "Image Files (*.png *.jpg *.bmp)");
    ui->edt_filePath->setText(FileName);
    ui->lab_image->setPixmap(QPixmap(FileName));
}

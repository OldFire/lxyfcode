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

QString MainWindow::getIdCardNumber(QString &str)
{
    QJsonParseError json_error;
    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8(), &json_error);
    if(json_error.error == QJsonParseError::NoError)
    {
        if(doc.isObject())
        {
            QJsonObject obj= doc.object();
            if(obj.contains("plates"))
            {
                QJsonValue val= obj.take("plates");
                if(val.isArray())
                {
                     QJsonArray arry= val.toArray();
                     QJsonObject obj1=arry.at(0).toObject();
                     if(obj1.contains("txt"))
                     {
                         QString idCard=obj1.take("txt").toString();
                         return idCard;
                     }
                }

            }
        }
    }
    return NULL;
}


void MainWindow::finishedSlot(QNetworkReply *reply)
{

    if (reply->error() == QNetworkReply::NoError)
         {
             QByteArray bytes = reply->readAll();


           //  /************************************
             QJsonParseError json_error;
             QJsonDocument parse_doucment = QJsonDocument::fromJson(bytes, &json_error);
             if(json_error.error == QJsonParseError::NoError)
             {
                 if(parse_doucment.isObject())
                 {
                     QJsonObject obj = parse_doucment.object();
                     if(obj.contains("outputs"))
                     {
                         QJsonValue name_value = obj.take("outputs");
                         if(name_value.isArray())
                         {
                             QJsonArray myoutputs = name_value.toArray();

                             QJsonValue val=myoutputs.at(0);
                             if(val.isObject())
                             {
                                 QJsonObject obj1= val.toObject();
                                 if(obj1.contains("outputValue"))
                                 {
                                    QJsonObject obj2=obj1.take("outputValue").toObject();
                                    if(obj2.contains("dataValue"))
                                    {
                                        QString mydatavalue=obj2.take("dataValue").toVariant().toString();
                                        qDebug()<<mydatavalue;
                                        QString IdCardnumber=getIdCardNumber(mydatavalue);

                                        ui->edt_ResData ->setText("your car number is:"+IdCardnumber);
                                    }
                                 }
                             }

                         }
                     }
                 }
             }

            // ***************************************/

         }
         else
         {
             qDebug()<<"handle errors here";
             QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
             //statusCodeV是HTTP服务器的相应码，reply->error()是Qt定义的错误码，可以参考QT的文档
             qDebug( "found error ....code: %d %d\n", statusCodeV.toInt(), (int)reply->error());
             qDebug(qPrintable(reply->errorString()));
             ui->edt_ResData ->setText("sorry,don't recoginzed your card number!");
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

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

    m_accessManager=new QNetworkAccessManager(this);
    QObject::connect(m_accessManager, SIGNAL(finished(QNetworkReply*)),
             this, SLOT(finishedGet(QNetworkReply*)));

    ui->edt_send->setText("hello");
     connect(ui->edt_talk,SIGNAL(textChanged()),this,SLOT(movetoEnd()));

     connect(ui->edt_send, SIGNAL(returnPressed()), this, SLOT(on_btn_send_clicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete nam;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(ui->edt_send->text().isEmpty()||ui->edt_send->text().isNull()||ui->edt_send->text()=="") return;

    if(event->key() == Qt::Key_Return)
    {
        this->on_btn_send_clicked();
    }

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

void MainWindow::finishedGet(QNetworkReply *reply)
{

    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();
        QJsonDocument doc=QJsonDocument::fromJson(bytes);
        if(doc.isObject())
        {
            QJsonObject obj= doc.object();
            if(obj.contains("result"))
            {
                QJsonValue val=obj.take("result");
                if(val.isObject())
                {
                    QJsonObject obj1= val.toObject();
                    if(obj1.contains("content"))
                    {
                        QString resdata=obj1.take("content").toString();
                        all_msg+="recv:\n  "+QString(resdata)+"\n";
                        ui->edt_talk->setText(all_msg);
                    }
                }
            }
        }

    }
    else
    {
        qDebug()<<"handle errors here";
        QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        //statusCodeV是HTTP服务器的相应码，reply->error()是Qt定义的错误码，可以参考QT的文档
        qDebug( "found error ....code: %d %d\n", statusCodeV.toInt(), (int)reply->error());
        qDebug(qPrintable(reply->errorString()));
        all_msg+="recv:\n  "+QString("sorry,i don't konw what are you say...")+"\n";
        ui->edt_talk ->setText(all_msg);

    }
    reply->deleteLater();

}



void MainWindow::replyErrprSlot()
{
    qDebug()<<"is  error!";
}


void MainWindow::on_btn_PostReq_clicked()
{
    if(FileName.isEmpty()||FileName==" ")
        {
            QMessageBox::warning(NULL,"warning","文件类型错误或未选择文件，请重新输入！",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            return;
        }
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


        delete request;
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

void MainWindow::on_btn_refresh_clicked()
{
    all_msg="";
    ui->edt_talk->clear();

}

void MainWindow::on_btn_send_clicked()
{

    QString msg=ui->edt_send->text();

    if(msg.isEmpty()||msg=="")
        {
            QMessageBox::warning(NULL,"warning","消息为空，请重新输入！",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            return;
        }
    QByteArray addr("http://jisuznwd.market.alicloudapi.com/iqa/query?question=");

    QUrl myurl(addr+msg.toUtf8());
   // qDebug()<<addr+msg.toUtf8();
    QNetworkRequest request;
   request.setUrl(myurl);
   request.setRawHeader("Content-Type","application/json; charset=utf-8");
   request.setRawHeader("Accept","application/json");
   request.setRawHeader("Authorization","APPCODE a13ff1330a354694ae17ab6defe32a78");
   m_accessManager->get(request);


   all_msg+="send:\n  "+msg+"\n";
   ui->edt_send->clear();
}

void MainWindow::movetoEnd()
{
    QTextCursor cursor=ui->edt_talk->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->edt_talk->setTextCursor(cursor);

}

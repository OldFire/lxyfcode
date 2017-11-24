#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lab_publish->adjustSize();
    ui->lab_publish->setWordWrap(true);

    ui->lab_publish->setText("说明：\n \
                             0101:单人历史\n \
                             0102:单人文学\n \
                             0201:双人历史\n \
                             0202:双人文学"
                             );
    btn_flag=1;
    ui->edit_address->setText("112.74.205.53");
    ui->edit_port->setText("9988");
    connect(ui->display_msg,SIGNAL(textChanged()),this,SLOT(movetoEnd()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendMessage()
{
    QString strMesg= ui->send_msg->toPlainText();
    all_msg+="send:\n    "+strMesg+"\n";
    ui->display_msg->setText(all_msg);
    ui->display_msg->update();

    tcpClient->write(strMesg.toStdString().c_str(),strlen(strMesg.toStdString().c_str())); //发送数据
}
void MainWindow::revData()
{
    QByteArray qba;
    int onecelen;
    int totalreadlen=0;
    int headlen=tcpClient->read(4).toInt();
    int remainlen=headlen;
#if 0

    while(remainlen)
    {
      onecelen=remainlen>1024?1024:remainlen;
      qba+=tcpClient->read(onecelen);
      totalreadlen+=onecelen;
      remainlen=headlen-totalreadlen;
    }
#else
    char buf[1025]={0};
    while(remainlen)
    {
      onecelen=remainlen>1024?1024:remainlen;
      int ret=tcpClient->read(buf,onecelen);
      if(ret) totalreadlen+=ret;
      else
       {
           QMessageBox::warning(NULL,"warning","接收消息中出现问题!",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
           break;
       }
      qba+=QByteArray(buf);
      memset(buf,0,1025);
      remainlen=headlen-totalreadlen;
    }
#endif

    all_msg+="recvlen:"+QString("%1").arg(headlen)+"\n";
    all_msg+="recv:\n    "+QString(qba)+"\n";
    ui->display_msg->setText(all_msg);
    ui->display_msg->update();
}

void MainWindow::connecterror()
{
    all_msg+="tips:\n    "+QString("连接服务器失败......")+"\n";
    ui->display_msg->setText(all_msg);
    ui->display_msg->update();
}

void MainWindow::on_btn_send_clicked()
{
    if(btn_flag==1)
    {
        QMessageBox::warning(NULL,"warning","未连接到服务器，无法发送消息！",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    this->sendMessage();
    ui->send_msg->clear();

    ui->send_msg->update();
}

void MainWindow::on_btn_contrl_clicked()
{


    QString addr=ui->edit_address->text();
    QString port=ui->edit_port->text();
    if(addr.isEmpty()||port.isEmpty())
    {
        QMessageBox::warning(NULL,"warning","地址或端口不对，请重新输入！",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }

    if(btn_flag%=2)
    {
        ui->edit_address->setEnabled(false);
        ui->edit_port->setEnabled(false);
        tcpClient = new QTcpSocket(this);
        tcpClient->connectToHost(addr,port.toInt());
        connect(tcpClient,SIGNAL(readyRead()),this,SLOT(revData()));
        connect(tcpClient, static_cast<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error),this,connecterror);
        ui->btn_contrl->setText("断开");
    }
    else
    {
        tcpClient->close();
        ui->edit_address->setEnabled(true);
        ui->edit_port->setEnabled(true);
        ui->btn_contrl->setText("连接");
        delete tcpClient;

    }
    btn_flag++;

}

void MainWindow::movetoEnd()
{
    QTextCursor cursor=ui->display_msg->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->display_msg->setTextCursor(cursor);

}

void MainWindow::on_btn_clear_clicked()
{
    ui->display_msg->clear();
    ui->send_msg->clear();
    all_msg.clear();
}

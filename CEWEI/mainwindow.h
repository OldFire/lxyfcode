#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QDateTime>
#include <QGroupBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <QDialog>
#include <QMap>
#include <QProcess>
#include <windows.h>
#include <QButtonGroup>
#include <QToolButton>
#include "mythread.h"
#include <QVector>
#include <cmath>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QAction>
#include <QMenu>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool workDetail(int flag);
    bool initWorkspace();
    bool jogAction(int axId,int flag); //jog运动,axId轴号  flag运动速度加方向
    bool trapAction(int axId,int flag,long pos); //jog运动,axId轴号  flag运动速度加方向
    bool intiProgramList(); //初始化项目列表到控件
    void createSignalArea(QFrame *frame,QButtonGroup&btngroup, QString signame,int count); //创建一个信号模块
    bool isContain(QWidget*obj,QWidget*parent,QPoint point,int border);  //判断鼠标是否在控件内
    bool signalFlag();
public slots:
     void myTimeout();

private slots:
     void on_pushButton_commTools_clicked();

     void on_pushButton_writeConfig_clicked();

     void on_pushButton_readConfig_clicked();

     void on_comboBox_workSpace_currentIndexChanged(const QString &arg1);

     void on_comboBox_Num_currentIndexChanged(const QString &arg1);

     void on_pushButton_openConfig_clicked();

     void on_comboBox_speed_currentIndexChanged(const QString &arg1);

     void on_pushButton_axiy_fu_pressed();

     void on_pushButton_axiy_fu_released();

     void on_pushButton_axix_zheng_pressed();

     void on_pushButton_axix_fu_released();

     void on_pushButton_axix_zheng_released();

     void on_pushButton_axix_fu_pressed();

     void on_pushButton_axiy_zheng_pressed();

     void on_pushButton_axiy_zheng_released();

     void on_pushButton_axiz_zheng_pressed();

     void on_pushButton_axiz_fu_released();

     void on_pushButton_axiz_zheng_released();

     void on_pushButton_axiz_fu_pressed();

     void on_pushButton_axiu_zheng_pressed();

     void on_pushButton_axiu_zheng_released();

     void on_pushButton_axiu_fu_pressed();

     void on_pushButton_axiu_fu_released();

     void on_pushButton_sysInit_clicked();  //复位按钮功能

     void on_pushButton_sysStop_clicked();

     void on_pushButton_isStop_clicked();

     void on_pushButton_setProgram_clicked();

     void on_pushButton_startProgram_clicked();

     void on_comboBox_exchangeCardid_currentIndexChanged(const QString &arg1);

     void on_pushButton_reWorkSpace_clicked();

     void on_pushButton_nextGo_clicked();

     void on_lineEdit_nextStop_clicked();

     void on_pushButton_reAix_x_clicked();

     void on_pushButton_reAix_y_clicked();

     void on_pushButton_reAix_z_clicked();

     void on_pushButton_reAix_u_clicked();

private:
    Ui::MainWindow *ui;
    QLabel *label;
    QTimer *timer;
    int nowSpeed;
    int cardId;
    MyThread *pthread;
    QMenu *rightMenu;
    QPoint globalPos; //鼠标当前位置
    QAction *isNormal;
    QAction *isOpposite;
public:
    QButtonGroup btngroup_sigin; //输入信号模块
    QButtonGroup btngroup_sigout; //输出信号模块
    QButtonGroup btngroup_sigzheng; //正极限位模块
    QButtonGroup btngroup_sigfu; //负极限位模块
    QButtonGroup btngroup_sigyuan; //原点信号模块
    QButtonGroup btngroup_dalarm; //驱动报警模块
    QButtonGroup btngroup_tomcan; //伺服全能模块
    QButtonGroup btngroup_alclear; //报警清除模块

protected:
    void contextMenuEvent(QContextMenuEvent*event);


};

#endif // MAINWINDOW_H

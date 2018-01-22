#include "mainwindow.h"
#include "ui_mainwindow.h"

QMap<QString,QString>mymap;
QMap<QString,QString>programMap;

static QString  sig_on="background-color: rgb(255, 255, 0);border-radius:12px";
static QString  sig_off="background-color: rgb(170, 170, 255);border-radius:12px";

QString path_cwProgramList="./cwProgramList.ini";
QString path_toolDirs="./toolDirs.ini";
QString path_signalInfo="./signalInfo.ini";
char* path_config="./config.ini";

static long sts;
QString myId;
QString myName;
QString myType;
QString myNum;
QString myAxisX;
QString myAxisY;
QString myAxisZ;
QString myAxisU;

short axi_x,axi_y,axi_z,axi_u;

double nowPos_x,nowPos_y,nowPos_z,nowPos_u;

QString *arrystr[]={&myId,&myName,&myType,&myNum,&myAxisX,&myAxisY,&myAxisZ,&myAxisU};

//判断是否取反,1:正常  0:取反
char bg_sigin[17];
char bg_sigout[17];
char bg_sigzheng[9];
char bg_sigfu[9];
char bg_sigyuan[9];
char bg_sigdalarm[9];
char bg_sigtomcan[9];
char bg_sigalclear[9];


QStringList mylist;

int speedGrade[]={2,4,8,12};

static bool initReult=false;  //复位标识

void myStop(int flag)       // 1.系统急停 2.轴暂停运动
{
    GT_Stop(1<<(axi_x-1),1<<(axi_x-1));
    if(axi_y!=0) GT_Stop(1<<(axi_y-1),1<<(axi_y-1));
    if(axi_z!=0) GT_Stop(1<<(axi_z-1),1<<(axi_z-1));
    if(axi_u!=0) GT_Stop(1<<(axi_u-1),1<<(axi_u-1));
    if(flag==1)
    {
        GT_AxisOff(axi_x);
        if(axi_y!=0) GT_AxisOff(axi_y);
        if(axi_z!=0) GT_AxisOff(axi_z);
        if(axi_u!=0) GT_AxisOff(axi_u);
        GT_Close();
        initReult=FALSE;
    }
}


//写配置信息到文件
bool write_tofile( char* filename)
{
    FILE *fp=fopen(filename,"w+");
    if (fp==NULL)
    {
        QMessageBox::warning(NULL,"error","写配置信息失败!");
        return false;
    }
    char buf[100]={0};

    QString str;
    str=QString("ID=")+myId+QString(";\n")+\
            QString("名称=")+myName+QString(";\n")+\
            QString("类型=")+myType+QString(";\n")+\
            QString("轴数量=")+myNum+QString(";\n")+\
            QString("X轴ID=")+myAxisX+QString(";\n")+\
            QString("Y轴ID=")+myAxisY+QString(";\n")+\
            QString("Z轴ID=")+myAxisZ+QString(";\n")+\
            QString("U轴ID=")+myAxisU+QString(";\n");
    mymap.insert(myId,str);
    for(auto it=mymap.begin();it!=mymap.end();it++)
    {
        strcpy(buf,it.value().toStdString().c_str());
        int ret=fwrite(buf,strlen(buf),1,fp);
        if(ret<=0) qDebug()<<"写出数据失败!";
    }
    fclose(fp);
    return true;
}

//从配置文件读取信息
bool read_fromfile(char*filename,char*curSelect)
{
    FILE*fp=fopen(filename,"r");
    if(fp==NULL)
    {
        QMessageBox::warning(NULL,"error","读取配置信息失败!");
        return false;
    }
    char buf[100]={0};
    char tmp1[50],tmp2[50];
    int i=0;

    while(fgets(buf,sizeof(buf),fp))
    {
        memset(tmp2,0,sizeof(tmp2));
        sscanf(buf,"%[^=]=%[^;]",tmp1,tmp2);
        if(strcmp(tmp2, curSelect) == 0 &&
                strcmp(tmp1,"ID")==0) break;
        *arrystr[i] = QString(tmp2);
        i++;
        if(myId.isEmpty()) myId="0";
        if (i == 8)
        {
            QString str= QString("ID=") + myId + QString(";\n") + \
                    QString("名称=") + myName + QString(";\n") + \
                    QString("类型=") + myType + QString(";\n") + \
                    QString("轴数量=") + myNum + QString(";\n") + \
                    QString("X轴ID=") + myAxisX + QString(";\n") + \
                    QString("Y轴ID=") + myAxisY + QString(";\n") + \
                    QString("Z轴ID=") + myAxisZ + QString(";\n")+ \
                    QString("U轴ID=") + myAxisU + QString(";\n");
            mymap.insert(myId, str);
            i = 0;
        }
    }
    fclose(fp);
    return true;
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("策维项目");
    // resize(1033,633);  // 设置窗口大小
    setFixedSize(1025,633);

    //输入信号
    createSignalArea(ui->frame_5,btngroup_sigin,"输入信号",16);

    //输出信号
    createSignalArea(ui->frame_12,btngroup_sigout,"输出信号",16);

    //正极限位
    createSignalArea(ui->frame_4,btngroup_sigzheng,"正极限位",8);

    //负极限位
    createSignalArea(ui->frame_7,btngroup_sigfu,"负极限位",8);

    //原点信号
    createSignalArea(ui->frame_8,btngroup_sigyuan,"原点信号",8);

    //驱动报警
    createSignalArea(ui->frame_9,btngroup_dalarm,"驱动报警",8);

    //伺服使能
    createSignalArea(ui->frame_10,btngroup_tomcan,"伺服使能",8);

    //报警清除
    createSignalArea(ui->frame_11,btngroup_alclear,"报警清除",8);

    memset(bg_sigin,'1',16);
    memset(bg_sigout,'1',16);
    memset(bg_sigzheng,'1',8);
    memset(bg_sigfu,'1',8);
    memset(bg_sigyuan,'1',8);
    memset(bg_sigdalarm,'1',8);
    memset(bg_sigtomcan,'1',8);
    memset(bg_sigalclear,'1',8);

    //读取信号状态
    signalFlag();

    rightMenu=new QMenu();
    isNormal= rightMenu->addAction(QIcon(":/new/prefix1/select.bmp"),"正常");
    isOpposite= rightMenu->addAction(QIcon(":/new/prefix1/blank.bmp"),"取反");
    rightMenu->addSeparator();
    QAction *saveTofile= rightMenu->addAction(QIcon(":/new/prefix1/add.bmp"),"保存");

    //设置底部状态栏
    QStatusBar *statusbar=statusBar();
    label=new QLabel(statusbar);
    statusbar->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
    statusbar->addPermanentWidget(label);
    statusbar->addWidget(new QLabel("你好,欢迎使用策维系统!!!"));
    timer=new QTimer();
    timer->setInterval(200);
    timer->start();

    mylist<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8";

    //获取项目列表
    intiProgramList();

    //卡号列表初始化
    ui->comboBox_exchangeCardid->addItems(mylist);

    QStringList speedList;
    speedList<<"1-低速"<<"2-中速"<<"3-高速"<<"4-极速";
    ui->comboBox_speed->addItems(speedList);


    //读配置文件
    on_pushButton_readConfig_clicked();

    //工站详情
    workDetail(1);

    //设置初始速度
    nowSpeed=speedGrade[0];

    axi_x=myAxisX.toInt()+1;
    axi_y=myAxisY.toInt()+1;
    axi_z=myAxisZ.toInt()+1;
    axi_u=myAxisU.toInt()+1;

    //初始化点位运动的点
    ui->lineEdit_nextPosX->setText("0");
    ui->lineEdit_nextPosY->setText("0");
    ui->lineEdit_nextPosZ->setText("0");
    ui->lineEdit_nextPosU->setText("0");

    //底部状态栏与信号检测200sec/次
    connect(timer, SIGNAL(timeout()), this,SLOT(myTimeout()));

    //保存监测
    connect(saveTofile,&QAction::triggered,[](){
        QFile file(path_signalInfo);
           if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
           {
               QMessageBox::warning(NULL,"error","保存失败!");
               return;
           }
           QTextStream txtOutput(&file);

           txtOutput <<bg_sigin<<endl
                    <<bg_sigout<<endl
                    <<bg_sigzheng<<endl
                    <<bg_sigfu<<endl
                    <<bg_sigyuan<<endl
                    <<bg_sigdalarm<<endl
                    <<bg_sigtomcan<<endl
                    <<bg_sigalclear;
           file.close();
    });


    //是否正常监测
    connect(isNormal,&QAction::triggered,[=](){
        isNormal->setIcon(QIcon(":/new/prefix1/select.bmp"));
        isOpposite->setIcon(QIcon(":/new/prefix1/blank.bmp"));
        for(int i=0;i<16;i++)
        {
            if(isContain(btngroup_sigin.button(i),ui->frame_5,this->globalPos,0))
            {
                bg_sigin[i]='1';
            }
            else if(isContain(btngroup_sigout.button(i),ui->frame_12,this->globalPos,0))
            {
                bg_sigout[i]='1';
            }
            else if((i<8)&& isContain(btngroup_sigzheng.button(i),ui->frame_4,this->globalPos,0))
            {
                bg_sigzheng[i]='1';
            }
            else if((i<8) && isContain(btngroup_sigfu.button(i),ui->frame_7,this->globalPos,0))
            {
                bg_sigfu[i]='1';
            }
            else if((i<8) && isContain(btngroup_sigyuan.button(i),ui->frame_8,this->globalPos,0))
            {
                bg_sigyuan[i]='1';
            }
            else if((i<8) && isContain(btngroup_dalarm.button(i),ui->frame_9,this->globalPos,0))
            {
                bg_sigdalarm[i]='1';
            }
            else if((i<8) && isContain(btngroup_tomcan.button(i),ui->frame_10,this->globalPos,0))
            {
                bg_sigtomcan[i]='1';
            }
            else if((i<8) && isContain(btngroup_alclear.button(i),ui->frame_11,this->globalPos,0))
            {
                bg_sigalclear[i]='1';
            }
        }

    });

    //是否取反监测
    connect(isOpposite,&QAction::triggered,[=](){
        isNormal->setIcon(QIcon(":/new/prefix1/blank.bmp"));
        isOpposite->setIcon(QIcon(":/new/prefix1/select.bmp"));
        for(int i=0;i<16;i++)
        {
            if(isContain(btngroup_sigin.button(i),ui->frame_5,this->globalPos,0))
            {
                bg_sigin[i]='0';
            }
            else if(isContain(btngroup_sigout.button(i),ui->frame_12,this->globalPos,0))
            {
                bg_sigout[i]='0';
            }
            else if((i<8)&& isContain(btngroup_sigzheng.button(i),ui->frame_4,this->globalPos,0))
            {
                bg_sigzheng[i]='0';
            }
            else if((i<8) && isContain(btngroup_sigfu.button(i),ui->frame_7,this->globalPos,0))
            {
                bg_sigfu[i]='0';
            }
            else if((i<8) && isContain(btngroup_sigyuan.button(i),ui->frame_8,this->globalPos,0))
            {
                bg_sigyuan[i]='0';
            }
            else if((i<8) && isContain(btngroup_dalarm.button(i),ui->frame_9,this->globalPos,0))
            {
                bg_sigdalarm[i]='0';
            }
            else if((i<8) && isContain(btngroup_tomcan.button(i),ui->frame_10,this->globalPos,0))
            {
                bg_sigtomcan[i]='0';
            }
            else if((i<8) && isContain(btngroup_alclear.button(i),ui->frame_11,this->globalPos,0))
            {
                bg_sigalclear[i]='0';
            }
        }
    });


    //对输出信号的按钮监测
    connect(&btngroup_sigout,static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),[=](int index){
        GT_SetDo(MC_GPO,1<<index);
    });

    //对报警清除的按钮监测
    connect(&btngroup_alclear,static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),[=](int index){
        GT_SetDo(MC_CLEAR,1<<index);
    });

    //对使能的按钮监测
    connect(&btngroup_tomcan,static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),[=](int index){
        GT_SetDo(MC_ENABLE,1<<index);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::workDetail(int flag)
{
    //设置工站ID
    ui->lineEdit_Id->setText(myId);

    //工站名称
    ui->lineEdit_Name->setText(myName);

    //电机类型
    if(flag==1) ui->comboBox_Type->addItem("电机工站");
    ui->comboBox_Type->setCurrentIndex(myType.toInt());

    //轴数量设置
    if (flag == 1)
    {
        QStringList tmp;
        tmp<<"1"<<"2"<<"3"<<"4";
        ui->comboBox_Num->addItems(tmp);
    }
    ui->comboBox_Num->setCurrentIndex(myNum.toInt());

    //轴ID设置

    if (flag == 1)
    {
        ui->comboBox_Axi_idx->addItems(mylist);
        ui->comboBox_Axi_idy->addItems(mylist);
        ui->comboBox_Axi_idz->addItems(mylist);
        ui->comboBox_Axi_idu->addItems(mylist);

    }
    ui->comboBox_Axi_idx->setCurrentIndex(myAxisX.toInt());
    ui->comboBox_Axi_idy->setCurrentIndex(myAxisY.toInt());
    ui->comboBox_Axi_idz->setCurrentIndex(myAxisZ.toInt());
    ui->comboBox_Axi_idu->setCurrentIndex(myAxisU.toInt());

    QString arg;
    on_comboBox_Num_currentIndexChanged(arg);
    return true;
}

bool MainWindow::initWorkspace()
{

    for(auto it=mymap.begin();it!=mymap.end();it++)
    {
        QString  str1;
        QString str, str2,str3;
        str1 = it.key();
        str2 = it.value();
        str3=str2.replace(";","");
        int slen=str3.indexOf("类型")-(str3.indexOf("名称=")+3);
        str = str3.mid(8,slen-1); //减1为去掉最后的换行符
        str1=str1+"-"+str;
        if(ui->comboBox_workSpace->findText(str1)>=0) continue;
        ui->comboBox_workSpace->addItem(str1);
    }



    ui->comboBox_workSpace->setCurrentIndex(mymap.size()-1);
    return true;
}

bool MainWindow::jogAction(int axId, int flag)
{
    if(!initReult) return false;
    TThreadSts thread;
    short rtn;
    short funId;
    TVarInfo speed,axi,count,pclock,flag1,flag2;

    rtn = GT_Download("myJogaction.bin");
    // 获取函数ID
    rtn = GT_GetFunId("jogAction",&funId);

    // 获取局部变量的ID
    rtn = GT_GetVarId("jogAction","axi",&axi);
    rtn = GT_GetVarId("jogAction","speed",&speed);
    rtn = GT_GetVarId("jogAction","pclock",&pclock);
    rtn = GT_GetVarId("jogAction","count",&count);
    rtn = GT_GetVarId("jogAction","flag1",&flag1);
    rtn = GT_GetVarId("jogAction","flag2",&flag2);

    // 绑定线程，函数，数据页
    rtn = GT_Bind(0,funId,0);

    double value=axId;
    // 初始化运动程序的全局变量axi
    rtn = GT_SetVarValue(0,&axi,&value);

    // 初始化运动程序的全局变量speed
    value=flag;
    rtn = GT_SetVarValue(0,&speed,&value);

    // 初始化运动程序的全局变量pclock
    value=NULL;
    rtn = GT_SetVarValue(0,&pclock,&value);

    // 初始化运动程序的全局变量count
    value=1;
    rtn = GT_SetVarValue(0,&count,&value);

    double sts=0;
    // 启动线程
    rtn = GT_RunThread(0);
    do
    {
        // 查询线程状态
        rtn = GT_GetThreadSts(0,&thread);


        rtn = GT_GetVarValue(0,&flag1,&sts);
        if(sts)
        {
            qDebug()<<"运动到负限位!";

        }
        rtn = GT_GetVarValue(0,&flag2,&sts);
        if(sts)
        {
            qDebug()<<"运动到负限位!";
        }

    }while( 1== thread.run );	// 等待线程运行结束

    return true;
}

bool MainWindow::trapAction(int axId, int flag, long aimpos)
{
    if(!initReult) return false;
    TThreadSts thread;
    short rtn;
    short funId;
    TVarInfo speed,axi,count,pclock,flag1,flag2,pos;

    rtn = GT_Download("myTrapaction.bin");
    // 获取函数ID
    rtn = GT_GetFunId("myTrapaction",&funId);

    // 获取局部变量的ID
    rtn = GT_GetVarId("trapAction","axi",&axi);
    rtn = GT_GetVarId("trapAction","speed",&speed);
    rtn = GT_GetVarId("trapAction","pclock",&pclock);
    rtn = GT_GetVarId("trapAction","count",&count);
    rtn = GT_GetVarId("trapAction","flag1",&flag1);
    rtn = GT_GetVarId("trapAction","flag2",&flag2);
    rtn = GT_GetVarId("trapAction","pos",&pos);

    // 绑定线程，函数，数据页
    rtn = GT_Bind(axId,funId,axId);

    double value=axId;
    // 初始化运动程序的全局变量axi
    rtn = GT_SetVarValue(axId,&axi,&value);

    // 初始化运动程序的全局变量speed
    value=flag;
    rtn = GT_SetVarValue(axId,&speed,&value);

    // 初始化运动程序的全局变量pclock
    value=NULL;
    rtn = GT_SetVarValue(axId,&pclock,&value);

    // 初始化运动程序的全局变量count
    value=1;
    rtn = GT_SetVarValue(axId,&count,&value);

    // 初始化运动程序的全局变量pos
    value=aimpos;
    rtn = GT_SetVarValue(axId,&pos,&value);

    double sts=0;
    // 启动线程
    rtn = GT_RunThread(axId);
    do
    {
        // 查询线程状态
        rtn = GT_GetThreadSts(axId,&thread);
        rtn = GT_GetVarValue(axId,&flag1,&sts);
        if(sts)
        {
            qDebug()<<"运动到负限位!";
        }
        rtn = GT_GetVarValue(axId,&flag2,&sts);
        if(sts)
        {
            qDebug()<<"运动到正限位!";
        }

    }while( 1== thread.run );	// 等待线程运行结束

    return true;
}

//初始化已经添加过的项目列表
bool MainWindow::intiProgramList()
{
    QFile file(path_cwProgramList);
    QByteArray readStr;
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(NULL, "error", "项目列表读取失败!!!");
    }
    while(1)
    {
        readStr=file.readLine();
        if(readStr.length()<10) break;
        char kn[50]={0};
        char ktmp[50]={0};
        sscanf(readStr.data(),"%[^|]|",kn);
        strcpy(ktmp,kn);
        strcat(ktmp,"|");
        readStr.replace(ktmp,"").replace("\n","");
        programMap.insert(QString(kn),QString(readStr));
        ui->comboBox_selProgram->addItem(QString(kn));
    }
}

//信号模块初始化
void MainWindow::createSignalArea(QFrame*frame,QButtonGroup&btngroup,QString signame, int count)
{
    QHBoxLayout *siginLayout=new QHBoxLayout;
    frame->setLayout(siginLayout);

    QLabel *lab_sigin=new QLabel(signame);
    lab_sigin->setFixedWidth(53);
    siginLayout->addWidget(lab_sigin);
    QGridLayout *sigRight=new QGridLayout;
    for(int i=0;i<count;i++)
    {
        QToolButton *btn=new QToolButton;
        btn->setStyleSheet(sig_off); //无信号样式
        btn->setFixedSize(25,25);
        if(i<8)
        {
            sigRight->addWidget(btn,0,i);
        }
        else
        {
            sigRight->addWidget(btn,1,i-8);
        }
        btngroup.addButton(btn,i);
    }
    siginLayout->addLayout(sigRight);

    static int flag_i=1;
    connect(&btngroup,static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),[&](int index){

        if(flag_i)
        {
            btngroup.button(index)->setStyleSheet(sig_on);//有信号样式
            flag_i=0;
        }
        else
        {
            btngroup.button(index)->setStyleSheet(sig_off);//无信号样式
            flag_i=1;
        }
    });
}


//状态栏时间显示部分
void MainWindow::myTimeout()
{
    //底部状态栏
    QDateTime time=QDateTime::currentDateTime();
    label->setText(time.toString("yyyy-MM-dd  hh:mm:ss  ddd"));
    label->update();

    //信号检测
    long lGpiValue_fu=0;
    long lGpiValue_yuan=0;
    long lGpiValue_zhen=0;
    long lGpiValue_dalarm=0;
    long lGpiValue_sigin=0;
    long lGpiValue_motcan=0;
    long lGpiValue_alclear=0;
    long lGpiValue_sigout=0;

    //读取IO输入状态
    GT_GetDi(MC_LIMIT_POSITIVE, &lGpiValue_zhen);
    GT_GetDi(MC_HOME, &lGpiValue_yuan);
    GT_GetDi(MC_LIMIT_NEGATIVE, &lGpiValue_fu);
    GT_GetDi(MC_ALARM, &lGpiValue_dalarm);
    GT_GetDi(MC_GPI, &lGpiValue_sigin);

    //读取IO输出状态
    GT_GetDo(MC_ENABLE, &lGpiValue_motcan);
    GT_GetDo(MC_CLEAR, &lGpiValue_alclear);
    GT_GetDo(MC_GPO, &lGpiValue_sigout);

    for(int i=0,j=0;i<8,j<16;i++,j+=2)
    {
        //检测正限位
        if(bg_sigzheng[i]=='1')
        {
            if(lGpiValue_zhen&1<<i)
            {
                btngroup_sigzheng.button(i)->setStyleSheet(sig_on);
                GT_Stop(1<<i,1<<i);
            }
            else btngroup_sigzheng.button(i)->setStyleSheet(sig_off);
        }
        else
        {
            if(lGpiValue_zhen&1<<i)
            {
                btngroup_sigzheng.button(i)->setStyleSheet(sig_off);
                GT_Stop(1<<i,1<<i);
            }
            else btngroup_sigzheng.button(i)->setStyleSheet(sig_on);
        }


        //检测原点
        if(bg_sigyuan[i]=='1')
        {
            if(lGpiValue_yuan&1<<i) btngroup_sigyuan.button(i)->setStyleSheet(sig_on);
            else btngroup_sigyuan.button(i)->setStyleSheet(sig_off);
        }
        else
        {
            if(lGpiValue_yuan&1<<i) btngroup_sigyuan.button(i)->setStyleSheet(sig_off);
            else btngroup_sigyuan.button(i)->setStyleSheet(sig_on);
        }

        //检测负限位
        if(bg_sigfu[i]=='1')
        {
            if(lGpiValue_fu&1<<i)
            {
                btngroup_sigfu.button(i)->setStyleSheet(sig_on);
                GT_Stop(1<<i,1<<i);
            }
            else btngroup_sigfu.button(i)->setStyleSheet(sig_off);
        }
        else
        {
            if(lGpiValue_fu&1<<i)
            {
                btngroup_sigfu.button(i)->setStyleSheet(sig_off);
                GT_Stop(1<<i,1<<i);
            }
            else btngroup_sigfu.button(i)->setStyleSheet(sig_on);
        }


        //检测驱动报警
        if(bg_sigdalarm[i]=='1')
        {
            if(lGpiValue_dalarm&1<<i) btngroup_dalarm.button(i)->setStyleSheet(sig_on);
            else btngroup_dalarm.button(i)->setStyleSheet(sig_off);
        }
        else
        {
            if(lGpiValue_dalarm&1<<i) btngroup_dalarm.button(i)->setStyleSheet(sig_off);
            else btngroup_dalarm.button(i)->setStyleSheet(sig_on);
        }


        //检测输入信号
        if(bg_sigin[i]=='1')
        {
            if(lGpiValue_sigin&1<<j)
            {
                btngroup_sigin.button(j)->setStyleSheet(sig_off);
                btngroup_sigin.button(j+1)->setStyleSheet(sig_on);
            }
            else
            {
                btngroup_sigin.button(j)->setStyleSheet(sig_on);
                btngroup_sigin.button(j+1)->setStyleSheet(sig_off);
            }
        }
        else
        {
            if(lGpiValue_sigin&1<<j)
            {
                btngroup_sigin.button(j)->setStyleSheet(sig_on);
                btngroup_sigin.button(j+1)->setStyleSheet(sig_off);
            }
            else
            {
                btngroup_sigin.button(j)->setStyleSheet(sig_off);
                btngroup_sigin.button(j+1)->setStyleSheet(sig_on);
            }
        }

        //检测伺服使能
        if(bg_sigtomcan[i]=='1')
        {
            if(lGpiValue_motcan&1<<i) btngroup_tomcan.button(i)->setStyleSheet(sig_on);
            else btngroup_tomcan.button(i)->setStyleSheet(sig_off);
        }
        else
        {
            if(lGpiValue_motcan&1<<i) btngroup_tomcan.button(i)->setStyleSheet(sig_off);
            else btngroup_tomcan.button(i)->setStyleSheet(sig_on);
        }


        //检测报警清除
        if(bg_sigalclear[i]=='1')
        {
            if(lGpiValue_alclear&1<<i) btngroup_alclear.button(i)->setStyleSheet(sig_on);
            else btngroup_alclear.button(i)->setStyleSheet(sig_off);
        }
        else
        {
            if(lGpiValue_alclear&1<<i) btngroup_alclear.button(i)->setStyleSheet(sig_off);
            else btngroup_alclear.button(i)->setStyleSheet(sig_on);
        }


        //检测输出信号
        if(bg_sigout[i]=='1')
        {
            if(lGpiValue_sigout&1<<j)
            {
                btngroup_sigout.button(j)->setStyleSheet(sig_off);
                btngroup_sigout.button(j+1)->setStyleSheet(sig_on);
            }
            else
            {
                btngroup_sigout.button(j)->setStyleSheet(sig_on);
                btngroup_sigout.button(j+1)->setStyleSheet(sig_off);
            }

        }
        else
        {
            if(lGpiValue_sigout&1<<j)
            {
                btngroup_sigout.button(j)->setStyleSheet(sig_on);
                btngroup_sigout.button(j+1)->setStyleSheet(sig_off);
            }
            else
            {
                btngroup_sigout.button(j)->setStyleSheet(sig_off);
                btngroup_sigout.button(j+1)->setStyleSheet(sig_on);
            }

        }

    }

    //获取当前位置
    double enc[4]={0};
    GT_GetEncPos(axi_x,&enc[0],myNum.toShort()+1);
    nowPos_x=enc[0]/1000;
    nowPos_y=enc[1]/1000;
    nowPos_z=enc[2]/1000;
    nowPos_u=enc[3]/1000;
    ui->lineEdit_curPosX->setText(QString("%1").arg(nowPos_x));
    ui->lineEdit_curPosY->setText(QString("%1").arg(nowPos_y));
    ui->lineEdit_curPosZ->setText(QString("%1").arg(nowPos_z));
    ui->lineEdit_curPosU->setText(QString("%1").arg(nowPos_u));
}

//外部工具
void MainWindow::on_pushButton_commTools_clicked()
{
    QDialog *toolwidget =new QDialog;
    toolwidget->setWindowTitle("常用工具");
    toolwidget->setFixedSize(400,300);
    QVBoxLayout *mainLayout=new QVBoxLayout;
    toolwidget->setLayout(mainLayout);
    mainLayout->setMargin(50);

    QHBoxLayout *topLayout=new QHBoxLayout;
    QLabel *lab1=new QLabel("添加工具");
    topLayout->addWidget(lab1);
    QLineEdit *toolName=new QLineEdit;
    topLayout->addWidget(toolName);
    QPushButton *addTool=new QPushButton;
    addTool->setIcon(QIcon(":/new/prefix1/add.bmp"));
    addTool->setMinimumWidth(60);
    topLayout->addWidget(addTool);
    QMap<QString,QString>myMap;

    QFile file(path_toolDirs);
    QByteArray readStr;
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(toolwidget, "error", "工具读取失败!!!");
    }

    while(1)
    {
        readStr=file.readLine();
        if(readStr.length()<10) break;
        char kn[50]={0};
        char ktmp[50]={0};
        sscanf(readStr.data(),"%[^|]|",kn);
        strcpy(ktmp,kn);
        strcat(ktmp,"|");
        readStr.replace(ktmp,"").replace("\n","");
        myMap.insert(QString(kn),QString(readStr));
        // qDebug()<<kn<<":"<<readStr;
    }
    file.close();

    connect(addTool, &QPushButton::clicked, [=](){
        QString filename =QFileDialog::getOpenFileName(NULL, "选择程序","../", "可执行程序 (*.exe);;其它 (*.*)");
        toolName->setText(filename);
        QFileInfo fileinfo(filename);
        QFile file(path_toolDirs);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Append))
        {
            QMessageBox::warning(toolwidget, "error", "添加失败!!!");
            return;
        }

        QTextStream txtOutput(&file);
        txtOutput << fileinfo.fileName()<<"|"<<fileinfo.filePath()<<endl;
        file.close();
    });

    QGridLayout *bottomLayout=new QGridLayout;

    int i=0;
    for( auto it=myMap.begin();it!=myMap.end();it++)
    {
        QPushButton *btn=new QPushButton(toolwidget);
        btn->setFixedSize(60,30);
        if(i<3) bottomLayout->addWidget(btn,0,i,Qt::AlignCenter);
        else if(i<6) bottomLayout->addWidget(btn,1,i-3,Qt::AlignCenter);
        else if(i<9) bottomLayout->addWidget(btn,2,i-6,Qt::AlignCenter);
        QString disText=it.key();
        btn->setText(disText.replace(".exe",""));
        btn->setToolTip(it.key());
        i++;
        connect(btn,&QPushButton::clicked,[=](){
            QProcess myprocess;
            QString program=it.value();
            if(disText.indexOf("exe"))
            {
                myprocess.startDetached(program.replace("/","//"),QStringList(program.replace("/","//")));
            }
            else
            {
                myprocess.startDetached("cmd.exe",QStringList(program.replace("/","//")));
            };
        });
    }

    mainLayout->addLayout(topLayout);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(bottomLayout);

    toolwidget->exec();//模态显示

}

//写配置信息到文件
void MainWindow::on_pushButton_writeConfig_clicked()
{

    if(ui->lineEdit_Name->text().isEmpty())
    {
        QMessageBox::warning(this,"error","名称为空，请\n重新输入！");
        return;
    }

    myName=ui->lineEdit_Name->text();
    myType=QString("%1").arg(ui->comboBox_Type->currentIndex());
    myNum=QString("%1").arg(ui->comboBox_Num->currentIndex());

    myAxisX=QString("%1").arg(ui->comboBox_Axi_idx->currentIndex());
    myAxisY=QString("%1").arg(ui->comboBox_Axi_idy->currentIndex());
    myAxisZ=QString("%1").arg(ui->comboBox_Axi_idz->currentIndex());
    myAxisU=QString("%1").arg(ui->comboBox_Axi_idu->currentIndex());

    if (write_tofile(path_config))
    {
        int maplen = mymap.size();
        myId =QString("%1").arg(maplen);
        ui->lineEdit_Id->setText(myId);
        ui->lineEdit_Name->clear();
        ui->comboBox_Num->setCurrentIndex(0);
    }
}

//从配置信息读取文件
void MainWindow::on_pushButton_readConfig_clicked()
{
    FILE*fp = fopen(path_config, "r");
    if (fp == NULL)
    {
        QMessageBox::warning(NULL,"error","读取配置信息失败!");
        myId=QString("0");
        return;
    }
    char buf[100] = { 0 };
    int count = 0;
    while (fgets(buf, sizeof(buf), fp))
    {
        count++;
    }
    fclose(fp);
    count /= 8;
    memset(buf, 0, sizeof(buf));
    char* ch = itoa(count, buf, 10);
    mymap.clear();
    read_fromfile(path_config, ch);

    initWorkspace();
}

//工站切换
void MainWindow::on_comboBox_workSpace_currentIndexChanged(const QString &arg1)
{

    int i = ui->comboBox_workSpace->currentIndex();

    QString val=mymap[QString("%1").arg(i)];
    char buf[100] = { 0 };
    strcpy(buf,val.toStdString().c_str());
    char *p=strtok(buf,";");
    for(int i=0;i<sizeof(arrystr)/sizeof(arrystr[0]);i++)
    {
        char kn[50], kv[50];
        sscanf(p, "%[^=]=%[^;]", kn, kv);
        *arrystr[i]=QString(kv);
        p = strtok(NULL, ";");
    }
    axi_x=myAxisX.toInt()+1;
    axi_y=myAxisY.toInt()+1;
    axi_z=myAxisZ.toInt()+1;
    axi_u=myAxisU.toInt()+1;

    workDetail(2);
}

//轴数量切换
void MainWindow::on_comboBox_Num_currentIndexChanged(const QString &arg1)
{
    int j=ui->comboBox_Num->currentIndex();
    switch(j)
    {
    case 0:
        ui->label_idy->hide();
        ui->label_idz->hide();
        ui->label_idu->hide();
        ui->comboBox_Axi_idy->hide();
        ui->comboBox_Axi_idz->hide();
        ui->comboBox_Axi_idu->hide();
        break;
    case 1:
        ui->label_idy->show();
        ui->label_idz->hide();
        ui->label_idu->hide();
        ui->comboBox_Axi_idy->show();
        ui->comboBox_Axi_idz->hide();
        ui->comboBox_Axi_idu->hide();
        break;
    case 2:
        ui->label_idy->show();
        ui->label_idz->show();
        ui->label_idu->hide();
        ui->comboBox_Axi_idy->show();
        ui->comboBox_Axi_idz->show();
        ui->comboBox_Axi_idu->hide();
        break;
    case 3:
        ui->label_idy->show();
        ui->label_idz->show();
        ui->label_idu->show();
        ui->comboBox_Axi_idy->show();
        ui->comboBox_Axi_idz->show();
        ui->comboBox_Axi_idu->show();
        break;
    default:
        break;

    }
}

//打开工站配置文件
void MainWindow::on_pushButton_openConfig_clicked()
{
    QProcess noteProcess;
    noteProcess.startDetached("notepad.exe",QStringList(path_config));
}

//速度切换
void MainWindow::on_comboBox_speed_currentIndexChanged(const QString &arg1)
{
    int i=ui->comboBox_speed->currentIndex();
    switch(i)
    {
    case 0:
        nowSpeed=speedGrade[0];
        break;
    case 1:
        nowSpeed=speedGrade[1];
        break;
    case 2:
        nowSpeed=speedGrade[2];
        break;
    case 4:
        nowSpeed=speedGrade[3];
        break;
deault:
        break;
    }
}


//运动微调模块
void MainWindow::on_pushButton_axix_zheng_pressed()
{
    if(initReult) jogAction(axi_x,nowSpeed);
}

void MainWindow::on_pushButton_axix_zheng_released()
{
    GT_Stop(1<<(axi_x-1),1<<(axi_x-1));
}

void MainWindow::on_pushButton_axix_fu_pressed()
{
    if(initReult) jogAction(axi_x,-nowSpeed);
}

void MainWindow::on_pushButton_axix_fu_released()
{
    GT_Stop(1<<(axi_x-1),1<<(axi_x-1));
}

void MainWindow::on_pushButton_axiy_zheng_pressed()
{
    if(initReult) jogAction(axi_y,nowSpeed);
}

void MainWindow::on_pushButton_axiy_zheng_released()
{
    GT_Stop(1<<(axi_y-1),1<<(axi_y-1));
}

void MainWindow::on_pushButton_axiy_fu_pressed()
{
    if(initReult) jogAction(axi_y,-nowSpeed);
}

void MainWindow::on_pushButton_axiy_fu_released()
{
    GT_Stop(1<<(axi_y-1),1<<(axi_y-1));
}

void MainWindow::on_pushButton_axiz_zheng_pressed()
{
    if(initReult) jogAction(axi_z,nowSpeed);
}

void MainWindow::on_pushButton_axiz_zheng_released()
{
    GT_Stop(1<<(axi_z-1),1<<(axi_z-1));
}

void MainWindow::on_pushButton_axiz_fu_pressed()
{
    if(initReult) jogAction(axi_z,-nowSpeed);
}

void MainWindow::on_pushButton_axiz_fu_released()
{
    GT_Stop(1<<(axi_z-1),1<<(axi_z-1));
}

void MainWindow::on_pushButton_axiu_zheng_pressed()
{
    if(initReult) jogAction(axi_u,nowSpeed);
}

void MainWindow::on_pushButton_axiu_zheng_released()
{
    GT_Stop(1<<(axi_u-1),1<<(axi_u-1));
}

void MainWindow::on_pushButton_axiu_fu_pressed()
{
    if(initReult) jogAction(axi_u,-nowSpeed);
}

void MainWindow::on_pushButton_axiu_fu_released()
{
    GT_Stop(1<<(axi_u-1),1<<(axi_u-1));
}

//复位功能
void MainWindow::on_pushButton_sysInit_clicked()
{
    short sRtn;
    TJogPrm  jog;

        // 打开运动控制器
        sRtn = GT_Open();

        // 复位运动控制器
        sRtn = GT_Reset();

        if(sRtn!=0)
        {
            QMessageBox::warning(NULL,"error","程序复位失败！");
        }


    // 配置运动控制器
    // 注意：配置文件取消了各轴的报警和限位
    sRtn = GT_LoadConfig("./test.cfg");

    // 清除各轴的报警和限位
    sRtn = GT_ClrSts(1, 8);

    // 伺服使能
    sRtn = GT_AxisOn(axi_x);
    if(axi_y!=0) sRtn = GT_AxisOn(axi_y);
    if(axi_z!=0) sRtn = GT_AxisOn(axi_z);
    if(axi_u!=0) sRtn = GT_AxisOn(axi_u);

    // 位置清零
    sRtn = GT_ZeroPos(axi_x);
    if(axi_y!=0) sRtn = GT_ZeroPos(axi_y);
    if(axi_z!=0) sRtn = GT_ZeroPos(axi_z);
    if(axi_u!=0) sRtn = GT_ZeroPos(axi_u);

    // AXIS轴规划位置清零
    sRtn = GT_SetPrfPos(axi_x, 0);
    if(axi_y!=0) sRtn = GT_SetPrfPos(axi_y, 0);
    if(axi_z!=0) sRtn = GT_SetPrfPos(axi_z, 0);
    if(axi_u!=0) sRtn = GT_SetPrfPos(axi_u, 0);

    // 将AXIS轴设为jog模式
    sRtn =GT_PrfJog(axi_x);
    if(axi_y!=0) sRtn =GT_PrfJog(axi_y);
    if(axi_z!=0) sRtn =GT_PrfJog(axi_z);
    if(axi_u!=0) sRtn =GT_PrfJog(axi_u);

    // 读取运动参数
    sRtn =GT_GetJogPrm(axi_x,&jog);
    if(axi_y!=0) sRtn =GT_GetJogPrm(axi_y,&jog);
    if(axi_z!=0) sRtn =GT_GetJogPrm(axi_z,&jog);
    if(axi_u!=0) sRtn =GT_GetJogPrm(axi_u,&jog);

    jog.acc=0.0625;
    jog.dec=0.0625;

    // 设置运动参数
    sRtn =GT_SetJogPrm(axi_x,&jog);
    if(axi_y!=0) sRtn =GT_SetJogPrm(axi_y,&jog);
    if(axi_z!=0) sRtn =GT_SetJogPrm(axi_z,&jog);
    if(axi_u!=0) sRtn =GT_SetJogPrm(axi_u,&jog);

    initReult=TRUE;

}

//系统急停
void MainWindow::on_pushButton_sysStop_clicked()
{
    myStop(1);
}

void MainWindow::on_pushButton_setProgram_clicked()
{
    QProcess noteProcess;
    noteProcess.startDetached("notepad.exe",QStringList(path_cwProgramList));
}

//启动项目
void MainWindow::on_pushButton_startProgram_clicked()
{
    QProcess myprocess;
    QString key=ui->comboBox_selProgram->currentText();
    QString program=programMap[key];
    myprocess.startDetached(program.replace("/","//"),QStringList(program.replace("/","//")));

}

//切换控制卡
void MainWindow::on_comboBox_exchangeCardid_currentIndexChanged(const QString &arg1)
{
    int cardIndex=ui->comboBox_exchangeCardid->currentIndex();
    cardId=cardIndex;
    int ret=GT_SetCardNo(cardId);
    if(ret!=0) QMessageBox::warning(NULL,"error","切换控制卡失败!");

    short sRtn;
    TJogPrm  jog;


    // 注意：配置文件取消了各轴的报警和限位
    sRtn = GT_LoadConfig("./test.cfg");

    // 清除各轴的报警和限位
    sRtn = GT_ClrSts(1, 8);

    // 伺服使能
    sRtn = GT_AxisOn(axi_x);
    if(axi_y!=0) sRtn = GT_AxisOn(axi_y);
    if(axi_z!=0) sRtn = GT_AxisOn(axi_z);
    if(axi_u!=0) sRtn = GT_AxisOn(axi_u);

    // 位置清零
    sRtn = GT_ZeroPos(axi_x);
    if(axi_y!=0) sRtn = GT_ZeroPos(axi_y);
    if(axi_z!=0) sRtn = GT_ZeroPos(axi_z);
    if(axi_u!=0) sRtn = GT_ZeroPos(axi_u);

    // AXIS轴规划位置清零
    sRtn = GT_SetPrfPos(axi_x, 0);
    if(axi_y!=0) sRtn = GT_SetPrfPos(axi_y, 0);
    if(axi_z!=0) sRtn = GT_SetPrfPos(axi_z, 0);
    if(axi_u!=0) sRtn = GT_SetPrfPos(axi_u, 0);

    // 将AXIS轴设为jog模式
    sRtn =GT_PrfJog(axi_x);
    if(axi_y!=0) sRtn =GT_PrfJog(axi_y);
    if(axi_z!=0) sRtn =GT_PrfJog(axi_z);
    if(axi_u!=0) sRtn =GT_PrfJog(axi_u);

    // 读取运动参数
    sRtn =GT_GetJogPrm(axi_x,&jog);
    if(axi_y!=0) sRtn =GT_GetJogPrm(axi_y,&jog);
    if(axi_z!=0) sRtn =GT_GetJogPrm(axi_z,&jog);
    if(axi_u!=0) sRtn =GT_GetJogPrm(axi_u,&jog);

    jog.acc=0.0625;
    jog.dec=0.0625;

    // 设置运动参数
    sRtn =GT_SetJogPrm(axi_x,&jog);
    if(axi_y!=0) sRtn =GT_SetJogPrm(axi_y,&jog);
    if(axi_z!=0) sRtn =GT_SetJogPrm(axi_z,&jog);
    if(axi_u!=0) sRtn =GT_SetJogPrm(axi_u,&jog);

    initReult=TRUE;
}

//点位运动
void MainWindow::on_pushButton_nextGo_clicked()
{
    double aimpos_x,aimpos_y,aimpos_z,aimpos_u;
    aimpos_x=ui->lineEdit_nextPosX->text().toDouble()*1000;
    if(aimpos_x!=0) trapAction(axi_x,nowSpeed,aimpos_x);

    aimpos_y=ui->lineEdit_nextPosY->text().toDouble()*1000;
    if(aimpos_y!=0) trapAction(axi_y,nowSpeed,aimpos_y);

    aimpos_z=ui->lineEdit_nextPosZ->text().toDouble()*1000;
    if(aimpos_z!=0) trapAction(axi_z,nowSpeed,aimpos_z);

    aimpos_u=ui->lineEdit_nextPosU->text().toDouble()*1000;
    if(aimpos_u!=0) trapAction(axi_u,nowSpeed,aimpos_u);
}

void MainWindow::on_lineEdit_nextStop_clicked()
{
    myStop(2);
}


//重置运动
void MainWindow::on_pushButton_isStop_clicked()
{
    myStop(2);
}

//工站回原
void MainWindow::on_pushButton_reWorkSpace_clicked()
{

    //找原点,点位运动模式
    if(axi_x!=0) trapAction(axi_x,nowSpeed,0);
    if(axi_y!=0) trapAction(axi_y,nowSpeed,0);
    if(axi_z!=0) trapAction(axi_z,nowSpeed,0);
    if(axi_u!=0) trapAction(axi_u,nowSpeed,0);

    //找原点,jog运动模式
//    double oldpos_x,oldpos_y,oldpos_z,oldpos_u;
//    oldpos_x=oldpos_y=oldpos_z=oldpos_u=0;
//    connect(timer,QTimer::timeout,[&](){
//        if(abs(nowPos_x)-abs(oldpos_x)>50)
//        {
//            nowSpeed=-nowSpeed;
//            jogAction(axi_x,nowSpeed);
//            oldpos_x=nowPos_x;
//        }
//        else GT_Stop(1<<(axi_x-1),1<<(axi_x-1));

//        if(abs(nowPos_y)-abs(oldpos_y)>50)
//        {
//            nowSpeed=-nowSpeed;
//            jogAction(axi_y,nowSpeed);
//            oldpos_y=nowPos_y;
//        }
//        else GT_Stop(1<<(axi_y-1),1<<(axi_y-1));

//        if(abs(nowPos_z)-abs(oldpos_z)>50)
//        {
//            nowSpeed=-nowSpeed;
//            jogAction(axi_z,nowSpeed);
//            oldpos_z=nowPos_z;
//        }
//        else GT_Stop(1<<(axi_z-1),1<<(axi_z-1));

//        if(abs(nowPos_u)-abs(oldpos_u)>50)
//        {
//            nowSpeed=-nowSpeed;
//            jogAction(axi_u,nowSpeed);
//            oldpos_u=nowPos_u;
//        }
//        else GT_Stop(1<<(axi_u-1),1<<(axi_u-1));
//    });
}

void MainWindow::on_pushButton_reAix_x_clicked()
{
    if(axi_x!=0) trapAction(axi_x,nowSpeed,0);
}

void MainWindow::on_pushButton_reAix_y_clicked()
{
    if(axi_y!=0) trapAction(axi_y,nowSpeed,0);
}

void MainWindow::on_pushButton_reAix_z_clicked()
{
   if(axi_z!=0) trapAction(axi_z,nowSpeed,0);
}

void MainWindow::on_pushButton_reAix_u_clicked()
{
    if(axi_u!=0) trapAction(axi_u,nowSpeed,0);
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{

    globalPos=event->globalPos();
//    qDebug()<<ui->frame->parentWidget()->mapToGlobal(ui->frame->pos());
//    qDebug()<<ui->frame->pos();
//    qDebug()<<globalPos;
    if(isContain(ui->frame,ui->frame->parentWidget(),globalPos,0))
    {
        for(int i=0;i<16;i++)
        {
            if(isContain(btngroup_sigin.button(i),ui->frame_5,this->globalPos,0))
            {
                if(bg_sigin[i]=='1')
                {
                    isNormal->setIcon(QIcon(":/new/prefix1/select.bmp"));
                    isOpposite->setIcon(QIcon(":/new/prefix1/blank.bmp"));
                }
                else
                {
                    isNormal->setIcon(QIcon(":/new/prefix1/blank.bmp"));
                    isOpposite->setIcon(QIcon(":/new/prefix1/select.bmp"));
                }
            }
            else if(isContain(btngroup_sigout.button(i),ui->frame_12,this->globalPos,0))
            {
                if(bg_sigout[i]=='1')
                {
                    isNormal->setIcon(QIcon(":/new/prefix1/select.bmp"));
                    isOpposite->setIcon(QIcon(":/new/prefix1/blank.bmp"));
                }
                else
                {
                    isNormal->setIcon(QIcon(":/new/prefix1/blank.bmp"));
                    isOpposite->setIcon(QIcon(":/new/prefix1/select.bmp"));
                }
            }
            else if((i<8)&& isContain(btngroup_sigzheng.button(i),ui->frame_4,this->globalPos,0))
            {
                if(bg_sigzheng[i]=='1')
                {
                    isNormal->setIcon(QIcon(":/new/prefix1/select.bmp"));
                    isOpposite->setIcon(QIcon(":/new/prefix1/blank.bmp"));
                }
                else
                {
                    isNormal->setIcon(QIcon(":/new/prefix1/blank.bmp"));
                    isOpposite->setIcon(QIcon(":/new/prefix1/select.bmp"));
                }
            }
            else if((i<8) && isContain(btngroup_sigfu.button(i),ui->frame_7,this->globalPos,0))
            {
               if(bg_sigfu[i]=='1')
               {
                   isNormal->setIcon(QIcon(":/new/prefix1/select.bmp"));
                   isOpposite->setIcon(QIcon(":/new/prefix1/blank.bmp"));
               }
               else
               {
                   isNormal->setIcon(QIcon(":/new/prefix1/blank.bmp"));
                   isOpposite->setIcon(QIcon(":/new/prefix1/select.bmp"));
               }
            }
            else if((i<8) && isContain(btngroup_sigyuan.button(i),ui->frame_8,this->globalPos,0))
            {
                if(bg_sigyuan[i]=='1')
                {
                    isNormal->setIcon(QIcon(":/new/prefix1/select.bmp"));
                    isOpposite->setIcon(QIcon(":/new/prefix1/blank.bmp"));
                }
                else
                {
                    isNormal->setIcon(QIcon(":/new/prefix1/blank.bmp"));
                    isOpposite->setIcon(QIcon(":/new/prefix1/select.bmp"));
                }
            }
            else if((i<8) && isContain(btngroup_dalarm.button(i),ui->frame_9,this->globalPos,0))
            {
                if(bg_sigdalarm[i]=='1')
                {
                    isNormal->setIcon(QIcon(":/new/prefix1/select.bmp"));
                    isOpposite->setIcon(QIcon(":/new/prefix1/blank.bmp"));
                }
                else
                {
                    isNormal->setIcon(QIcon(":/new/prefix1/blank.bmp"));
                    isOpposite->setIcon(QIcon(":/new/prefix1/select.bmp"));
                }
            }
            else if((i<8) && isContain(btngroup_tomcan.button(i),ui->frame_10,this->globalPos,0))
            {
                if(bg_sigtomcan[i]=='1')
                {
                    isNormal->setIcon(QIcon(":/new/prefix1/select.bmp"));
                    isOpposite->setIcon(QIcon(":/new/prefix1/blank.bmp"));
                }
                else
                {
                    isNormal->setIcon(QIcon(":/new/prefix1/blank.bmp"));
                    isOpposite->setIcon(QIcon(":/new/prefix1/select.bmp"));
                }
            }
            else if((i<8) && isContain(btngroup_alclear.button(i),ui->frame_11,this->globalPos,0))
            {
                if(bg_sigalclear[i]=='1')
                {
                    isNormal->setIcon(QIcon(":/new/prefix1/select.bmp"));
                    isOpposite->setIcon(QIcon(":/new/prefix1/blank.bmp"));
                }
                else
                {
                    isNormal->setIcon(QIcon(":/new/prefix1/blank.bmp"));
                    isOpposite->setIcon(QIcon(":/new/prefix1/select.bmp"));
                }
            }
        }
        rightMenu->exec(globalPos);
    }




}


bool MainWindow::isContain(QWidget *obj,QWidget*parent,QPoint globalpoint,int border)
{
    int w=obj->width();
    int h=obj->height();
    QPoint leftTop=parent->mapToGlobal(obj->pos());
    QRect includeArea(leftTop.rx(),leftTop.ry(),w,h);
    if(includeArea.contains(globalpoint)) return true;
    return false;
}

bool MainWindow::signalFlag()
{
    QFile file(path_signalInfo);
       if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
       {
           QMessageBox::warning(NULL,"error","打开信号配置文件失败!");
           return false;
       }
       QTextStream txtin(&file);
       txtin >>bg_sigin
               >>bg_sigout
               >>bg_sigzheng
               >>bg_sigfu
               >>bg_sigyuan
               >>bg_sigdalarm
               >>bg_sigtomcan
               >>bg_sigalclear;
       file.close();
}


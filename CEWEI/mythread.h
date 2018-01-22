#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include <QButtonGroup>
#include <QDebug>
#include <windows.h>
#include <QVector>
#include "gts.h"
#include <QPushButton>
#include <QTimer>

class MyThread : public QThread
{
public:
    MyThread();
    virtual void run();
};

#endif // MYTHREAD_H

/*==================================
*   Copyright (C) 2016 All rights reserved.
*   
*   文件名称：t05_nonlock_thread_pool.cpp
*   创 建 者：薛国良
*   创建日期：2016年10月29日
*   描    述：
*
================================================================*/

#include "h.h"
#include <list>
#include<algorithm>
using namespace std;

// 描述线程属性的
// 修改线程属性，只在主线程中进行
typedef struct thread
{
    int fdThread;
    int fdMain;
    int Running;
    // 该队列只有在子线程休眠时，主线程才访问该队列，所以是线程安全的
    list<int>* queue;
    int index;
    pthread_t tid;
} thread;

// 保存正在运行的线程和休眠的线程
// 这个结构只有主线程在访问
list<thread*> runningThread;
list<thread*> sleepingThread;

// 通过popen获得命令的输出
int get_cpu_count()
{
    FILE* fp = popen("cat /proc/cpuinfo | grep processor | wc -l", "r");
    char buf[1024];
    memset(buf, 0, sizeof(buf));
    fread(buf, 1, sizeof(buf), fp);
    pclose(fp);
    return atoi(buf);
}

// 工作线程和之前的单线程的工作线程没有区别
void* work_thread(void* ptr)
{
    thread* t = (thread*)ptr;
    char ch;

    while(1)
    {
        // 通知主线程，本宝宝要睡觉了
        write(t->fdThread, &ch, 1);
        // 阻塞等待主线程的通知
        read(t->fdThread, &ch, 1);

        while(t->queue->size() > 0)
        {
            int task = t->queue->front();
            t->queue->pop_front();

            printf("task is %d, thread id = 0x%x\n", task, (int)pthread_self());
        }
    }
}

// 创建一个线程
void create_thread(int i)
{
    thread* t = new thread;
    int fd[2];
    socketpair(AF_UNIX, SOCK_STREAM, 0, fd);
    t->fdThread = fd[0];
    t->fdMain = fd[1];
    t->Running = 1;
    t->queue = new list<int>;
    t->index = i;

    runningThread.push_back(t);

    pthread_create(&t->tid, NULL, work_thread, t);
}

// a.out [threadcount]
// a.out xxxx
int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("usage: %s [thread_count]\n", argv[0]);
        return 0;
    }

    // 获得线程数量
    int threadCount = atoi(argv[1]);
    if(threadCount == 0)
    {
        int cpuCount = get_cpu_count();
        printf("cpuCount is %d\n", cpuCount);
        threadCount = cpuCount * 2;
    }

    // 主线程临时缓存任务的队列
    list<int>* mainQueue = new list<int>;


    // 创建多个线程
    for(int i=0; i<threadCount; ++i)
    {
        create_thread(i);
    }

    char ch;
    // 多路复用，监控标准输入和线程的通知信息
    while(1)
    {
        int maxfd = STDIN_FILENO;
        fd_set set;
        FD_ZERO(&set);
        FD_SET(STDIN_FILENO, &set);
        





        for_each(runningThread.begin(),runningThread.end(),[&](thread*t)
        {
            FD_SET(t->fdMain, &set);
            // 找最大的文件描述符
            if(t->fdMain > maxfd) maxfd = t->fdMain;
        });

/*
        for(list<thread*>::iterator it = runningThread.begin();
                it != runningThread.end();
                ++it)
        {
            thread* t = *it;
            FD_SET(t->fdMain, &set);
            // 找最大的文件描述符
            if(t->fdMain > maxfd) maxfd = t->fdMain;
        }

*/






        int ret = select(maxfd+1, &set, NULL, NULL, NULL);
        if(ret > 0)
        {
            if(FD_ISSET(STDIN_FILENO, &set))
            {
                // 有外部任务
                char buf[100];
                fgets(buf, sizeof(buf), stdin);
                int task = atoi(buf);
                mainQueue->push_back(task);

                // 检查一下工人，是不是闲着的
                if(sleepingThread.size() > 0)
                {
                    thread* t = sleepingThread.front();
                    sleepingThread.pop_front();
                    // 下一次select监听就会监听该线程
                    runningThread.push_back(t);
                    t->Running = 1;
                    // 唤醒
                    write(t->fdMain, &ch, 1);
                }
            }

            for(auto it = runningThread.begin();
                    it != runningThread.end();)
            {
                thread* t = *it;
                // 如果thread->fdMain在集合set中，那说明该线程由运行转入到休眠
                if(FD_ISSET(t->fdMain, &set))
                {
                    // 读走通知消息，这个很重要
                    read(t->fdMain, &ch, 1);
                    // 如果包工头有任务，那么交换任务列表
                    if(mainQueue->size() > 0)
                    {
                        // 交换任务列表
                        list<int>* tmp = mainQueue;
                        mainQueue = t->queue;
                        t->queue = tmp;

                        // 唤醒
                        write(t->fdMain, &ch, 1);
                    }
                    else
                    {
                        // 便利list时，删除list中的元素，是不安全的
                        it = runningThread.erase(it);
                        sleepingThread.push_back(t);
                        t->Running = 0;
                        continue;
                    }
                }

                ++it;
            }
        }
    }
}















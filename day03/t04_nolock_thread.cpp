#include "h.h"
#include<list>
using namespace std;

list<int>*queueMain;
list<int>*queueThread;
int fdMain;
int fdThread;

int threadRunning=1;

void*thread_func(void*arg)
{
    char tmp;
    while(1)
    {
        write(fdThread,&tmp,1);
        read(fdThread,&tmp,1);
        while(1)
        {
            if(queueThread->size()==0) break;
            int task=queueThread->front();
            printf("task is %d\n",task);
            queueThread->pop_front();
        }
    }
}


int main()
{
    list<int>queue1;
    list<int>queue2;
    queueMain=&queue1;
    queueThread=&queue2;

    int fd[2];

    socketpair(AF_UNIX,SOCK_STREAM,0,fd);
    fdMain=fd[0];
    fdThread=fd[1];

    pthread_t tid;
    pthread_create(&tid,NULL,thread_func,NULL);

    char tmp;



    while(1)
    {
        fd_set set;
        FD_ZERO(&set);
        FD_SET(fdMain,&set);
        FD_SET(STDIN_FILENO,&set);
        int ret=select(fdMain+1,&set,NULL,NULL,0);
        if(ret>0)
        {
            if(FD_ISSET(STDIN_FILENO,&set))
            {
                char buf[1024];
                fgets(buf,sizeof(buf),stdin);
                int task=atoi(buf);
                queueMain->push_back(task);

                if(threadRunning==0)
                {
                    write(fdMain,&tmp,1);
                    threadRunning=1;
                }
            }
            if(FD_ISSET(fdMain,&set))
            {
                read(fdMain,&tmp,1);

                if(queueMain->size())
                {
                    list<int>*ltmp;
                    ltmp=queueMain;
                    queueMain=queueThread;
                    queueThread=ltmp;

                    write(fdMain,&tmp,1);
                }
                else
                {
                    threadRunning=0;
                }
            }

        }
    }

}

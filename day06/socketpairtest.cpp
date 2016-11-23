#include "h.h"
#include <list>
using namespace std;
list<int>*queueMain;
list<int>*queueThread;
int fdMain;
int fdThread;
int threadRunning=1;
char buf[1024]={0};

void*thread_func(void*arg)
{
	char tmp;
	while(1)
	{
		write(fdThread,&tmp,sizeof(tmp));
		read(fdThread,&tmp,sizeof(tmp));
		while(queueThread->size()>0)
		{
			int task=queueThread->front();
			queueThread->pop_front();
			printf("task is %d\n",task);
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
	fd_set set;
	while(1)
	{
		FD_ZERO(&set);
		FD_SET(STDIN_FILENO,&set);
		FD_SET(fdMain,&set);

		int ret=select(fdMain+1,&set,NULL,NULL,0);
		if(ret<0)
		{
			perror("select error");
			return -1;
		}
		if(ret==0)
		{
			printf("Nothing happened\n");
		}
		else
		{
			if(FD_ISSET(STDIN_FILENO,&set))
			{
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
				if(queueMain->size()>0)
				{
					list<int>*lt=queueMain;
					queueMain=queueThread;
					queueThread=lt;
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

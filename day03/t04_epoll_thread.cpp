/* ************************************************************************
 *       Filename:  t04_epoll_thread.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/05/2016 01:25:12 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "../h.h"
#include <list>
using namespace std;

int epollfd;
void recv_data(int fd)
{
	char buf[1024];
	int ret=read(fd,buf,sizeof(buf));
	if(ret==0)
	{
		close(fd);
		return;
	}

	printf("%s\n",buf);
	struct epoll_event ev;
	ev.data.fd=fd;
	ev.events=EPOLLIN|EPOLLONESHOT;

	epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&ev);
}

list<int>msg_fds;
pthread_mutex_t mutex;
sem_t sem;

void*work_thread(void*ptr)
{
	while(1)
	{
		int ret=sem_wait(&sem);
		if(ret<0)
		{
			if(errno=EINTR)
				continue;
			exit(1);
		}

		pthread_mutex_lock(&mutex);
		if(msg_fds.size()==0)
		{
			pthread_mutex_unlock(&mutex);
			continue;
		}
		int fd=msg_fds.front();
		msg_fds.pop_front();
		pthread_mutex_unlock(&mutex);

		recv_data(fd);
	}
}

int main()
{
	pthread_mutex_init(&mutex,NULL);
	sem_init(&sem,0,0);
	pthread_t tid;
	pthread_create(&tid,NULL,work_thread,NULL);

	int fd=socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(9988);
	addr.sin_addr.s_addr=INADDR_ANY;

	int ret=bind(fd,(struct sockaddr*)&addr,sizeof(addr));
	if(ret<0)
	{
		perror("bind error");
		return 1;
	}

	listen(fd,20);
	epollfd=epoll_create(512);

	struct epoll_event ev;
	ev.data.fd=fd;
	ev.events=EPOLLIN;
	epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&ev);

	while(1)
	{
		struct epoll_event out_ev[8];
		int ret=epoll_wait(epollfd,out_ev,8,2000);
		if(ret>0)
		{
			int i;
			for(i=0;i<ret;++i)
			{
				struct epoll_event*p=&out_ev[i];
				if(p->data.fd==fd)
				{
					int newfd=accept(fd,NULL,NULL);
					ev.data.fd=newfd;
					ev.events=EPOLLIN|EPOLLONESHOT;
					epoll_ctl(epollfd,EPOLL_CTL_ADD,newfd,&ev);

				}
				else
				{
					pthread_mutex_lock(&mutex);
					msg_fds.push_back(p->data.fd);
					pthread_mutex_unlock(&mutex);

					sem_post(&sem);
				}
			}
		}
	}

	pthread_join(tid,NULL);
}

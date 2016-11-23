/* ************************************************************************
 *       Filename:  epoll.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/04/2016 09:05:22 AM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
int main()
{
	char buf[4096];
	int readlen=0;
	int fd_mice=open("/dev/input/mice",O_RDONLY);
	if(fd_mice<0)
	{
		perror("mice error");
		return -1;
	}
	int fd_keyb=open("/dev/input/event1",O_RDONLY);
	if(fd_keyb<0)
	{
		perror("keyb error");
		return -1;
	}

	int epollfd=epoll_create(512);
	struct epoll_event ev;
	ev.events=EPOLLIN;
	ev.data.fd=fd_mice;
	int ret=epoll_ctl(epollfd,EPOLL_CTL_ADD,fd_mice,&ev);

	ev.evens=EPOLLIN;
	ev.data.fd=fd_keyb;
	ret=epoll_ctl(epollfd,EPOLL_CTL_ADD,fd_keyb,&ev);

	if(ret<0)
	{
		perror("epoll_ctl error");
		return -1;
	}

	struct epoll_event fd_events[2];

	while(1)
	{
		int ret=epoll_wait(epollfd,fd_events,2,2000);
		if(ret<0)
		{
			if(errno==EINTR)
				continue;
			else
				exit(1);
		}
		if(ret==0)
			printf("nothing happened\n");
		else
		{
			for(int i=0;i<ret;i++)
			{
				struct epoll_event*p=&fd+events[i];
				if(p->data.fd==fd_mice)
				{
					readlen=read(fd_mice,buf,sizeof(buf));
					printf("mouse event %d\n",readlen);
				}
				else if(p->data.fd==fd_keyb)
				{
					readlen=read(fd_keyb,buf,sizeof(buf));
					printf("keyoard event %d\n",readlen);
				}
			}
		}
	}
}



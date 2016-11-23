/* ************************************************************************
 *       Filename:  epolltest.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/01/2016 08:37:58 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
int main()
{
	char buf[4096]={0};
	int readlen=0;
	int fd_mice=open("/dev/input/mice",O_RDONLY);
	if(fd_mice<0)
	{
		perror("mice error");
	}
	int fd_keyb=open("/dev/input/event1",O_RDONLY);
	if(fd_keyb<0)
	{
		perror("fd_keyb error");
	}

	int epollfd=epoll_create(512);

	struct epoll_event ev;
	ev.events=EPOLLIN;
	ev.data.fd=fd_mice;
	int ret=epoll_ctl(epollfd,EPOLL_CTL_ADD,fd_mice,&ev);
	if(ret<0)
	{
		perror("epoll_ctr error");
		return -1;
	}

	ev.data.fd=fd_keyb;
	ret=epoll_ctl(epollfd,EPOLL_CTL_ADD,fd_keyb,&ev);
	if(ret<0)
	{
		perror("epoll_ctr error");
		return -1;
	}

	struct epoll_event fd_events[2];

	while(1)
	{
		int ret= epoll_wait(epollfd,fd_events,2,2000);
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
				struct epoll_event*p=&fd_events[i];
				if(p->data.fd==fd_mice)
				{
					readlen=read(fd_mice,buf,sizeof(buf));
					printf("mouse event %d\n",readlen);
				}
				else if(p->data.fd==fd_keyb)
				{
					readlen=read(fd_keyb,buf,sizeof(buf));
					printf("keyboard event %d\n",readlen);

				}
			}
		}
	}
	

}

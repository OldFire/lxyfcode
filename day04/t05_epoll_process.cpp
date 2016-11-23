/* ************************************************************************
 *       Filename:  t05_epoll_process.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/05/2016 06:35:03 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/


#include "../h.h"
int main()
{
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

	int process_count=20;
	int isParent=1;
	for(int i=0;i<process_count;++i)
	{
		pid_t pid=fork();
		if(pid==0)
		{
			isParent=0;
			break;
		}
	}

	int epollfd=epoll_create(512);

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
			for(int i=0;i<ret;++i)
			{
				struct epoll_event*p=&out_ev[i];
				if(p->data.fd==fd)
				{
					int newfd=accept(fd,NULL,NULL);
					ev.data.fd=newfd;
					epoll_ctl(epollfd,EPOLL_CTL_ADD,newfd,&ev);
				}
				else
				{
					char buf[1024];
					int ret=recv(p->data.fd,buf,sizeof(buf),0);
					if(ret>0)  printf("%s\n",buf);
					else
					{
						close(p->data.fd);
					}
				}
			}
		}
	}

	if(isParent)
	{
		for(int i=0;i<process_count;i++)
		{
			wait(NULL);
		}
	}
}


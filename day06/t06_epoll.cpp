/* ************************************************************************
 *       Filename:  t06_epoll.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/05/2016 07:06:58 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "../h.h"

void set_non_block(int fd)
{
	uint32_t flags;
	flags=fcntl(fd,F_GETFL);
	flags|=O_NONBLOCK;
	fcntl(fd,F_SETFL,flags);
}

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

	set_non_block(fd);
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
			for(int i=0;i<ret;i++)
			{
				struct epoll_event*p=&out_ev[i];
				if(p->data.fd==fd)
				{
					while(1)
					{
						int newfd=accept(fd,NULL,NULL);
						if(newfd<0)
						{
							if(errno==EAGAIN)
								break;
							else
								exit(1);
						}
						ev.data.fd=newfd;
						set_non_block(newfd);
						ev.events=EPOLLIN|EPOLLET;
						epoll_ctl(epollfd,EPOLL_CTL_ADD,newfd,&ev);
					}
				}
				else
				{
					printf("socket has data,but not recv\n");
					char buf[1024];
					while(1)
					{
						int ret=read(p->data.fd,buf,sizeof(buf));
						if(ret>0)
						{
							printf("%s\n",buf);
						}
						else if(ret<0)
						{
							if(errno==EAGAIN)
							{
								break;
							}
							else
							{
								close(p->data.fd);
							}
						}
						else
						{
							close(p->data.fd);
						}
					}
				}
			}
		}
	}

}




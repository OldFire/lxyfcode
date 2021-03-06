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

#define PROCESS_COUNT 5 //所要创建的进程数
#define create_daemon(){ \
	if(fork()==0) setsid(); \
	else exit(0); \
	if(fork()!=0) exit(0); \
	}


void set_non_block(int fd)
{
	uint32_t flags;
	flags=fcntl(fd,F_GETFL);
	flags|=O_NONBLOCK;
	fcntl(fd,F_SETFL,flags);
}

int main()
{
	create_daemon();

	signal(SIGCHLD,SIG_IGN);
	signal(SIGINT,SIG_IGN);
	signal(SIGHUP,SIG_IGN);
	signal(SIGPIPE,SIG_IGN);
	signal(SIGTTOU,SIG_IGN);
	signal(SIGQUIT,SIG_IGN);
	signal(SIGTSTP,SIG_IGN);  //ctrl + Z退出
	
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

	//创建多进程任务
	int isParent=1;
	for(int i=0;i<PROCESS_COUNT;++i)
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
							if(errno==EAGAIN||errno==EINTR)
								break;
							else
								exit(1);
						}
						printf("has new client...\n");
						send(newfd,"hello client...\n",20,0);
						ev.data.fd=newfd;
						set_non_block(newfd);
						ev.events=EPOLLIN|EPOLLET|EPOLLOUT;
						epoll_ctl(epollfd,EPOLL_CTL_ADD,newfd,&ev);
					}
				}
				else
				{
					char buf[1024];
					while(1)
					{
						int ret=read(p->data.fd,buf,sizeof(buf));
						if(ret>0)
						{
							printf("Servrecv:%s\n",buf);
							send(p->data.fd,buf,ret,0);
							bzero(buf,sizeof(buf));
						}
						else if(ret<=0)
						{
							if(errno==EAGAIN||EINTR) break;
							epoll_ctl(epollfd,EPOLL_CTL_DEL,p->data.fd,&ev);
							close(p->data.fd);
							break;
						}
					}
				}
			}
		}
	}

	if(isParent)
	{
		for(int i=0;i<PROCESS_COUNT;i++)
		{
			waitpid(-1,NULL,WNOHANG);
		}
	}
	close(epollfd);

}




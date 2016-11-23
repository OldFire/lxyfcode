/* ************************************************************************
 *       Filename:  t03_select_server.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/05/2016 01:08:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "../h.h"

fd_set newfds;

int maxfd;

void recv_data(int sock)
{
	char buf[1024];
	int ret=recv(sock,buf,sizeof(buf),0);
	if(ret==0)
	{
		printf("client close socket\n");
		close(sock);

		FD_CLR(sock,&newfds);
		if(sock==maxfd) maxfd--;
		return;
	}
	printf("%s\n",buf);
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

	FD_ZERO(&newfds);
	FD_SET(fd,&newfds);
	maxfd=fd;

	while(1)
	{
		fd_set set;
		memcpy(&set,&newfds,sizeof(set));

		struct timeval tv;
		tv.tv_sec=2;
		tv.tv_usec=0;
		int ret=select(maxfd+1,&set,NULL,NULL,&tv);
		if(ret>0)
		{
			if(FD_ISSET(fd,&set))
			{
				int newfd=accept(fd,NULL,NULL);
				FD_SET(newfd,&newfds);
				if(newfd>maxfd) maxfd=newfd;

				FD_CLR(fd,&set);
			}
			int sock;
			for(sock=3;sock<=maxfd;sock++)
			{
				if(FD_ISSET(sock,&set))
				{
					recv_data(sock);
				}
			}

		}
	}


}


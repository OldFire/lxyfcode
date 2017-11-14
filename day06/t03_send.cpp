/* ************************************************************************
 *       Filename:  to3_send.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/31/2016 06:44:08 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "../h.h"

int main(int argc,char*argv[])
{
	int fd=socket(AF_INET,SOCK_STREAM,0);
	if(argc!=3)
	{
		printf("usage [%s] [addr] [port]...\n",argv[0]);
		return -1;
	}
	int port=atoi(argv[2]);
	char *address=argv[1];

	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(port);
	addr.sin_addr.s_addr=inet_addr(address);

	int ret=connect(fd,(struct sockaddr*)&addr,sizeof(addr));
	
	if(ret<0)
	{
		printf("server is no ACK...\n");
		return -1;
	}

	fd_set set;
	while(1)
	{
		FD_ZERO(&set);
		FD_SET(STDIN_FILENO,&set);
		FD_SET(fd,&set);

		select(fd+1,&set,NULL,NULL,0);

		if(FD_ISSET(STDIN_FILENO,&set))
		{
			char temp[1024]={0};
			fgets(temp,sizeof(temp),stdin);
			send(fd,temp,sizeof(temp),0);

		}
		if(FD_ISSET(fd,&set))
		{
			char buf[1024]={0};
			int ret=recv(fd,buf,sizeof(buf),0);
			if(ret==0) break;
			printf("Clientrecv:%s\n",buf);
		}
	}
	return 0;

}



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

#include "h.h"

int main()
{
	int fd=socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(6666);
	addr.sin_addr.s_addr=inet_addr("127.0.0.1");

	connect(fd,(struct sockaddr*)&addr,sizeof(addr));

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
			printf("recv:%s",buf);
		}
	}
	return 0;

}



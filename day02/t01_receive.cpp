/* ************************************************************************
 *       Filename:  t01_receive.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/30/2016 08:59:55 AM
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
	addr.sin_port=htons(9989);
	addr.sin_addr.s_addr=INADDR_ANY;

	bind(fd,(struct sockaddr*)&addr,sizeof(addr));
	listen(fd,10);
	
	char buf[1024];
	int newfd=accept(fd,NULL,NULL);

	recv(newfd,buf,sizeof(buf),0);
	printf("recv:%s\n",buf);
	close(newfd);
	close(fd);
	return 0;
}

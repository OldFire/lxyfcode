/* ************************************************************************
 *       Filename:  t01_send.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/30/2016 08:53:35 AM
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
	addr.sin_addr.s_addr=inet_addr("127.0.0.1");

	connect(fd,(struct sockaddr*)&addr,sizeof(addr));

	char buf[]="hello, server";

	send(fd,buf,sizeof(buf),0);
	close(fd);
	return 0;
}

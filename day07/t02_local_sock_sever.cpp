/* ************************************************************************
 *       Filename:  t02_local_sock_sever.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/04/2016 09:03:45 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "../h.h"
int main()
{
	int fd=socket(AF_UNIX,SOCK_STREAM,0);

	struct sockaddr_un addr;
	addr.sun_family=AF_UNIX;
	strcpy(addr.sun_path,"socket_file");
	bind(fd,(struct sockaddr*)&addr,sizeof(addr));
	listen(fd,10);

	int newfd=accept(fd,NULL,NULL);
	char buf[1024];
	recv(newfd,buf,sizeof(buf),0);
	printf("%s\n",buf);
	return 0;
}



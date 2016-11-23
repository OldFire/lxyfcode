/* ************************************************************************
 *       Filename:  t01http_server_test.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/08/2016 08:39:56 PM
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
	addr.sin_port=htons(9889);
	addr.sin_addr.s_addr=INADDR_ANY;

	bind(fd,(struct sockaddr*)&addr,sizeof(addr));

	listen(fd,10);

	int newfd=accept(fd,NULL,NULL);

	char buf[8192];
	read(newfd,buf,sizeof(buf));

	printf("%s\n",buf);

	while(1)
	{
		sleep(1);
	}
}



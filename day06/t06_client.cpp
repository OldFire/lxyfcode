/* ************************************************************************
 *       Filename:  t06_client.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/05/2016 07:06:58 PM
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
	addr.sin_addr.s_addr=inet_addr("127.0.0.1");

	connect(fd,(struct sockaddr*)&addr,sizeof(addr));
	send(fd,"hello",6,0);
	sleep(1);
	send(fd,"h",2,0);
	while(1)
	{
		sleep(1);
	}
	close(fd);
	return 0;
}

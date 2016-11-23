/* ************************************************************************
 *       Filename:  t01_udp_recv.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/04/2016 07:12:10 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "../h.h"
int main()
{
	int socketfd= socket(AF_INET,SOCK_DGRAM,0);
	
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(8888);
	addr.sin_addr.s_addr=INADDR_ANY;

	bind(socketfd,(struct sockaddr*)&addr,sizeof(addr));

	char buf[1024];
	memset(buf,0,sizeof(buf));
	recv(socketfd,buf,sizeof(buf),0);
	
	printf("buf is: %s\n",buf);
	close(socketfd);
	return 0;
	
}


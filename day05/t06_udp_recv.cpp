/* ************************************************************************
 *       Filename:  t06_udp_recv.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/04/2016 08:45:43 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "../h.h"

int main()
{
	int sock=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(9988);
	addr.sin_addr.s_addr=INADDR_ANY;

	int ret=bind(sock,(struct sockaddr*)&addr,sizeof(addr));

	struct sockaddr from;
	socklen_t len=sizeof(from);

	char buf[1024];
	memset(buf,0,sizeof(buf));
	recvfrom(sock,buf,sizeof(buf),0,&from,&len);
	printf("buf is %s\n",buf);

	sendto(sock,"from server",sizeof("from server"),0,&from,len);
	close(sock);
	return 0;
}



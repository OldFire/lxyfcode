/* ************************************************************************
 *       Filename:  t04_udp_broadcast_recv.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/04/2016 07:58:59 PM
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

	char buf[1024];
	memset(buf,0,sizeof(buf));
	recv(sock,buf,sizeof(buf),0);
	printf("buf is: %s\n",buf);
	close(sock);
	return 0;
}



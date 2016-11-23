/* ************************************************************************
 *       Filename:  t06_udp_send.cpp
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
	addr.sin_addr.s_addr=inet_addr("127.0.0.1");

	char buf[1024]="hello bdp";
	sendto(sock,buf,sizeof(buf),0,(struct sockaddr*)&addr,
			sizeof(addr));
	struct sockaddr fromaddr;
	socklen_t len=sizeof(fromaddr);

	recvfrom(sock,buf,sizeof(buf),0,&fromaddr,&len);
	printf("recv data %s\n",buf);

	return 0;
}




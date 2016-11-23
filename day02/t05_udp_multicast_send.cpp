/* ************************************************************************
 *       Filename:  t05_udp_multicast_send.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/04/2016 08:24:36 PM
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
	addr.sin_addr.s_addr=inet_addr("224.0.0.100");

	char buf[]="hello mulit";
	sendto(sock,buf,sizeof(buf),0,(struct sockaddr*)&addr,
			sizeof(addr));
	return 0;
}



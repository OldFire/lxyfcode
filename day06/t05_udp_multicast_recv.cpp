/* ************************************************************************
 *       Filename:  t05_udp_multicast_recv.cpp
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
	addr.sin_addr.s_addr=INADDR_ANY;

	int ret=bind(sock,(struct sockaddr*)&addr,
			sizeof(addr));

	//join the group of multicast
	struct ip_mreq merq;
	//join the address of multicast
	merq.imr_multiaddr.s_addr=inet_addr("224.0.0.100");
	//the interface of receive
	merq.imr_interface.s_addr=INADDR_ANY;

	ret=setsockopt(sock,IPPROTO_IP,IP_ADD_MEMBERSHIP,
			&merq,sizeof(merq));

	char buf[1024];
	memset(buf,0,sizeof(buf));
	recv(sock,buf,sizeof(buf),0);

	printf("buf is:%s\n",buf);
	close(sock);
	return 0;

}



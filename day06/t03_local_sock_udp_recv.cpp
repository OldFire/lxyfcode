/* ************************************************************************
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
	int fd=socket(AF_UNIX,SOCK_DGRAM,0);

	struct sockaddr_un addr;
	addr.sun_family=AF_UNIX;
	strcpy(addr.sun_path,"udp1");

	bind(fd,(struct sockaddr*)&addr,sizeof(addr));
	
	char buf[1024];
	struct sockaddr peer_addr;
	socklen_t len=sizeof(peer_addr);
	
	recvfrom(fd,buf,sizeof(buf),0,&peer_addr,&len);
	printf("%s\n",buf);

	sendto(fd,"ack info",8,0,&peer_addr,len);
	close(fd);
	return 0;
}



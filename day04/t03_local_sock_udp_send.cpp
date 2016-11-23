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
	strcpy(addr.sun_path,"udp2");

	bind(fd,(struct sockaddr*)&addr,sizeof(addr));
	
	strcpy(addr.sun_path,"udp1");
	sendto(fd,"hello",5,0,(struct sockaddr*)&addr,sizeof(addr));

	char buf[1024];
	recv(fd,buf,sizeof(buf),0);

	printf("%s\n",buf);
	close(fd);
	return 0;
}



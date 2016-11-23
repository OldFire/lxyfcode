/* ************************************************************************
 *       Filename:  t01_udp_send.cpp
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
	addr.sin_addr.s_addr=inet_addr("127.0.0.1");

	//if use connect that needn't use sendto 
	//otherwise you must use sendto
	connect(socketfd,(struct sockaddr*)&addr,sizeof(addr));

	char buf[1024]="hello udp";

	send(socketfd,buf,strlen(buf)+1,0);

	send(socketfd,"haha,world",11,0);
	return 0;


}



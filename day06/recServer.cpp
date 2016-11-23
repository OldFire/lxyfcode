/* ************************************************************************
 *       Filename:  recServer.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/02/2016 09:44:27 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"

int main()
{
	int temp;
	int sockfd=socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(7777);
	addr.sin_addr.s_addr=INADDR_ANY;

	bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
	listen(sockfd,250);

	int fdnew=accept(sockfd,NULL,NULL);
	recv(fdnew,&temp,sizeof(temp),0);
	printf("the process %d\n",temp);
}


/* ************************************************************************
 *       Filename:  sendClient.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/02/2016 10:05:54 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "h.h"
int main(int argc,char*argv[])
{
	char*pro=argv[0];
	int num=atoi(argv[1]);
	int port=atoi(argv[2]);
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)	perror("sockfd error");

	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(port);
	addr.sin_addr.s_addr=inet_addr("127.0.0.1");

	int ret=connect(sockfd,(struct sockaddr*)&addr,sizeof(addr));
	if(ret<0)	perror("connect error");


	for(int i=0;i<num;i++)
	{
		pid_t pid=fork();
		if(pid==0)
		{
			send(sockfd,&i,sizeof(int),0);
			printf("process is %d\n",i);
			getchar();
			return 0;

		}

	}
	for(int i=0;i<num;i++)
	{
		wait(NULL);
	}
	
}



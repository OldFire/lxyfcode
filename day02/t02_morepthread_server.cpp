/* ************************************************************************
 *       Filename:  t02_morepthread_server.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/05/2016 12:34:47 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "../h.h"
void *handle_socket(void*ptr)
{
	int fd=(int)(intptr_t)ptr;
	char buf[1024];
	recv(fd,buf,sizeof(buf),0);
	printf("%s\n",buf);
	close(fd);
}

int main()
{
	int fd=socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(9988);
	addr.sin_addr.s_addr=INADDR_ANY;

	int ret=bind(fd,(struct sockaddr*)&addr,sizeof(addr));
	if(ret<0)
	{
		perror("bind error");
		return 1;
	}

	listen(fd,20);
	while(1)
	{
		int newfd=accept(fd,NULL,NULL);

		pthread_t tid;
		pthread_create(&tid,NULL,handle_socket,(void*)(intptr_t)newfd);

		pthread_detach(tid);
	}
}



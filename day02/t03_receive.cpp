/* ************************************************************************
 *       Filename:  t03_receive.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/31/2016 08:01:18 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include"h.h"

int main()
{
	int fd=socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(6666);
	addr.sin_addr.s_addr=INADDR_ANY;

	bind(fd,(struct sockaddr*)&addr,sizeof(addr));

	listen(fd,10);

	int fdnew=accept(fd,NULL,NULL);

	char buf[1024];
	fd_set set;
	while(1)
	{
		FD_ZERO(&set);
		FD_SET(STDIN_FILENO,&set);
		FD_SET(fdnew,&set);

		select(fdnew+1,&set,NULL,NULL,0);
		if(FD_ISSET(fdnew,&set))
		{
			memset(buf,0,sizeof(buf));
			int ret=recv(fdnew,buf,sizeof(buf),0);
			if(ret<=0) break;
			printf("recv:%s",buf);
		}
		if(FD_ISSET(STDIN_FILENO,&set))
		{
			char tmp[1024];
			fgets(tmp,sizeof(tmp),stdin);
			send(fdnew,tmp,sizeof(tmp),0);
		}
	}
	close(fdnew);
	close(fd);


	return 0;
}





/* ************************************************************************
 *       Filename:  t06_file_receive.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/31/2016 10:16:43 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"

int main()
{
	int fd=socket(AF_INET,SOCK_STREAM,0);
	FILE *fp=fopen("temp","w");

	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(6666);
	addr.sin_addr.s_addr=INADDR_ANY;

	bind(fd,(struct sockaddr*)&addr,sizeof(addr));

	listen(fd,10);

	int fdnew=accept(fd,NULL,NULL);

	char buf[4096];
	while(1)
	{
		int ret=recv(fdnew,buf,sizeof(buf),0);
		if(ret<=0) break;
		fwrite(buf,ret,1,fp);

	}
	fclose(fp);
	close(fd);
}



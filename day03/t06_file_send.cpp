/* ************************************************************************
 *       Filename:  t06_file_send.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/31/2016 09:41:13 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"

void sendall(char*filename,char*ip,uint16_t port)
{
	FILE*fp=fopen(filename,"r");
	char buf[4096];
	int fd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(6666);
	addr.sin_addr.s_addr=inet_addr("127.0.0.1");

	connect(fd,(struct sockaddr*)&addr,sizeof(addr));

	while(1)
	{
		memset(buf,0,sizeof(buf));
		int ret=fread(buf,1,sizeof(buf),fp);
		if(ret<=0) break;
		int alreadsend=0;
		while(alreadsend!=ret)
		{
			int len=send(fd,buf,ret-alreadsend,0);
			alreadsend+=len;
		}
	}

	close(fd);
	fclose(fp);
}

int main(int argc,char*argv[])
{
	if(argc!=4)
	{
		printf("usage:%s [filename] [ip] [port]\n",argv[0]);
		return -1;
	}
	char*filename=argv[1];
	char*ip=argv[2];
	uint16_t port=atoi(argv[3]);

	sendall(filename,ip,port);

	return 0;

}



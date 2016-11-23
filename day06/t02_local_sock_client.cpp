/* ************************************************************************
 *       Filename:  t02_local_sock_client.cpp
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
	int fd=socket(AF_UNIX,SOCK_STREAM,0);

	struct sockaddr_un addr;
	addr.sun_family=AF_UNIX;
	strcpy(addr.sun_path,"socket_file");

	connect(fd,(struct sockaddr*)&addr,sizeof(addr));

	write(fd,"hello",5);
	close(fd);
	return 0;
}



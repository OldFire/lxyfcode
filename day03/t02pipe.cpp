/* ************************************************************************
 *       Filename:  t02pipe.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/27/2016 10:18:56 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "h.h"
int main()
{
	int fd=open("fifo_file",O_RDWR);
	printf("open\n");
	char buf[1024];
	int ret=read(fd,buf,sizeof(buf));

	write(fd,buf,sizeof(buf));
	return 0;
}



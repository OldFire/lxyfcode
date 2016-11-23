/* ************************************************************************
 *       Filename:  t01pipe_read.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/27/2016 10:08:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
int main()
{
	int fd=open("fifo_file",O_RDONLY);
	if(fd<0)
	{
		perror("open");
		return 0;
	}
	printf("open write success\n");
	char buf[1024]="hello";
	int ret=write(fd,buf,strlen(buf)+1);
	printf("write result:%s,ret is %d\n",buf,ret);

	return 0;
}



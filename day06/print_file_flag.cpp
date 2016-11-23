/* ************************************************************************
 *       Filename:  print_file_flag.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/17/2016 08:54:15 AM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "../h.h"
int main(int argc,char*argv[])
{
	int val;
	if(argc!=2)
	{
		printf("usage:a.out descriptor\n");
		return -1;
	}
	
	if((val=fcntl(atoi(argv[1]),F_GETFL,0))<0)
	{
		printf("fcntl error for fd %d",atoi(argv[1]));
	}
	switch(val&O_ACCMODE)
	{
		case O_RDONLY:
			printf("read only\n");
			break;
		case O_WRONLY:
			printf("write only\n");
			break;
		case O_RDWR:
			printf("read write\n");
			break;
		default:
			perror("unknow access mode\n");
	}

	if(val&O_APPEND) printf("append\n");
	if(val&O_NONBLOCK) printf("nonblocking\n");
	if(val&O_SYNC) printf("synchronous writes\n");
	if(val&O_FSYNC) printf("synchronnous writes\n");

	return 0;
}

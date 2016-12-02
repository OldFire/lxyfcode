/* ************************************************************************
 *       Filename:  a.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/27/2016 07:08:37 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
	char buf[]="/tmp/XXXXXX";
	int fd=mkstemp(buf); //返回的文件描述符可读可写
//	int fd=open("a.txt",O_RDWR|O_TRUNC|O_CREAT);
	if(fd<0)
	{
		perror("error\n");
		return -1;
	}
	write(fd,"aaabbb",6);
	//fsync(fd);
	lseek(fd,0,SEEK_SET);
	char temp[512]={0};
	read(fd,temp,6);
	printf("temp is %s\n",temp);

	close(fd);
	printf("%s\n",buf);
}

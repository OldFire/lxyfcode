/* ************************************************************************
 *       Filename:  lseek.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  08/09/2017 09:37:09 AM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "../h.h"
#include <limits.h>
/*
int main()
{
	if(lseek(STDIN_FILENO,0,SEEK_CUR)==-1)
	{
		printf("cannot seek\n");
	}
	else
	{
		printf("seek OK\n");
	}
	exit(0);
}
*/
char buf1[]="abcdefghij";
char buf2[]="ABCDEFGHIJ";

int main()
{
	int fd;
	if((fd=creat("file.hole",0666))<0)
	{
		perror("create error.\n");
	}

	if(write(fd,buf1,10)!=10)
	{
		printf("buf1 write error.");
	}

	if(lseek(fd,16348,SEEK_SET)==-1)
	{
		perror("lseek error\n");
	}

	if(write(fd,buf2,10)!=10)
	{
		perror("buf2 write error");
	}
}

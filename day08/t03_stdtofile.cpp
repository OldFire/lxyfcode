/* ************************************************************************
 *       Filename:  t03_stdtofile.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  02/04/2017 06:30:48 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include"../h.h"

#define PROTECT_PROCESS \
{ \
	if(fork()>0) exit(0); \
	setsid(); \
	if(fork()>0) exit(0); \
}


int main(int argc,char*argv[])
{

	if(argc!=2)
	{
		printf("useage is %s [filename]\n",argv[1]);
		return -1;
	}

	char*filename=argv[1];

	int fd=open(filename,O_WRONLY|O_CREAT|O_APPEND,0666);
	if(fd<0)
	{
		perror("open");
		return -2;
	}
	PROTECT_PROCESS
	dup2(fd,STDOUT_FILENO);
	printf("%d",fd);
}



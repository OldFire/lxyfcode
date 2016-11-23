/* ************************************************************************
 *       Filename:  terminal_nonblock.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/23/2016 04:49:47 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "../h.h"

#define MSG_TRY "try again\n"
#define MSG_TIMEOUT "timeout\n"

int main()
{
	char buf[10];
	int fd,n,i;
	fd=open("/dev/tty",O_RDONLY|O_NONBLOCK);
	if(fd<0)
	{
		perror("open /dev/tty");
		exit(1);
	}

	for(i=0;i<5;i++)
	{
		n=read(fd,buf,sizeof(buf));
		if(n>=0)	break;
		if(errno!=EAGAIN)
		{
			perror("read /dev/tty");
			exit(1);
		}
		sleep(1);
		write(STDOUT_FILENO,MSG_TRY,strlen(MSG_TRY));
	}

	if(i==5)
	{
		write(STDOUT_FILENO,MSG_TIMEOUT,strlen(MSG_TIMEOUT));
	}
	else
	{
		write(STDOUT_FILENO,buf,0);
	}
	close(fd);
	return 0;
}

/* ************************************************************************
 *       Filename:  fcntl_nonblock.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/23/2016 05:25:05 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "../h.h"

#define MSG_TRY "try again\n"

int main()
{
	char buf[10];
	int n;
	int flags;
	flags=fcntl(STDIN_FILENO,F_GETFL);
	flags|=O_NONBLOCK;
	if(fcntl(STDIN_FILENO,F_SETFL,flags)==-1)
	{
		perror("fcntl error\n");
		exit(1);
	}
tryagain:
	n=read(STDIN_FILENO,buf,10);
	if(n<0)
	{
		if(errno==EAGAIN)
		{
			sleep(1);
			write(STDOUT_FILENO,MSG_TRY,strlen(MSG_TRY));
			goto tryagain;
		}
		perror("read stdin\n");
		exit(1);
	}
	write(STDOUT_FILENO,buf,n);
	return 0;
}

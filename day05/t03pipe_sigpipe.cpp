/* ************************************************************************
 *       Filename:  t03pipe_sigpipe.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/27/2016 10:40:42 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "h.h"
int main()
{
	signal(SIGPIPE,SIG_IGN);

	int fd[2];
	pipe(fd);
	
	close(fd[0]);

	char a;

	int ret=write(fd[1],&a,1);
	if(ret<0)
	{
		perror("write");
	}
	while(1)
	{
		sleep(1);
	}
	return 0;
}



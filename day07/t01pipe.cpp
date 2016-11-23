/* ************************************************************************
 *       Filename:  t01pipe.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/27/2016 10:22:01 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "h.h"
int main()
{
	int fd[2];
	pipe(fd);


	pid_t pid=fork();
	if(pid==0)
		{
			close(fd[1]);
			char buf[128];
			read(fd[0],buf,sizeof(buf));
			printf("%s\n",buf);
		}
	else
	{
		close(fd[0]);
		write(fd[1],"hello",6);
		wait(NULL);
	}
	return 0;
}



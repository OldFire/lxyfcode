/* ************************************************************************
 *       Filename:  t04pipe_command.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/28/2016 11:16:08 AM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"

int main()
{
	pid_t fd[2];
	pipe(fd);

	int fread=fd[0];
	int fwrite=fd[1];

	{
		pid_t pid=fork();
		if(pid==0)
		{
			close(fread);
			dup2(fwrite,STDOUT_FILENO);
			execlp("ps","ps","aux",NULL);
			close(fwrite);
			return 0;

		}
	}

	{
		pid_t pid=fork();
		if(pid==0)
		{
			close(fwrite);
			dup2(fread,STDIN_FILENO);
			execlp("grep","grep","a.out",NULL);
			close(fread);
			return 0;
		}
	}

	close(fread);
	close(fwrite);
	wait(NULL);
	wait(NULL);
	return 0;
}



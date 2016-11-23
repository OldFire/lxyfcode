/* ************************************************************************
 *       Filename:  t01socketpair.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/28/2016 11:46:11 AM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
int main()
{
	int fd[2];

	socketpair(AF_UNIX,SOCK_STREAM,0,fd);

	pid_t pid=fork();
	if(pid>0)
	{
		close(fd[1]);
		//father process
		while(1)
		{
			char buf[1024];
			fgets(buf,sizeof(buf),stdin);

			if(strcmp(buf,"exit\n")==0)
				break;
				write(fd[0],buf,strlen(buf)-1);
			
		}
		close(fd[0]);
		wait(NULL);
		return 0;
	}
	else
	{
		close(fd[0]);
		while(1)
		{
			char buf[1024];
			int ret=read(fd[1],buf,sizeof(buf));
			if(ret==0)
			{
				printf("%s",buf);
				break;
			}
			printf("%s",buf);
			return 0;
		}

	}
}



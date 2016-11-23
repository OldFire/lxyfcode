/* ************************************************************************
 *       Filename:  handlecmd.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/28/2016 01:32:21 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "h.h"

void split_cmd(char*simple_cmd,char*args[])
{
	int index=0;
	char*arg=strtok(simple_cmd," \t");
	while(1)
	{
		args[index++]=arg;
		if(arg==NULL)
			break;
		arg=strtok(NULL," \t");
	}
}


void handle_simple_cmd(char*simple_cmd)
{
	char*pos=strstr(simple_cmd,">");
	if(pos==NULL)
	{
		char*args[4096];
		split_cmd(simple_cmd,args);

		pid_t pid=fork();
		if(pid==0)
		{
			execvp(args[0],args);
			printf("can not find command %s\n",args[0]);
			exit(1);
		}
		wait(NULL);
	}
	else
	{
		char test=pos[1];
		char* cmd=strtok(simple_cmd,">");
		char*filename=strtok(NULL,">");

		int fd;
		if(test=='>')
		{	
			fd=open(filename,O_WRONLY|O_APPEND);
			if(fd<0)
			{
				fd=open(filename,O_WRONLY|O_APPEND|O_CREAT,0777);
			}
		}
		else
		{
			fd=open(filename,O_WRONLY|O_CREAT|O_TRUNC,0777);
		}
		dup2(fd,STDOUT_FILENO);
		close(fd);
		handle_simple_cmd(cmd);
	}
}
int main(int argc,char*argv[])
{
	char*cmd=argv[1];
	char*handle_cmd_path=argv[0];

	char*pos=strstr(cmd,"|");
	if(pos==NULL)
	{
		handle_simple_cmd(cmd);
		return 0;
	}
	else
	{
		char*remain=NULL;
		char*first_cmd=strtok_r(cmd,"|",&remain);

		int fd[2];
		pipe(fd);
		int fdread=fd[0];
		int fdwrite=fd[1];

		pid_t pid=fork();
		if(pid==0)
		{
			dup2(fdread,STDIN_FILENO);
			close(fdread);
			close(fdwrite);

			execl(handle_cmd_path,handle_cmd_path,remain,NULL);

			exit(1);
		}

		dup2(fdwrite,STDOUT_FILENO);
		close(fdwrite);
		close(fdread);
		handle_simple_cmd(first_cmd);


		close(STDOUT_FILENO);
		wait(NULL);

	}
	return 0;
}



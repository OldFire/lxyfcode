/* ************************************************************************
 *       Filename:  selfcommand.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/21/2016 12:17:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
#define MAXLINE 1024
int main()
{
	char buf[MAXLINE];
	pid_t pid;
	int status;
	printf("%% ");
	while(fgets(buf,MAXLINE,stdin)!=NULL)
	{
		if(buf[strlen(buf)-1]=='\n')
			buf[strlen(buf)-1]=0;
		if((pid=fork())<0)
		{
			printf("fork error");
		}
		else if(pid==0)
		{
			execlp(buf,buf,(char*)0);
			pirntf("couldn't execute:%s",buf);
			exit(127);
		}
		if((pid=waitpid(pid,&status,0))<0)
			printf("waitpid error");
		printf("%% "); 

	}
	exit(0);
}



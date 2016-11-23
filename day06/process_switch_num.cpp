/* ************************************************************************
 *       Filename:  process_switch_num.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/22/2016 11:28:27 AM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "../h.h"
int main()
{
	int fd[2];
	socketpair(AF_UNIX,SOCK_STREAM,0,fd);
	int fdMain=fd[0];
	int fdProcess=fd[1];

	pid_t pid=fork();
	if(pid==0)
	{
		char tmp;
		for(int i=1;;i+=2)
		{
			sleep(1);
			write(fdProcess,&tmp,sizeof(tmp));
			read(fdProcess,&tmp,sizeof(tmp));
			printf("the proc nubler is:%d\n",i); 
		}
		return 0;
	}

	for(int i=0;;i+=2)
	{
		char tmp;
		read(fdMain,&tmp,sizeof(tmp));
		printf("the main mubler is:%d\n",i);
		write(fdMain,&tmp,sizeof(tmp));

	}

	wait(NULL);
}



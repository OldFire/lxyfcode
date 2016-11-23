/* ************************************************************************
 *       Filename:  sigmask.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/26/2016 12:59:03 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
void sig_handle(int v)
{
	printf("sig_handle %d\n",v);
}

int main()
{
	signal(SIGINT,sig_handle);
	signal(SIGCHLD,sig_handle);
	sigset_t set;//define a signal set

	sigemptyset(&set);//clear the set
	sigaddset(&set,SIGINT);//add the signal
	sigaddset(&set,SIGCHLD);
	sigaddset(&set,SIGUSR1);

	sigset_t oldset;
	sigprocmask(SIG_SETMASK,&set,&oldset);

	pid_t pid=fork();
	if(pid==0)
	{
		kill(getppid(),SIGINT);
		kill(getppid(),SIGINT);
		kill(getppid(),SIGINT);
		return 0;
	}
	while(1)
	{
		sleep(3);
		printf("1\n");
		//sigprocmask(SIG_SETMASK,NULL,&oldset);
		sigprocmask(SIG_SETMASK,&oldset,NULL);
		printf("2\n");
		break;
	}
	wait(NULL);
	return 0;
}


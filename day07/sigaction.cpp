/* ************************************************************************
 *       Filename:  sigaction.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/26/2016 06:29:26 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
/*
static void sig_usr(int signum)
{
	if(signum==SIGUSR1)
	{
		printf("SIGUSR1 received\n");
	}
	else if(signum==SIGUSR2)
	{
		printf("SIGUSR2 received\n");
	}
	else
		printf("signal %d received\n",signum);
}

int main()
{
	char buf[512];
	int n;
	struct sigaction sa_usr;

	sa_usr.sa_flags=0;
	sa_usr.sa_handler=sig_usr;


	sigaction(SIGUSR1,&sa_usr,NULL);
	sigaction(SIGUSR2,&sa_usr,NULL);

	printf("My PID is is %d\n",getpid());

	while(1)
	{
		if((n=read(STDIN_FILENO,buf,511))==-1)
		{
			if(errno==EINTR)
			{
				printf("read is interrupted by signal\n");

			}	
		}
		else
		{
			buf[n]='\0';
			printf("%d bytes read: %s\n",n,buf);
		}
	}
	return 0;
}
*/

void handle(int sig,siginfo_t* info,void*p)
{
	printf("sig=%d,hello %d\n",sig,info->si_int);
	printf("dig=%d,hello %d\n",sig,info->si_value.sival_int);
}

int main()
{
	struct sigaction act;
	act.sa_handler=NULL;
	act.sa_sigaction=handle;
	sigemptyset(&act.sa_mask);
	act.sa_flags=SA_SIGINFO;

	act.sa_restorer=NULL;//not use the posix isn't surpport

	sigaction(SIGINT,&act,NULL);

	pid_t pid=fork();
	if(pid==0)
	{
		union sigval v;
		v.sival_int=102;
		sigqueue(getppid(),SIGINT,v);
		return 0;
	}

	while(1)
	{
		sleep(1);
	}
}

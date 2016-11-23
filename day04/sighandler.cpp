/* ************************************************************************
 *       Filename:  sighandler.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/26/2016 08:38:14 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "h.h"
void signal_handler(int signum,siginfo_t*info,void*ptr)
{
	printf("signum=%d\n",signum);//signal number
	printf("info->si_pid=%d\n",info->si_pid);//the other size pid
	printf("info->si_sigval=%d\n",info->si_value.sival_int);//ther other transport message
}

int main()
{
	struct sigaction act;
	act.sa_sigaction=signal_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags=SA_SIGINFO;

	sigaction(SIGINT,&act,NULL);
	while(1)
	{
		printf("pid is %d\n",getpid());

		pause();
	}
	return 0;
}

/* ************************************************************************
 *       Filename:  sigsend.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/26/2016 08:28:33 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "h.h"
int main(int argc,char*argv[])
{
	pid_t pid,pid_self;
	union sigval tmp;
	pid=atoi(argv[1]);
	if(argc>=3)
		tmp.sival_int=atoi(argv[2]);
	else
		tmp.sival_int=100;

		sigqueue(pid,SIGINT,tmp);

	pid_self=getpid();
	printf("pid=%d,pid_self=%d\n",pid,pid_self);

	return 0;

}



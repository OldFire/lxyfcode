/* ************************************************************************
 *       Filename:  sigrestart.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/26/2016 09:07:05 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "h.h"
void handle(int v ,siginfo_t* v1,void*v2)
{
	printf("sig handle\n");
}

int main()
{
	struct sigaction act;
	act.sa_handler=NULL;
	act.sa_sigaction=handle;
	sigemptyset(&act.sa_mask);

	act.sa_flags=SA_SIGINFO;
	//act.sa_flags=SA_RESTART;

	act.sa_restorer=NULL;

	sigaction(SIGINT,&act,NULL);

	char buf[1024];
	int ret;
READAGAIN:
	ret=read(0,buf,sizeof(buf));
	if(ret<0)
	{
		if(errno==EINTR)
		{
			printf("read is interrupt by signal\n");
			goto READAGAIN;
		}
	}
	buf[ret]=0;
	printf("%s\n",buf);
	return 0;
}


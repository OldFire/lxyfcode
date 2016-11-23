/* ************************************************************************
 *       Filename:  selecttest.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/01/2016 09:44:43 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
int main()
{
	char buf[1024];
	int readlen=0;
	int fd_mice=open("/dev/input/mice",O_RDONLY);
	if(fd_mice<0)
	{
		perror("open mice error");
		return -1;
	}

	int fd_keyb=open("/dev/input/event1",O_RDONLY);
	if(fd_mice<0)
	{
		perror("open keyb error");
		return -1;
	}

	fd_set set;

	while(1)
	{
		FD_ZERO(&set);
		FD_SET(fd_mice,&set);
		FD_SET(fd_keyb,&set);

		struct timeval outTime={2,0};
		int ret=select(fd_keyb+1,&set,NULL,NULL,&outTime);

		if(ret<0)
		{
			perror("select error\n");
			exit(1);
		}
		if(ret==0)
		{
			printf("nothing happened\n");
		}
		else
		{
			if(FD_ISSET(fd_mice,&set))
			{
				readlen=read(fd_mice,buf,sizeof(buf));
				printf("mice event %d\n",readlen);
			}
			if(FD_ISSET(fd_keyb,&set))
			{
				readlen=read(fd_keyb,buf,sizeof(buf));
				printf("keyboard event %d\n",readlen);
			}
		}

	}

}



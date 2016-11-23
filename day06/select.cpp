/* ************************************************************************
 *       Filename:  select.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/27/2016 09:01:26 AM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
int main()
{
	int fd_mice=open("/dev/input/mice",O_RDONLY);
	int fd_keyb=open("/dev/input/event1",O_RDONLY);
	int readlen;
	char buf[1024];

	while(1)
		{
			fd_set set;
			FD_ZERO(&set);
			FD_SET(fd_mice,&set);
			FD_SET(fd_keyb,&set);

			int nfds=fd_keyb+1;

			struct timeval tv;
			tv.tv_sec=2;
			tv.tv_usec=0;

			int ret=select(nfds,&set,NULL,NULL,&tv);

			if(ret==-1)
				{
					if(errno==EINTR)
						continue;
					exit(1);
				}
			if(ret==0)
			{
				printf("the mouse and keyboard is not moving\n");
			}

			if(FD_ISSET(fd_mice,&set))
			{
				readlen=read(fd_mice,buf,sizeof(buf));
				printf("mouse is moving,readlen=%d\n",readlen);
			}

		}
}




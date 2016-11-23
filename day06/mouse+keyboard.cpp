/* ************************************************************************
 *       Filename:  mouse+keyboard.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/23/2016 08:40:16 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
int main()
{
	int fd_mice=open("/dev/input/mice",O_RDONLY|O_NONBLOCK);
	int fd_keyb=open("/dev/input/event1",O_RDONLY|O_NONBLOCK);


	char buf_mice[3];
	char buf_keyb[128];

	while(1)
	{
		int ret=read(fd_mice,buf_mice,sizeof(buf_mice));
		if(ret<0)
		{
			if(errno==EAGAIN)
			{
				printf("can't read mice\n");
						
			}
			else
			{
				printf("file description error\n");
			}
		}

		ret=read(fd_keyb,buf_keyb,sizeof(buf_keyb));
		if(ret<0)
		{
			if(errno==EAGAIN)
				printf("can not read keyboard\n");
			else
			{

			}

		}
	}
			 

}



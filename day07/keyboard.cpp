/* ************************************************************************
 *       Filename:  keyboard.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/23/2016 08:36:10 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
int main()
{
	int fd=open("/dev/input/event1",O_RDONLY);
	if(fd<0)
	{
		perror("open error");
		return 1;
	}
	while(1)
	{
		char buf[256];
		int ret=read(fd,buf,sizeof(buf));
		printf("ret is %d\n",ret);
				
	}
}



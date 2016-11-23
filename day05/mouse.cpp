/* ************************************************************************
 *       Filename:  mouse.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/23/2016 08:27:08 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
int main()
{
	int fd=open("/dev/input/mice",O_RDONLY);
	if(fd<0)
	{
		perror("open error");
		return 1;
	}

	while(1)
	{
		char buf[8];
		int len=read(fd,buf,sizeof(buf));
		printf("read len=%d\n",len);


		char key=buf[0];
		char xoff=buf[1];
		char yoff=buf[2];
		
		char btype=key&0x7;
		if(btype==0x00)
		{
			printf("button up\n");
		}
		else if(btype==0x01)
		{
			printf("left button down\n");
		}
		else if(btype==0x22)
		{
			printf("right button down\n");
		}
	}
	return 0;
}



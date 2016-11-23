/* ************************************************************************
 *       Filename:  lock.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/23/2016 09:13:01 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "h.h"
int main()
{
	int fd=open("a.txt",O_RDWR);

	struct flock l;
	l.l_type=F_WRLCK;
	l.l_whence=SEEK_SET;
	l.l_start=0;
	l.l_len=128;
	
	int ret=fcntl(fd,F_SETLKW,&l);
	write(fd,"123456",7);
	if(ret==0)
	{
		printf("lock success\n");
	}
	else
		printf("lock failure\n");

	getchar();
	l.l_type=F_UNLCK;
	fcntl(fd,F_SETLKW,&l);
	write(fd,"123456",7);


	close(fd);
}




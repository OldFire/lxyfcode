/* ************************************************************************
 *       Filename:  t03shm_open.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/27/2016 09:55:59 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include"h.h"
int main()
{
	int fd=shm_open("/xxxxxx",O_RDWR,0777);
	if(fd<0)
	{
		fd=shm_open("/xxxxxx",O_CREAT|O_RDWR,0777);
		if(fd<0)
		{
			perror("shm_open");
			return 0;
		}
		ftruncate(fd,4096);
	}

	char*ptr=(char*)mmap(NULL,1024,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	getchar();

	printf("ptr=%s\n",ptr);
	munmap(ptr,1024);
}



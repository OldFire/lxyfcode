/* ************************************************************************
 *       Filename:  t02mmap.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/27/2016 09:37:22 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
int main()
{
	int fd=open("/run/shm/a.shm",O_RDWR);
	void *ptr=mmap(NULL,1024,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	close(fd);
	getchar();
	printf("write data in share memory\n");
	//*(int*)ptr=100;
	printf("*ptr=%d\n",*(int*)ptr);
	munmap(ptr,1024);
	return 0;
}



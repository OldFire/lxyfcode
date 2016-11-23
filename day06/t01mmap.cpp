/* ************************************************************************
 *       Filename:  t01mmap.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/27/2016 08:59:34 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
int a=0;
int main()
{
	void *p=mmap(NULL,1024,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
	char*p1=(char*)malloc(100);

	if(p==MAP_FAILED)
	{
		perror("map error");
		return 0;
	}

	pid_t pid=fork();
	if(pid==0)
	{
		a=100;
		*(int*)p=100;
		*p1='a';
	}
	else
	{
		sleep(2);
		printf("%d\n",*(int*)p1);
		
		printf("p1=%d\n",(int)*p1);

		printf("%d\n",*(int*)p);
		printf("a=%d\n",a);
		wait(NULL);

	}
	free(p1);
	munmap(p,1024);
	return 0;
}



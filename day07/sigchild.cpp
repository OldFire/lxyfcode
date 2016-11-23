/* ************************************************************************
 *       Filename:  sigchild.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/23/2016 06:49:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
void handle(int v)
{
	wait(NULL);
	printf("some child something happen\n");
}

int main()
{
	signal(SIGCHLD,handle);

	pid_t pid=fork();
	if(pid==0)
	{
		printf("byebye\n");
		return 0;
	}
	while(1)
	{
		sleep(1);
	}
}



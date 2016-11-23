/* ************************************************************************
 *       Filename:  fork_test.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/27/2016 11:20:36 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "h.h"
int main()
{
	int a=1;
	pid_t pid=fork();
	if(pid==0)
	{
		a++;
		printf("a=%d\n",a);
		pid_t pid1=fork();
		if(pid1==0)
		{
			getchar();
			return 1;
		}
		getchar();
		return 1;
	}

	pid=fork();
	if(pid==0)
	{
		a++;
		printf("a=%d\n",a);
		getchar();
		return 2;
		
	}
	wait(NULL);
	wait(NULL);
	printf("a=%d\n",a);
	
	while(1)
	{
		sleep(1);
	}
	return 0;

}




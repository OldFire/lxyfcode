/* ************************************************************************
 *       Filename:  fork_test1.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/28/2016 09:26:32 AM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
int main()
{
	int i=10;
	pid_t pid=fork();
	pid_t pid1=fork();
	if(pid1==0)
	{
		fork();
	}
	getchar();
	wait(NULL);
	wait(NULL);
	return -1;
	
}



/* ************************************************************************
 *       Filename:  pid.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/20/2016 07:39:37 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include"h.h"
int main()
{
	pid_t pid=getpid();
	printf("%d\n",(int)pid);
	while(1)
	{
		sleep(1);
	}
	return 0;
}


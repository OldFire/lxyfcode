/* ************************************************************************
 *       Filename:  t02pipe_size.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/27/2016 10:34:10 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "h.h"
int main()
{
	int fd[2];
	pipe(fd);

	int sum=0;
	while(1)
	{
		char c;
		int ret=write(fd[1],&c,1);
		sum++;
		printf("sum is %d\n",sum);
	}
	return 0;
}



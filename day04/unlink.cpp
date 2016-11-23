/* ************************************************************************
 *       Filename:  unlink.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/17/2016 10:29:43 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "../h.h"
int main()
{
	if(open("tempfile",O_RDWR)<0)
	{
		perror("open error");
	}
	if(unlink("tempfile")<0)
	{
		perror("unlink error");
	}
	printf("file unlinked\n");
	sleep(15);
	printf("done\n");
	return 0;
}



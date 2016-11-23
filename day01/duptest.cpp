/* ************************************************************************
 *       Filename:  duptest.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/03/2016 10:39:11 AM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"

int main()
{
	int fd=open("test.txt",O_WRONLY|O_CREAT|O_TRUNC);
	char buf[]="关山难越，谁悲失路之人？萍水相逢，尽是它乡之客。";
	dup2(fd,STDOUT_FILENO);
	printf("%s\n",buf);
	close(fd);
	return 0;
}



/* ************************************************************************
 *       Filename:  dup.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/22/2016 08:51:23 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "h.h"
int main()
{
	int sfd=dup(STDOUT_FILENO),testfd;
	printf("sfd=[%d]\n",sfd);

	testfd=open("a.txt",O_CREAT|O_RDWR|O_APPEND);
	if(0>testfd)
	{
		printf("open file error.\n");
		exit(1);
	}

	/*重定向*/
	if(0>dup2(testfd,STDOUT_FILENO))
	{
		printf("can't redirect fd error\n");
		exit(1);
	}

	/*此时stdout写入应该输出到文件*/
	write(STDOUT_FILENO,"file\n",5);

	/*恢复stdout*/
	if(0<=dup2(sfd,STDOUT_FILENO))
	{
		printf("recover fd ok\n");
		
		/*恢复后,写入stdout应该输向屏幕输出*/
		write(STDOUT_FILENO,"stdout\n",7);
	}

	printf("gogogogogogogo!\n");
	close(testfd);

	return 0;
}



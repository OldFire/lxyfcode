/* ************************************************************************
 *       Filename:  access.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/17/2016 07:29:18 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "../h.h"
int main(int argc,char*argv[])
{
	if(argc!=2)
	{
		printf("usage: a.out<pathname>");
		return -1;
	}
	if(access(argv[1],R_OK)<0)
	{
		printf("access error for %s\n",argv[1]);
	}
	else
	{
		printf("read access OK\n");
	}
	if(open(argv[1],O_RDONLY)<0)
	{
		printf("open error for %s\n",argv[1]);
	}
	else
	{
		printf("open for reading ok\n");
	}
	return 0;
}



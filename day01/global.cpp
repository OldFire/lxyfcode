/* ************************************************************************
 *       Filename:  global.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/23/2016 07:39:21 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include"h.h"
#include<list>
using namespace std;
list<int>a;

void handle(int v)
{
	printf("add one\n");
	a.push_back(1);
}

int main()
{
	signal(SIGINT,handle);
	pid_t pid=fork();
	if(pid==0)
	{
		while(1)
		{
			kill(getppid(),SIGINT);
		}
		return 0;
	}
	while(1)
	{
		if(a.size()>0)
			{
				a.push_back(2);
				printf("remove one\n");

			}
	}
}


/* ************************************************************************
 *       Filename:  t04_not_safe.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/28/2016 05:12:32 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "h.h"
int result=0;
void add()
{
	int i=0;
	for(i=0;i<100000;++i)
	{
		result++;
	}
}

void *thread_func(void*arg)
{
	add();
	return NULL;
}

int main()
	{
		pthread_t t1,t2;
		pthread_create(&t1,NULL,thread_func,NULL);
		pthread_create(&t2,NULL,thread_func,NULL);

		pthread_join(t1,NULL);
		pthread_join(t2,NULL);

		printf("result is %d\n",result);
	}


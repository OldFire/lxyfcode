/* ************************************************************************
 *       Filename:  t01thread.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/28/2016 02:57:48 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
void *thread_func(void*arg)
{
	pthread_t tid=pthread_self();
	int a=(int)(intptr_t)arg;
	while(1)
	{
		sleep(1);
		printf("thread runing a=%d,tid=%d\n",a,(int)tid);

		pthread_exit(NULL);
		exit(1);
	}
	return NULL;
}

int main()
{
	pthread_t tid;
	pthread_create(&tid,NULL,thread_func,(void*)(intptr_t)1);

	pthread_t tid2;
	pthread_create(&tid2,NULL,thread_func,(void*)(intptr_t)2);

	if(pthread_equal(tid,tid2))
	{
		printf("equal\n");
	}
	else
	{
		printf("not equal\n");
	}

	pthread_exit(0);

	pause();
	return 0;

}


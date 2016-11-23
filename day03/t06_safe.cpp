/* ************************************************************************
 *       Filename:  t06_safe.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/28/2016 03:57:36 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
int result=0;
int a;
int b;
int c;

pthread_mutex_t mutex;

void add()
{
	int i=0;
	for(i=0;i<100000;++i)
	{
		pthread_mutex_lock(&mutex);
		result++;
		pthread_mutex_unlock(&mutex);
	}
}


void *thread_func(void*arg)
{
	add();
	return NULL;
}

int main()
{
	pthread_mutex_init(&mutex,NULL);

	pthread_t t1,t2;
	pthread_create(&t1,NULL,thread_func,NULL);
	pthread_create(&t2,NULL,thread_func,NULL);


	pthread_join(t1,NULL);
	pthread_join(t2,NULL);

	printf("result is %d\n",result);
	return 0;
}

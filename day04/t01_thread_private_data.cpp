/* ************************************************************************
 *       Filename:  t01_thread_private_data.c
 *    Description:  
 *        Version:  1.0
 *        Created:  10/29/2016 09:23:10 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
int globle_var;
pthread_key_t key;

void foo()
{
	void* self_data=pthread_getspecific(key);
	if(self_data)
	{
		printf("%s\n",(char*)self_data);
	}
	else
	{
		printf("other thread call me\n");
	}
}

void*thread_func(void*ptr)
{
	printf("thread enter\n");
	foo();
	printf("thread end\n");
}

int main()
{
	int var;
	pthread_key_create(&key,free);
	char*p=(char*)malloc(100);
	strcpy(p,"main thread");
	pthread_setspecific(key,p);

	pthread_t tid;
	pthread_create(&tid,NULL,thread_func,NULL);

	sleep(1);

	printf("main enter\n");
	foo();
	printf("main end\n");

	return 0;
}

/* ************************************************************************
 *       Filename:  t03main_thread_exit.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/28/2016 05:08:21 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "h.h"
void *thread_func(void*arg)
{
	while(1)
	{
		printf("hello thread\n");
		sleep(1);
	}
}

int main()
{
	pthread_t tid;
	pthread_create(&tid,NULL,thread_func,NULL);

	printf("main thread exit\n");

	pthread_exit(0);
	return 0;
}



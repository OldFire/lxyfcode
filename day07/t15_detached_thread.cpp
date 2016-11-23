/* ************************************************************************
 *       Filename:  t15_detached_thread.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/28/2016 09:34:29 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "h.h"
void *thread_func(void*arg)
{
	return NULL;
}

int main()
{
	pthread_t tid;
	pthread_attr_t attr;

	pthread_attr_init(&attr);

	int scope;
	pthread_attr_getscope(&attr,&scope);
	if(scope==PTHREAD_SCOPE_SYSTEM)
		{
			printf("scope system\n");
		}
	else if(scope==PTHREAD_SCOPE_PROCESS)
	{
		printf("scope process\n");
	}
	else
	{
		printf("what is this\n");
	}

	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

	pthread_create(&tid,&attr,thread_func,NULL);



	int ret=pthread_join(tid,NULL);
	if(ret==EINVAL)
	{
		printf("not joinable\n");
	}
	return 0;
}



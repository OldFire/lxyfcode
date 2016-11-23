/* ************************************************************************
 *       Filename:  t14_detached_thread.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/28/2016 09:20:25 PM
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
	pthread_create(&tid,NULL,thread_func,NULL);

	pthread_detach(tid);
	int ret=pthread_join(tid,NULL);
	if(ret==EINVAL)
	{
		printf("not joinable\n");
	}
	return 0;
}



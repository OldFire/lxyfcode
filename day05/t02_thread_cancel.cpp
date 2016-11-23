/* ************************************************************************
 *       Filename:  t02_thread_cancel.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/29/2016 10:02:01 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
void* thread_func(void*ptr)
{
	while(1)
	{
		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);
		sleep(1);
		pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
		
		pthread_testcancel();
	}
	return NULL;
}

int main()
{
	pthread_t tid;
	pthread_create(&tid,NULL,thread_func,NULL);

	pthread_cancel(tid);

	pthread_join(tid,NULL);
	printf("thread exit\n");
	return 0;
}

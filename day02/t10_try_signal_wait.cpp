/* ************************************************************************
 *       Filename:  t10_try_signal_wait.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/28/2016 05:22:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
pthread_mutex_t mutex;
pthread_cond_t cond;

void *thread_func(void*arg)
{
	pthread_mutex_lock(&mutex);
	pthread_cond_wait(&cond,&mutex);
	pthread_mutex_unlock(&mutex);

	printf("hello world\n");
	return NULL;
}

int main()
	{
		pthread_mutex_init(&mutex,NULL);
		pthread_cond_init(&cond,NULL);

		pthread_t tid;
		pthread_create(&tid,NULL,thread_func,NULL);

		sleep(1);

		pthread_cond_signal(&cond);

		pthread_join(tid,NULL);
		return 0;
	}



/* ************************************************************************
 *       Filename:  t08_relock.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/28/2016 04:59:21 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include"h.h"
thread_rwlock_t mutex;

void *thread_func(void*arg)
{
	ptrehad_rwlock_rdlock(&mutex);
	pthread_rwlock_unlock(&mutex);
}

void thread_func2(void*arg)
{
	pthread_rwlock_wrlock(&mutex);
	pthread_rwlock_unlock(&mutex);
}

void main()
{
	pthread_rwlock_init(&mutex,NULL);
	pthread_t tid;
	pthread_create(&tid,NULL,thread_func,NULL);

	pthread_join(&tid);
}


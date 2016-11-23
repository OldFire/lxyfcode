/* ************************************************************************
 *       Filename:  t07_recursive_lock.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/28/2016 04:06:58 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include"h.h"
pthread_mutex_t mutex;

int main()
{
	pthread_mutexattr_t attr;

	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE);

	pthread_mutex_init(&mutex,&attr);

	pthread_mutex_lock(&mutex);
	pthread_mutex_lock(&mutex);
	pthread_mutex_lock(&mutex);
	pthread_mutex_lock(&mutex);
	pthread_mutex_lock(&mutex);


	printf("hello world\n");

	pthread_mutex_unlock(&mutex);
	pthread_mutex_unlock(&mutex);
	pthread_mutex_unlock(&mutex);
	pthread_mutex_unlock(&mutex);
	pthread_mutex_unlock(&mutex);

	return 0;
}



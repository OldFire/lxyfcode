/* ************************************************************************
 *       Filename:  t11_semaphone.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/28/2016 06:36:22 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
#include<list>
#include<iostream>
using namespace std;

list<int>tasks;
pthread_mutex_t mutex;

sem_t sem;

void *thread_func(void*ptr)
{
	while(1)
	{
		printf("begin wait\n");
		sem_wait(&sem);
		printf("end wait\n");

		int task;

		pthread_mutex_lock(&mutex);

		task=*tasks.begin();
		tasks.pop_front();
		pthread_mutex_unlock(&mutex);

		printf("task is %d\n",task);
	}
}

int main()
{
	pthread_mutex_init(&mutex,NULL);

	sem_init(&sem,0,0);
	pthread_t tid;
	pthread_create(&tid,NULL,thread_func,NULL);

	while(1)
	{
		char buf[100];
		fgets(buf,sizeof(buf),stdin);
		int a=atoi(buf);

		pthread_mutex_lock(&mutex);
		tasks.push_back(a);
		pthread_mutex_unlock(&mutex);

		printf("send semaphone\n");
		sem_post(&sem);
	}
	return 0;
}

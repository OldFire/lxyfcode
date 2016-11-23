/* ************************************************************************
 *       Filename:  t09_queue.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/28/2016 05:34:04 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
#include<list>
#include<iostream>
using namespace std;

typedef struct task_t
{
	int v;
}task_t;

list<task_t*>g_queue;

pthread_mutex_t g_mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t g_cond;

void *work_thread(void *ptr)
{
	while(1)
	{
		pthread_mutex_lock(&g_mutex);
		
		pthread_cond_wait(&g_cond,&g_mutex);
		pthread_mutex_unlock(&g_mutex);

		while(1)
		{
			pthread_mutex_lock(&g_mutex);
			if(g_queue.size()==0)
			{
				pthread_mutex_unlock(&g_mutex);
				break;
			}
			list<task_t*>::iterator it=g_queue.begin();
			task_t*task=*it;
			g_queue.pop_front();
			pthread_mutex_unlock(&g_mutex);

			printf("handle: %d\n",task->v);
			delete task;
		}

	}
}

int main()
	{
		pthread_cond_init(&g_cond,NULL);
		pthread_t tid;
		pthread_create(&tid,NULL,work_thread,NULL);

		while(1)
		{
			int a;

			char buf[100];
			fgets(buf,sizeof(buf),stdin);
			a=atoi(buf);
			task_t*task=new task_t;
			task->v=a;

			pthread_mutex_lock(&g_mutex);
			g_queue.push_back(task);
			pthread_mutex_unlock(&g_mutex);

			pthread_cond_signal(&g_cond);
		}
	}

/* ************************************************************************
 *       Filename:  t13_thread_poll.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/28/2016 06:53:22 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
#include<list>
using namespace std;

list<int>queue;
pthread_mutex_t mutex;
sem_t sem;

class Lock
{
	private:
		pthread_mutex_t& _m;
		Lock(const Lock&);
		Lock operator=(const Lock&);
	public:
		Lock(pthread_mutex_t& m):_m(m)
	{
		pthread_mutex_lock(&_m);
	}
		~Lock()
		{
			pthread_mutex_unlock(&_m);
		}
};

void*work_thread(void*)
{
	while(1)
		{
			int ret=sem_wait(&sem);
			if(ret<0)
			{
				if(errno==EINTR)
					continue;
				break;
			}
			int task;
			{
				Lock l(mutex);
				task=queue.front();
				queue.pop_front();
			}

			printf("thread id=0x%x,task is %d\n",(int)pthread_self(),task);
		}
}

int main()
{
	pthread_mutex_init(&mutex,NULL);
	sem_init(&sem,0,0);

	pthread_t tid1,tid2,tid3;
	pthread_create(&tid1,NULL,work_thread,NULL);
	pthread_create(&tid2,NULL,work_thread,NULL);
	pthread_create(&tid3,NULL,work_thread,NULL);

	while(1)
	{
		char buf[100];
		fgets(buf,sizeof(buf),stdin);
		int task=atoi(buf);

		{
			Lock l(mutex);
			queue.push_back(task);
		}

		sem_post(&sem);
	}
	return 0;
}

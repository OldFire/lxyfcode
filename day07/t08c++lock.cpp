/* ************************************************************************
 *       Filename:  t08c++lock.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/28/2016 05:17:12 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
pthread_mutex_t mutex;

class Lock
{
	private:
		pthread_mutex_t& _mutex;
	public:
		Lock(pthead_mutex_t& m):_mutex(m)
	{
		pthread_mutex_lock(&_mutex);
	}
		~Lock()
		{
			pthread_mutex_unlock(&_mutex);
		}
};


int a;


void foo()
{
	Lock lock(mutex);
	a++;
}

int main()
{
	pthread_mutex_init(&mutex,NULL);
	return 0;
}


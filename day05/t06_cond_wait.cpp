/* ************************************************************************
 *       Filename:  t06_cond_wait.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/31/2016 12:44:10 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
pthread_cond_t*cond;
pthread_mutex_t*mutex;

char*g_share_mem;

extern char*get_cond_wait(const char*filename,pthread_cond_t**outCond,pthread_mutex_t**outMutex);

int main()
{
	g_share_mem=get_cond_wait("/t06_test",&cond,&mutex);

	while(1)
	{
		pthread_mutex_lock(mutex);
		pthread_cond_wait(cond,mutex);
		pthread_mutex_unlock(mutex);

		printf("wait ok\n");
	}
	return 0;
}



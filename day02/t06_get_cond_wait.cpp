/* ************************************************************************
 *       Filename:  t06_cond_signal.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/31/2016 12:18:09 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "h.h"
char*get_cond_wait(const char*filename,pthread_cond_t**outCond,pthread_mutex_t**outMutex)
{
	pthread_cond_t*cond;
	pthread_mutex_t*mutex;
	char*g_share_mem;

	int fd=shm_open(filename,O_RDWR|O_CREAT|O_EXCL,0777);
	if(fd>0)
	{
		ftruncate(fd,4096);
		g_share_mem=(char*)mmap(NULL,4096,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
		cond=(pthread_cond_t*)g_share_mem;
		mutex=(pthread_mutex_t*)(g_share_mem+sizeof(pthread_cond_t));

		pthread_condattr_t cond_attr;
		pthread_condattr_init(&cond_attr);
		pthread_condattr_setpshared(&cond_attr,PTHREAD_PROCESS_SHARED);
		pthread_cond_init(cond,&cond_attr);


		pthread_mutexattr_t mutex_attr;
		pthread_mutexattr_init(&mutex_attr);
		pthread_mutexattr_setpshared(&mutex_attr,PTHREAD_PROCESS_SHARED);
		pthread_mutex_init(mutex,&mutex_attr);
	}
	else
	{
		fd=shm_open("/t06_test",O_RDWR,0777);

		g_share_mem=(char*)mmap(NULL,4096,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
		cond=(pthread_cond_t*)g_share_mem;
		mutex=(pthread_mutex_t*)(g_share_mem+sizeof(pthread_cond_t));
	}

	close(fd);

	
	*outCond=cond;
	*outMutex=mutex;


	return g_share_mem;
}




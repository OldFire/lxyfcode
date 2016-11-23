/* ************************************************************************
 *       Filename:  t02thread.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/28/2016 03:24:27 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include"h.h"
void *thread_func(void *arg)
{
	pthread_t tid=pthread_self();
	printf("tid1=%d\n",(int)(intptr_t)tid);
	
	return (void*)(intptr_t)"abcd";
}

int main()
{
	pthread_t tid;
	printf("tid0=%d\n",(int)(intptr_t)tid);
	pthread_create(&tid,NULL,thread_func,NULL);

	void*pRet;
	pthread_join(tid,&pRet);
	printf("tid2=%d\n",(int)(intptr_t)tid);
	printf("%s\n",(char*)pRet);
	return 0;
}


/* ************************************************************************
 *       Filename:  t05_not_safe_queue.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/28/2016 03:46:42 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include"h.h"
#include<list>
#include<iostream>
using namespace std;
typedef struct task_t
{
	int v;
}task_t;

list<task_t*>g_queue;
void*work_thread(void*ptr)
{
	while(1)
	{
		if(g_queue.size()==0) continue;

		list<task_t*>::iterator it=g_queue.begin();
		task_t*task=*it;
		g_queue.pop_front();

		printf("hanlde: %d\n",task->v);
		delete task;
	}
}

int main()
{
	pthread_t tid;
	pthread_create(&tid,NULL,work_thread,NULL);

	while(1)
	{
		int a;
		cin>>a;
		task_t*task=new task_t;
		task->v=a;
		g_queue.push_back(task);
	}
}

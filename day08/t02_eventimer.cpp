/* ************************************************************************
 *       Filename:  t02.eventimer.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  01/19/2017 04:12:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include<event.h>
#include<stdio.h>

void OnTimer(int socket,short ev,void*arg)
{
	printf("gave over!\n");
	timeval t;
	t.tv_sec=1;
	t.tv_usec=0;
	event_add((event*)arg,&t);
}
int main()
{
	event_init();
	struct event ev;
	evtimer_set(&ev,OnTimer,&ev);
	timeval t;
	t.tv_sec=1;
	t.tv_usec=0;
	event_add(&ev,&t);
	event_dispatch();

}



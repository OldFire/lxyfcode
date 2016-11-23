/* ************************************************************************
 *       Filename:  child.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/23/2016 08:21:00 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
void child_handle(int v)
{
	pid_t pid=waitpid(-1,NULL,WNOHANG);//等待子进程 退出，-1表示等待任一子进程，
	//NULL表示不保存退出信息，最后一个参数表示即使没有子进程退出也立即返回
	if(pid!=-1)
	{
		printf("one child dead\n");
		return;
	}
}

int main()
{
	signal(SIGCHLD,child_handle);
	pid_t pid=fork();
	if(pid==0)
	{
		return 0;
	}
	while(1)
		pause();
	return 0;
}



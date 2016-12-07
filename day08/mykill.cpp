/* ************************************************************************
 *       Filename:  mykill.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  2016年12月07日 15时40分15秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "../h.h"
int main()
{
	int flag=1;
	const char*command="ps aux|grep 'a.out'|grep -v 'grep'|awk '{print $2}'"; //-v get oppsize
	FILE*fp=popen(command,"r");
	if(fp<0) perror("fp error\n");
	char buf[1024];
	while(fgets(buf,sizeof(buf),fp))
	{
		flag=0;
		kill(atoi(buf),SIGKILL);
		printf("pid:%d a.out is quit.\n",atoi(buf));
		memset(buf,0,sizeof(buf));
	}
	if(flag)
	{
		printf("no a.out is running.\n");
	}
	pclose(fp);
	return 0;
}



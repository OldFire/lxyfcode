/* ************************************************************************
 *       Filename:  cpy_to_master.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/22/2016 07:05:21 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "../h.h"

int main()
{
	char buf[512];
	FILE*fp=popen("find ./ -type f | grep .cpp$","r");
	while(fgets(buf,sizeof(buf),fp))
	{
		buf[strlen(buf)-1]=0;
		pid_t pid=fork();
		if(buf!=NULL&&pid==0)
		{
			execlp("cp","cp",buf,"/home/itcast/Mycode/",NULL);
			memset(buf,0,sizeof(buf));
			return 0;
		}
		wait(NULL);
	}
	return 0;
}



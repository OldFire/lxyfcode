/* ************************************************************************
 *       Filename:  process_count.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/22/2016 12:46:17 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "../h.h"
int main()
{
	FILE *fp=popen("ps aux | awk '{print $2}'","r");
	char buf[100];
	int num=0;
	while(fgets(buf,sizeof(buf),fp))
	{
		//printf("%s\n",buf);
		if(atoi(buf)>=4000 && atoi(buf)<=5000)
		{
			num++;
		}
	}
	printf("the process pid 4000-5000 count is:%d\n",num);
	pclose(fp);
	return 0;
}

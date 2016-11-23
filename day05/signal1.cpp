/* ************************************************************************
 *       Filename:  signal1.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/23/2016 11:18:07 AM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ***********************************************************************/
#include "h.h"
void handle(int v)
{
	printf("signal recv\n");
}

int main()
{
	signal(SIGHUP,handle);
	//int*p=0;
	//*p=0;
	while(1)
	{
		sleep(1);
	}
}


/* ************************************************************************
 *       Filename:  seekdir.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/19/2016 08:50:40 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
int main()
{
	long loc;
	DIR* dir=opendir("testdir");
	struct dirent*entry;
	while(1)
	{
		loc=telldir(dir);
		entry=readdir(dir);
		if(entry==NULL) break;
		if(strcmp(entry->d_name,"a")==0) break;

	}
	seekdir(dir,loc);
	while(1)
	{
		entry=readdir(dir);
		if(entry==NULL) break;
		printf("loc is %d,entry->d_name=%s\n",(int)telldir(dir),entry->d_name);
	}

	return 0;
}



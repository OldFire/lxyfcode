/* ************************************************************************
 *       Filename:  dispalyname.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/20/2016 10:53:56 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "h.h"
int main(int argc,char*argv[])
{
	DIR *dir=opendir(argv[1]);
	struct dirent *enty;
	while((enty=readdir(dir))!=NULL)
	{
		printf("%s\n",enty->d_name);
	}
	closedir(dir);
	return 0;
}



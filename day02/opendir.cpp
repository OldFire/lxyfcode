/* ************************************************************************
 *       Filename:  opendir.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/21/2016 11:03:21 AM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
int main(int argc,char*argv[])
{
	DIR *dir=opendir(argv[1]);
	struct dirent *treny;
	while((treny=readdir(dir))!=NULL)
	{
		printf("%s\n",treny->d_name);
	}
	closedir(dir);
	return 0;
}



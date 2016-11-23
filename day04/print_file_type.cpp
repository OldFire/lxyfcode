/* ************************************************************************
 *       Filename:  print_file_type.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/17/2016 03:15:09 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "../h.h"

int main(int argc,char*argv[])
{
	struct stat buf;
	const char *ptr;
	for(int i=1;i<argc;i++)
	{
		printf("%s:",argv[i]);
		if(lstat(argv[i],&buf)<0)
		{
			perror("lstat error");
			continue;
		}
		if(S_ISREG(buf.st_mode)) ptr="regular\n";
		else if(S_ISDIR(buf.st_mode)) ptr="directory\n";
		else if(S_ISCHR(buf.st_mode)) ptr="character special\n";
		else if(S_ISBLK(buf.st_mode)) ptr="block special\n";
		else if(S_ISFIFO(buf.st_mode)) ptr="fifo\n";
		else if(S_ISLNK(buf.st_mode)) ptr="symbolic link\n";
		else if(S_ISSOCK(buf.st_mode)) ptr="socket\n";
		else
			ptr="** unknow mod **\n";
		printf("%s",ptr);
	}
		return 0;
}



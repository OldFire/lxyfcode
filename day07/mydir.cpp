/* ************************************************************************
 *       Filename:  mydir.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/19/2016 07:33:48 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "h.h"
int rm(const char*path)
{
	struct stat stat_buf;
	int ret=stat(path,&stat_buf);
	if(ret<0)
	{
		perror("stat");
		return -1;
	}
	if(!S_ISDIR(stat_buf.st_mode))
	{
		unlink(path);
		return 0;
	}
	char buf[1024];
	DIR*dir=opendir(path);

	if(dir==NULL)	return -1;

	struct dirent*entry=readdir(dir);
	while(entry)
	{
		sprintf(buf,"%s/%s",path,entry->d_name);//将目录名及文件名组成一个buf字符串
		if(entry->d_type==DT_REG||entry->d_type==DT_LNK)
		{
			unlink(buf);
		}
		if(entry->d_type==DT_DIR)
		{
			if(strcmp(entry->d_name,".")==0
				||strcmp(entry->d_name,"..")==0)
			{
				entry=readdir(dir);
				continue;
			}

			rm(buf);
		}
		entry=readdir(dir);
	}
	closedir(dir);
	rmdir(path);
	return 0;

}

int main(int argc,char*argv[])
{
	if(argc==1)
	{
		printf("usage: %s[pathname]\n",argv[0]);
		return 0;
	}
	rm(argv[1]);
	return 0;

}


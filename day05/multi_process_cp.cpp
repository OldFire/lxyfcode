/* ************************************************************************
 *       Filename:  multi_process_cp.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/22/2016 10:32:11 AM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"

int get_file_lenth(const char*filename)
{
	struct stat stabuf;
	int ret=stat(filename,&stabuf);
	if(ret==-1)
		return -1;
	return stabuf.st_size;

}

void process_copy(const char*src_file,const char*dst_file,int pos,int lenth)
{
	FILE*src=fopen(src_file,"r");
	FILE*dst=fopen(dst_file,"r+");
	char buf[4096];
	fseek(src,pos,SEEK_SET);
	fseek(dst,pos,SEEK_SET);
	while(lenth)
	{
		int copy_len=lenth<4096?lenth:4096;
		int ret=fread(buf,1,copy_len,src);
		fwrite(buf,ret,1,dst);
		lenth-=ret;
	}
	fclose(src);
	fclose(dst);
}

int main(int argc,char*argv[])
{
	if(argc!=5)
	{
		printf("usage :[%s] -job [process_count] [src_file] [dst_file]\n",argv[0]);
		return 1;
	}
	if(strcmp(argv[1],"-job")!=0)
	{
		printf("unknow options:%s\n",argv[1]);
		return 2;
	}
	int process_count=atoi(argv[2]);
	if(process_count<=0)
	{
		printf("process count error\n");
		return 3;
	}
	const char*src_file=argv[3];
	const char*dst_file=argv[4];
	
	int filelen=get_file_lenth(src_file);
	if(filelen==-1)
	{
		printf("file not exits\n");
		return 3;
	}
	int fd=open(dst_file,O_CREAT|O_WRONLY,0777);
	close(fd);
	truncate(dst_file,filelen);//创建指定大小的文件

	int i;
	int average=filelen/process_count;

	for(i=0;i<process_count-1;i++)
	{
		pid_t pid=fork();
		if(pid==0)
		{
			int pos=average*i;
			process_copy(src_file,dst_file,pos,average);
			return 0;
		}
	}
	int pos=average*i;
	process_copy(src_file,dst_file,pos,filelen-pos);

	for(i=0;i<process_count-1;++i)
	{
		wait(NULL);
	}
	return 0;
}


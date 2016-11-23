/* ************************************************************************
 *       Filename:  mycp.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/17/2016 06:49:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include<fcntl.h>
#include<stdio.h>
#include<inttypes.h>
#include<sys/mman.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<utime.h>
#include<stdio.h>
#include<stdlib.h>
//linux下方法(自写)
/*
int main(int argc,char*argv[]) 
{
	
	int fdr=open(argv[1],O_RDONLY);
	int fdw=open(argv[2],O_WRONLY|O_CREAT);

	char buf[1024];
	while(1)
	{
		int n=read(fdr,buf,sizeof(buf));
		if(n!=0)
		{
			write(fdw,buf,n);

		}
		else
			break;
	};

	close(fdr);
	close(fdw);

	struct stat sta1;

	stat(argv[1],&sta1);

	struct utimbuf uti={sta1.st_atime,sta1.st_mtime};

	//修改文件权限
	chmod(argv[2],sta1.st_mode);
	//修改文件属性
	utime(argv[2],&uti);

	//修改所有者
	chown(argv[2],sta1.st_uid,sta1.st_gid); //权限不足可能导致失败
	

	return 0;
}
*/

//c方法(老师方法)
int main(int argc,char*argv[])
{
	if(argc!=3)
	{
		printf("usage:%s[srcfile] [dstfile]\n",argv[0]);
	}
	const char*filesrc=argv[1];
	const char*filedst=argv[2];
	FILE*fp_src=fopen(filesrc,"r");
	FILE*fp_dst=fopen(filedst,"w");

	char buf[4096];
	while(1)
	{
		int ret=fread(buf,1,sizeof(buf),fp_src);
		if(ret<=0)
			break;
		fwrite(buf,ret,1,fp_dst);
	}
	fclose(fp_src);
	fclose(fp_dst);

	struct stat src_stat;
	stat(filesrc,&src_stat);
    
	struct utimbuf timbuf;
	timbuf.actime=src_stat.st_atime;
	timbuf.modtime=src_stat.st_mtime;
	utime(filedst,&timbuf);


	chmod(filedst,src_stat.st_mode);


	int ret=chown(filedst,src_stat.st_uid,src_stat.st_gid);
	if(ret<0)
	{
		perror("chown error");
	}
	return 0;

}



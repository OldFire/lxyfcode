/* ************************************************************************
 *       Filename:  mytar.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/19/2016 09:31:11 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "h.h"
#include<map>
#include<string>
using namespace std;
map<ino_t,string>savedfiles;
void tarfile(const char*filename,FILE*fpOut)
{
	struct stat stat_buf;
	
	stat(filename,&stat_buf);
	//检查这个文件是否已经保存过,是否是其他文件的硬链接
	string filesaved=savedfiles[stat_buf.st_ino];
	if(filesaved.size()!=0)
	{
		fprintf(fpOut,"h\n%s\n%s\n",filename,filesaved.c_str());
		return;
	}
	fprintf(fpOut,"f\n%s\n%lld\n",filename,(long long int)stat_buf.st_size);

	FILE*fpIn=fopen(filename, "r");
	char buf[4096];
	while(1)
	{
		int ret=fread(buf,1,sizeof(buf),fpIn);
		if(ret<=0) break;
		fwrite(buf,ret,1,fpOut);
	}
	fclose(fpIn);

	savedfiles[stat_buf.st_ino]=string(filename);
}

int tardir(const char*dirname,FILE*fpOut)
{
	char filepath[1024];

	//写目录
	fprintf(fpOut,"d\n");
	fprintf(fpOut,"%s\n",dirname);

	DIR*dir=opendir(dirname);
	struct dirent*entry=readdir(dir);
	while(entry)
	{
		sprintf(filepath,"%s/%s",dirname,entry->d_name);
		if(entry->d_type==DT_REG)
		{
			tarfile(filepath,fpOut);
		}
		else if(entry->d_type==DT_DIR)
		{
			if(strcmp(entry->d_name,".")==0||
					strcmp(entry->d_name,"..")==0)
			{
				entry=readdir(dir);
				continue;
			}
			tardir(filepath,fpOut);
		}
		entry=readdir(dir);
	}
	closedir(dir);
}


int tar(const char*dirname,const char* outfile)
{
	FILE*fpOut=fopen(outfile,"w");
	fprintf(fpOut,"xgltar\n");
	fprintf(fpOut,"1.0\n");

	int ret=tardir(dirname,fpOut);
	fclose(fpOut);
	return ret;
}

#define line_buf_size 1024
char line_buf[line_buf_size];
#define get_line() fgets(buf,line_buf_size,fin)

int untar1(FILE*fin)
{
	char*buf=line_buf;
	if(get_line()==NULL) return -1;
	printf("now utar type=%s",buf);

	if(strcmp(buf,"d\n")==0)
	{
		get_line();
		buf[strlen(buf)-1]=0;
		mkdir(buf,0777);
		printf("mkdir %s\n",buf);

	}
	else if(strcmp(buf,"f\n")==0)
	{
		get_line();
		buf[strlen(buf)-1]=0;
		FILE*out=fopen(buf,"w");
		printf("create file %s\n",buf);

		get_line();
		long long int len=atoll(buf);
		printf("filelen %s\n",buf);

		while(len>0)
		{
			int readlen=len<line_buf_size?len:line_buf_size;
			int ret=fread(buf,1,readlen,fin);
			fwrite(buf,1,ret,out);
			len-=ret;
		}
		fclose(out);
	}
	else if(strcmp(buf,"h\n")==0)
	{
		get_line();
		buf[strlen(buf)-1]=0;
		string new_path(buf);
	get_line();
		buf[strlen(buf)-1]=0;

		link(buf,new_path.c_str());


	}
	return 0;

}


int untar(const char*tarfile)
{
	char*buf=line_buf;
	FILE*fin=fopen(tarfile,"r");

	get_line();
	if(strcmp(buf,"xgltar\n")!=0)
	{
		printf("unkown file format\n");
		return -1;
	}




	get_line();
	if(strcmp(buf,"1.0\n")==0)
	{
		while(1)
		{
			int ret=untar1(fin);
			if(ret!=0)
				break;
		}
	}
	else
	{
		printf("unkown version\n");
		return -1;
	}
}


int main(int argc,char*argv[])
{
	 if(argc==1)
	 {
		 printf("usage \n\t%s -c [dir] [tarfile]\n\t%s -u [tarfile]\n",argv[0],argv[0]);
		 return -1;
	 }
	 const char*option=argv[1];
	 if(strcmp(option,"-c")==0)
	 {
		 const char* dirname =argv[2];
		 const char* outfile=argv[3];
		 return tar(dirname,outfile);
	 }
	 else if(strcmp(option,"-u")==0)
	 {
		 const char* tarfile=argv[2];
		 return untar(tarfile);
	 }
	 printf("option error\n");
	 return -1;
}






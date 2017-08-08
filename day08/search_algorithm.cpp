/* ************************************************************************
 *       Filename:  search_algorithm.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  08/07/2017 04:46:15 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "../h.h"
#include <string>
#include <algorithm>
using namespace std;
int main(int argc,char*argv[])
{
	if(argc<=1)
	{
		printf("usage [%s] [keywords]...\n",argv[0]);
		return -1;
	}

	char buf[1024]={0};
	string keyword,keyword2;
	string path="./test.txt";
	int i=0;
	while(--argc)
	{
		keyword+=argv[argc];
		keyword+=".*";

		keyword2+=argv[++i];
		keyword2+=".*";
	}
	int index=keyword.find(".");
	int index2=keyword2.find(".");
	if(index>0)		keyword.insert(index,"\\");
    if(index2>0)    keyword2.insert(index,"\\");
	//printf("index=%d\n",index);
	
	strcpy(buf,(keyword+"|"+keyword2).c_str());
	
	//printf("%s\n%s\n",keyword.c_str(),keyword2.c_str());
	//printf("buf=%s\n",buf);
	
	
	//string command="grep -E \""+string(buf)+"\" "+path+"|awk -F '\\t' '{print $3}'";  //全行匹配
	string command="cat "+ path+"|awk -F '\\t' '{print $3}'"+"|grep -E \""+string(buf)+"\" "; //在指定列匹配
	//printf("command=%s\n",command.c_str());
	
	FILE *fp=popen(command.c_str(),"r");
	if(fp<0)
	{
		perror("popen error\n");
		return -1;
	}
	char tmp[1024];
	while(fgets(tmp,sizeof(tmp),fp))
	{
		printf("tmp=%s",tmp);
		memset(tmp,0,sizeof(tmp));
	}
	fclose(fp);
}





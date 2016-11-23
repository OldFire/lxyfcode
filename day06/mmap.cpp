/* ************************************************************************
 *       Filename:  mmap.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/22/2016 07:31:36 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "h.h"
int main()
	{
		int fd=open("a.txt",O_RDWR);
		char *ptr=(char*)mmap(NULL,4096,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
 	    close(fd);
		//*(char*)ptr='a';//write data to file
		char str[]="曾经沧海难为水,除去巫山不是云.取次花丛懒回顾,半缘修道半缘君.";
		strcpy(ptr,str);
		munmap(ptr,4096);
		//close(fd);
		return 0;

	}



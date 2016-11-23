/* ************************************************************************
 *       Filename:  chmod.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/17/2016 08:18:55 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "../h.h"

int main()
{
	struct stat statbuf;
	if(stat("foo",&statbuf)<0) perror("stat error for foo");
	if(chmod("foo",(statbuf.st_mode&~S_IXGRP)|S_ISGID)<0) perror("chmod error for fool");
	if(chmod("bar",S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)<0) perror("chmod error for bar");
	return 0;
}



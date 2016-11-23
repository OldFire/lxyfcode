/* ************************************************************************
 *       Filename:  umask.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/17/2016 07:55:43 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "../h.h"

#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int main()
{
	umask(0);
	if(creat("foo",RWRWRW)<0) perror("create error for foo\n");
	umask(S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
	if(creat("bar",RWRWRW)<0) perror("create error for bar\n");
	return 0;
}



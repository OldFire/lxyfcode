/* ************************************************************************
 *       Filename:  exec.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/28/2016 12:11:32 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include"h.h"
int main()
{
	char p1[]="ls";
	char p2[]="-hl";
	char*const argv[]={p1,p2,NULL};
	 

	execv("/bin/ls",argv);
	return 0;
}



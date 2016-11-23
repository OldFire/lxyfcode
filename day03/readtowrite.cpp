/* ************************************************************************
 *       Filename:  readtowrite.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/21/2016 11:19:51 AM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
/*
int main()
{
	int n,m;
	char buf[1024];
	while((n=read(STDIN_FILENO,buf,1024))>0)
	{
		m=write(STDOUT_FILENO,buf,n);
		if(m<=1)
		{
			break;
		}
	}
	printf("exit\n");
	return 0;

}
*/

 int main()
 {
	int c;
	while((c=getc(stdin))!=EOF)
	{
		if(putc(c,stdout)==EOF) break;
	}
	exit(0);
 }



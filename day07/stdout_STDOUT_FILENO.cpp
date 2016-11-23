/* ************************************************************************
 *       Filename:  stdout_STDOUT_FILENO.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/28/2016 10:07:26 AM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "h.h"

int main()
{
	fwrite("abcd\n",5,1,stdout);
	
	dup2(STDOUT_FILENO,12);
	write(12,"1234\n",5);
	write(STDOUT_FILENO,"5678\n",5);
	write(1,"9999\n",5);
	close(10);
	return 0;
}

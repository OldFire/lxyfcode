/* ************************************************************************
 *       Filename:  strtok.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/23/2016 07:46:09 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"

int main()
{
	char buf[1024];
	fgets(buf,sizeof(buf),stdin);

	char*saveptr=NULL;
	char*q=strtok_r(buf," ",&saveptr);
	printf("%s\n",q);
	q=strtok_r(NULL," ",&saveptr);
	printf("%s\n",q);
}



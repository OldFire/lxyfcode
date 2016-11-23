/* ************************************************************************
 *       Filename:  arguements.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/26/2016 09:02:11 AM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "h.h"
int sum(int count,...)
{
	int i,sum=0;
	va_list vars;
	va_start(vars,count);
	while(count>0)
	{
		i=va_arg(vars,int);
		sum+=i;
		count--;
	}
	va_end(vars);
	return sum;
}

void myprint(const char*a,...)
{
	const char*tmp=a;
	va_list vars;
	va_start(vars,a);
	while(tmp)
	{
		printf("%s\n",tmp);
		tmp=va_arg(vars,const char*);
	}
}

int main()
{
	printf("the value is %d\n",sum(3,1,2,4));
	myprint("haha","hello","youyou",NULL);
	return 0;
}

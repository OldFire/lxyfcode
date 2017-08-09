/* ************************************************************************
 *       Filename:  mult_pricision.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  08/09/2017 10:09:07 AM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <cmath>
#include <string.h>
#include <iostream>
using namespace std;
char num1[501],num2[501];
int len1,len2,m=0,tmp[600]={0};
int main()
{
	cin>>num1>>num2;
	len1=strlen(num1); len2=strlen(num2);
	for(int i=0;i<len1;i++)
	{
		for(int j=0;j<len2;j++)
		{
			tmp[i+j]+=(num1[i]-'0')*(num2[j]-'0');
		}
	}

	int len=len1+len2-2;

	for(int i=len;i>0;i--)
	{ 		  
		if(tmp[i]>=10)
		{
			tmp[i-1]+=tmp[i]/10;
			tmp[i]%=10;
		}
	}
	while(len--) cout<<tmp[m++]; cout<<tmp[m];

	return 0;
}



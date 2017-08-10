/* ************************************************************************
 *       Filename:  01backpack_problem.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  08/09/2017 06:16:34 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <iostream>
#include <algorithm>
using namespace std;
int v,n,a,f[1000];
int main()
{
	cin>>v>>n;
	for(int i=0;i<n;i++)
	{
		cin>>a;
		for(int j=v;j>=a;j--)
		{
			f[j]=max(f[j],f[j-a]+a);
		}
	}
	cout<<v-f[v]<<endl;
	return 0;
}



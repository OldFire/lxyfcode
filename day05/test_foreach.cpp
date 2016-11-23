/* ************************************************************************
 *       Filename:  test_foreach.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/31/2016 10:03:12 AM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "h.h"
#include<algorithm>
#include<list>
using namespace std;

list<int>ls(5,9);

int main()
{
	ls.insert(++++++ls.begin(),2,2);
	for_each(ls.begin(),ls.end(),[](int& v){
			if(v<4)
			{
				v=8;
			};
			});

	for_each(ls.begin(),ls.end(),[](int v){
			printf("v=%d\n",v);
			});
	return 0;
}




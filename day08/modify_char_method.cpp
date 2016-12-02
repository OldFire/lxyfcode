#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
struct Person {
	char firstName[20];
	//string firstName;
	char lastNane[20];
	//string lastNane;
	int age;
};
//void peopleSwap(string& str1, string&str2)
//{
//	string temp;
//	temp=str1;
//	str1 = str2;
//	str2 = temp;
//}
void peopleSwap(char* str1, char*str2)
{
	char temp[20] = {0};
	strcpy(temp,str1);
	strcpy(str1, str2);
	strcpy(str2, temp);
}

int main()
{
	Person people[2]{ "aaa","111",18,
					  "bbb","222",19};

	printf("修改前:%s，%s,%d\n", people[0].firstName, people[0].lastNane, people[0].age);
	printf("修改前:%s，%s,%d\n", people[1].firstName, people[1].lastNane, people[1].age);
	//cout<<"修改前:"<<people[0].firstName<<" "<<people[0].lastNane<<" "<<people[0].age<<endl;
	//cout << "修改前:" << people[1].firstName << " " << people[1].lastNane << " " << people[1].age<<endl;
	peopleSwap(people[0].lastNane, people[1].lastNane);
	cout << "-------------------------" << endl;
	printf("修改后:%s，%s,%d\n", people[0].firstName, people[0].lastNane, people[0].age);
	printf("修改后:%s，%s,%d\n", people[1].firstName, people[1].lastNane, people[1].age);
	//cout << "修改后:" << people[0].firstName << " " << people[0].lastNane << " " << people[0].age << endl;
	//cout << "修改后:" << people[1].firstName << " " << people[1].lastNane << " " << people[1].age << endl;
	return 0;
}


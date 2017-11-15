#include</usr/include/mysql/mysql.h>
#include<stdlib.h>
#include<stdio.h>
#include<string>
#include<iostream>
using namespace std;
int main()
{
	MYSQL*mysql = NULL;
	int ret, i;

	mysql = mysql_init(NULL);
	if (mysql == NULL)
	{
		printf("mysql_init error:%d\n", mysql_errno(mysql));
		exit(1);
	}

	printf("init ok......\n");

	mysql = mysql_real_connect(mysql, "127.0.0.1", "root", "123456", "answer", 0, NULL, 0);
	if (mysql == NULL)
	{
		printf("mysql_real_connect error %d\n", mysql_errno(mysql));
		exit(1);
	}

	if(mysql_set_character_set(mysql,"utf8"))
	{
		printf("错误，%s\n",mysql_error(mysql));
		exit(1);
	}

	printf("mysql_real_connect ok......\n");

	string query="call getsingleSubject('历史');";

	ret = mysql_query(mysql, query.c_str());
	if (ret != 0)
	{
		printf("mysql_query error:%d\n", mysql_errno(mysql));
		exit(1);
	}

	//获取列
	int count = mysql_field_count(mysql);

	//获致结果集
	MYSQL_RES *result = mysql_store_result(mysql);
	if (result == NULL)
	{
		printf("mysql_store_result error:%d\n", mysql_errno(mysql));
		exit(1);
	}

	//打印表头
	MYSQL_FIELD *fields;
	fields = mysql_fetch_fields(result);
	for (i = 0; i < count; i++)
	{
		printf("%s\t", fields[i].name);
	}
	printf("\n");


	//解析结果集
	MYSQL_ROW row;
	while (row = mysql_fetch_row(result))
	{
		for (i = 0; i < count; i++)
		{
			printf("%s\t", row[i]);
		}
		printf("\n");
	}

	//释放结果集
	mysql_free_result(result);
	
	//关闭
	mysql_close(mysql);

	return 0;
}

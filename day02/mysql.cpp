/* ************************************************************************
 *       Filename:  sql.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/17/2016 04:49:10 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include<mysql.h>
#include<stdlib.h>
#include<stdio.h>

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

	mysql = mysql_real_connect(mysql, "127.0.0.1", "root", "123456", "mydb61", 0, NULL, 0);
	if (mysql == NULL)
	{
		printf("mysql_real_connect error %d\n", mysql_errno(mysql));
		exit(1);
	}

	printf("mysql_real_connect ok......\n");

	const char*query = "select * from emp";
	ret = mysql_query(mysql, query);
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


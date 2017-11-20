#include</usr/include/mysql/mysql.h>
#include<stdlib.h>
#include<stdio.h>
#include"cJSON.h"

void *connectTomysqldb()
{
	MYSQL*mysql = NULL;

	mysql = mysql_init(NULL);
	if (mysql == NULL)
	{
		printf("mysql_init error:%d\n", mysql_errno(mysql));
		return NULL;
	}

	printf("init ok......\n");

	mysql = mysql_real_connect(mysql, "112.74.205.53", "root", "zl123456", "answer", 0, NULL, 0);
	if (mysql == NULL)
	{
		printf("mysql_real_connect error %d\n", mysql_errno(mysql));
		return NULL;
	}

	if(mysql_set_character_set(mysql,"utf8"))
	{
		printf("错误，%s\n",mysql_error(mysql));
		return NULL;
	}

	printf("mysql_real_connect ok......\n");

	return mysql;

}

void disConnectmysqldb(void *mysql)
{
	//关闭
	mysql_close((MYSQL*)mysql);

	printf("mysqldb disconnect successful...\n");

}

void* getsingleSubject(void *sql,const char*str)
{
	MYSQL*mysql=(MYSQL*)sql;
	char query[100]={0};

	sprintf(query,"call getsingleSubject('%s');",(char*)str);
	int ret = mysql_query(mysql, query);
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

	//解析结果集
	MYSQL_ROW row;

	//cJSON相关声明

	char *out;
	cJSON*root=cJSON_CreateObject();
	if(!root)
	{
		printf("cJSON create error!\n");
		return NULL;
	}
	cJSON *subjectlist=cJSON_CreateArray();


	while (row = mysql_fetch_row(result))
	{

		//cJSON格式组包

		cJSON *question=cJSON_CreateObject();
		cJSON_AddItemToObject(question,"siId",cJSON_CreateString(row[2]));
		cJSON_AddItemToObject(question,"deTail",cJSON_CreateString(row[3]));

		cJSON *answer=cJSON_CreateArray();
		cJSON_AddItemToArray(answer,cJSON_CreateString(row[4]));
		cJSON_AddItemToArray(answer,cJSON_CreateString(row[5]));
		cJSON_AddItemToArray(answer,cJSON_CreateString(row[6]));
		cJSON_AddItemToObject(question,"ansWer",answer);
		cJSON_AddItemToObject(question,"reSult",cJSON_CreateString(row[8]));

		cJSON_AddItemToArray(subjectlist,question);

	}
	//释放结果集
	mysql_free_result(result);


	cJSON_AddItemToObject(root,"subjectList",subjectlist);

	out=cJSON_Print(root);

	cJSON_Delete(root);

	if(out)
	{
	//	printf("%s\n",out);  //打印结果
		return out;
	}

	return NULL;
}


void* getdoubleSubject(void *sql,const char*str)
{
	MYSQL*mysql=(MYSQL*)sql;

	char query[100]={0};

	sprintf(query,"call getdoubleSubject('%s');",(char*)str);
	int ret = mysql_query(mysql, query);
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

	//解析结果集
	MYSQL_ROW row;

	//cJSON相关声明

	char *out;
	cJSON*root=cJSON_CreateObject();
	if(!root)
	{
		printf("cJSON create error!\n");
		return NULL;
	}
	cJSON *subjectlist=cJSON_CreateArray();


	while (row = mysql_fetch_row(result))
	{

		//cJSON格式组包

		cJSON *question=cJSON_CreateObject();
		cJSON_AddItemToObject(question,"siId",cJSON_CreateString(row[2]));
		cJSON_AddItemToObject(question,"deTail",cJSON_CreateString(row[3]));

		cJSON *answer=cJSON_CreateArray();
		cJSON_AddItemToArray(answer,cJSON_CreateString(row[4]));
		cJSON_AddItemToArray(answer,cJSON_CreateString(row[5]));
		cJSON_AddItemToArray(answer,cJSON_CreateString(row[6]));
		cJSON_AddItemToObject(question,"ansWer",answer);
		cJSON_AddItemToObject(question,"reSult",cJSON_CreateString(row[8]));

		cJSON_AddItemToArray(subjectlist,question);

	}
	//释放结果集
	mysql_free_result(result);


	cJSON_AddItemToObject(root,"subjectList",subjectlist);

	out=cJSON_Print(root);

	cJSON_Delete(root);

	if(out)
	{
	//	printf("%s\n",out);  //打印结果
		return out;
	}

	return NULL;
}

#if 0

int main()
{
	void*mysql=connectTomysqldb();

	// getsingleSubject(mysql,"历史");
	getdoubleSubject(mysql,"文学");

	disConnectmysqldb(mysql);


	return 0;
}
#endif

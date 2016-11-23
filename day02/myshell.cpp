/* ************************************************************************
 *       Filename:  myshell.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/22/2016 03:30:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"

char g_cmd[1024];
char*g_cmdargs[10];
int g_args_count=0;
#define PATH_TYPE_A 0
#define PATH_TYPE_R 1
#define PATH_TYPE_C 2
int path_type(char*cmd)
{
	char *slas_pos=strstr(cmd,"/");
	if(slas_pos==cmd)
		return PATH_TYPE_A;
	else if(slas_pos!=NULL)
		return PATH_TYPE_R;
	return PATH_TYPE_C;
}

void get_cmd()
{
	char cur_path[1024];
	printf("%s$ ",getcwd(cur_path,sizeof(cur_path)));
	fgets(g_cmd,sizeof(g_cmd),stdin);
	g_cmd[strlen(g_cmd)-1]=0;

}

void split_cmd()
{
	g_args_count=0;
	char *arg=strtok(g_cmd," ");
	while(1)
	{
		g_cmdargs[g_args_count++]=arg;
		if(arg==NULL)
			return;
		arg=strtok(NULL," ");
	}
}

void handle_cmd()
{
	split_cmd();

	if(strcmp(g_cmdargs[0],"cd")==0)
	{
		if(g_cmdargs[1]!=NULL)
			chdir(g_cmdargs[1]);
		else
			chdir(getenv("HOME"));
		return;
	}

	pid_t pid=fork();
	if(pid==0)
	{
		setpgid(0,0);
		int pt=path_type(g_cmdargs[0]);
		if(pt==PATH_TYPE_C)
			execvp(g_cmdargs[0],g_cmdargs);
		else
			execv(g_cmdargs[0],g_cmdargs);
		return;
	}
	wait(NULL);
}

int main()
{
	while(1)
	{
		get_cmd();
		if(g_cmd==NULL)
			continue;
		handle_cmd();

	}
}



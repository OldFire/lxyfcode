/* ************************************************************************
 *       Filename:  getcmd.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/28/2016 01:08:51 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
char g_handlecmd_path[256];
char g_cmd[4096];

void getcmd()
{
	getcwd(g_cmd,sizeof(g_cmd));
	printf("%s$ ",g_cmd);
	fgets(g_cmd,sizeof(g_cmd),stdin);
	g_cmd[strlen(g_cmd)-1]=0;
}

void handlecmd()
{
	char*pcmd=strdup(g_cmd);
	char*firstcmd=strtok(pcmd," \t");
	if(strcmp(firstcmd,"cd")==0)
	{
		char*dir=strtok(NULL," \t");
		if(dir)
			chdir(dir);
		else
			chdir(getenv("HOME"));

		free(pcmd);
		return;
	}
	free(pcmd);

	pid_t pid=fork();
	if(pid==0)
	{
		execl(g_handlecmd_path,g_handlecmd_path,g_cmd,NULL);
		exit(1);
	}
	wait(NULL);

}



int main()
{
	getcwd(g_handlecmd_path,sizeof(g_handlecmd_path));
	strcat(g_handlecmd_path,"/handlecmd");

	while(1)
	{
		getcmd();
		if(strlen(g_cmd)==0)
		{
			continue;
		}
		handlecmd();
	}
}



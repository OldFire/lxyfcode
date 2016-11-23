/* ************************************************************************
 *       Filename:  sheel.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/22/2016 04:08:43 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
char cmd_line[1024];
char*cmd_line_pice[20];

void get_cmd()
	{
		char getpath[1024];
		printf("%s$ ",getcwd(getpath,1024));
		fgets(cmd_line,1024,stdin);
		cmd_line[strlen(cmd_line)-1]=0;

	}

void split_cmd()
{
	int	pice_count=0;
	char*pice=strtok(cmd_line," \t");
	while(1)
	{
		cmd_line_pice[pice_count++]=pice;
		if(pice==NULL)
			break;
		pice=strtok(NULL," \t");
	}

}

void handle_cmd()
{
	split_cmd();
	pid_t pid=fork();
	if(pid==0)
	{
	  int ret=execvp(cmd_line_pice[0],cmd_line_pice);
	  if(ret<0)
		  exit(0);
		return;
	}
	wait(NULL);
}


int main()
	{
		while(1)
		{
			get_cmd();
			if(cmd_line==NULL)
				break;
			handle_cmd();
		}
	}



/* ************************************************************************
 *       Filename:  t06_epoll.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/05/2016 07:06:58 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"
#include "mysql.hpp"
#include <map>
#include <set>
#include <string>
using namespace std;

static map<int,int>matchMap;
static int matchResult=0;
sem_t sem;

int senderfd,matcherfd;
static char*resBuf=NULL;

struct msg_fd{    //用于给线程函数传参
	char msg[8];
	int fd;
}; 

#define PROCESS_COUNT 0 //所要创建的进程数

#define create_daemon(){ \
	if(fork()==0) setsid(); \
	else exit(0); \
	if(fork()!=0) exit(0); \
}

int mySend(int fd,const char*src,int len)
{
	char msgBuf[8192]={0};
	sprintf(msgBuf,"%04d",len);
	strncat(msgBuf,src,len);
	int sendlen=send(fd,msgBuf,len+4,0);
	printf("sendlen=%d\n%s\n",sendlen,msgBuf);
	return sendlen;
}


void set_non_block(int fd)
{
	uint32_t flags;
	flags=fcntl(fd,F_GETFL);
	flags|=O_NONBLOCK;
	fcntl(fd,F_SETFL,flags);
}

void *senderThread(void*ptr)
{
	int timeout=20;
	int num;
	while(timeout--)
	{
		num=matchMap.size();
		if(num%2==0) 
		{
			senderfd=matchMap[num-1];
			matcherfd=matchMap[num];
			mySend(senderfd,"match sucess...\n",strlen("match sucess...\n"));
			mySend(senderfd,resBuf,strlen(resBuf));
			matchResult=0;
			return NULL;
		}
		sleep(1);
	}

	mySend(matchMap[num],"match failed...\n",strlen("match failed...\n"));
	map<int,int>::iterator iter;
	iter=matchMap.find(num);
	matchMap.erase(iter);
}

void waitMatch()
{
	pthread_t tid;
	if(matchMap.size()%2==1)
	{
		pthread_create(&tid,NULL,senderThread,NULL);
		pthread_detach(tid);
	}
}


void startdoubleMatch(int fd,int*sender,int*matcher,char*resBuf)
{
	mySend(fd,"is matching 15s...\n",strlen("is matching 15s...\n"));

	int num=matchMap.size();
	
	int isExist=0;

	//通过循环判断匹配池中是否存在此fd
	for(map<int,int>::iterator iter=matchMap.begin();iter!=matchMap.end();iter++)
	{
		if(iter->second==fd) isExist=1;
		break;
	}
                       	
	if(isExist==0)	matchMap[num+1]=fd;

	printf("num=%d\n",num);
	if(num>0&&(num%2==1))
	{
		*sender=matchMap[num];
		*matcher=matchMap[num+1];
		mySend(fd,"match sucess...\n",strlen("match sucess...\n"));
		mySend(fd,resBuf,strlen(resBuf));
		matchResult=0;
	}
	else
	{
		waitMatch();//匹配的回调函数
	}
}

void delMessage(void*ptr)
{
	msg_fd *tmp=(msg_fd*)ptr;
	char*msg=tmp->msg;
	int fd=tmp->fd;

	void *mysql=connectTomysqldb();//连接到数据库
	char *myReq=NULL;

	if(strncmp(msg,"0101",4)==0)//单人文学
	{
		myReq=(char*)getsingleSubject(mysql,"文学");
	}
	else if(strncmp(msg,"0102",4)==0)//单人历史
	{
		myReq=(char*)getsingleSubject(mysql,"历史");
	}
	else if(strncmp(msg,"0201",4)==0)//双人文学
	{

		if(matchResult==0)
		{
			printf(" i is called,matchResult=%d\n",matchResult);
			resBuf=(char*)getdoubleSubject(mysql,"文学");
			matchResult=1;
		}
		myReq=resBuf;
		startdoubleMatch(fd,&senderfd,&matcherfd,resBuf);
	}
	else if(strncmp(msg,"0202",4)==0)//双人历史
	{
		if(matchResult==0)
		{
			printf(" i is called,matchResult=%d\n",matchResult);
			resBuf=(char*)getdoubleSubject(mysql,"历史");
			matchResult=1;
		}
		myReq=resBuf;
		startdoubleMatch(fd,&senderfd,&matcherfd,resBuf);
	}
	else
	{	
		printf("未找到此类别，请重新选择!\n");
		myReq=(char*)"未找到此类别，请重新选择!";
	}

	disConnectmysqldb(mysql);
	if(strncmp(msg,"01",2)==0)	
	{
		mySend(fd,myReq,strlen(myReq));
	}
}



void* workThread(void *ptr)
{
	while(1)
	{
		int ret=sem_wait(&sem);
		if(ret<0)
		{
			if(errno==EINTR)
				continue;
		}

		msg_fd *tmp=(msg_fd*)ptr;
		printf("tmp->msg=%s,tmp->fd=%d\n",tmp->msg,tmp->fd);

		delMessage(ptr);
	}
}


int main()
{
	create_daemon();

	signal(SIGCHLD,SIG_IGN);
	signal(SIGINT,SIG_IGN);
	signal(SIGHUP,SIG_IGN);
	signal(SIGPIPE,SIG_IGN);
	signal(SIGTTOU,SIG_IGN);
	signal(SIGQUIT,SIG_IGN);
	signal(SIGTSTP,SIG_IGN);  //ctrl + Z退出

	sem_init(&sem,0,0);

	int fd=socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(9988);
	addr.sin_addr.s_addr=INADDR_ANY;

	int ret=bind(fd,(struct sockaddr*)&addr,sizeof(addr));
	if(ret<0)
	{
		perror("bind error");
		return 1;
	}
	listen(fd,20);

	set_non_block(fd);


	int epollfd=epoll_create(512);

	struct epoll_event ev;
	ev.data.fd=fd;
	ev.events=EPOLLIN;

	msg_fd *p1=new msg_fd;
	pthread_t tid;
	pthread_create(&tid,NULL,workThread,p1);	 //创建新线程处理收到的消息
	pthread_detach(tid);


	epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&ev);

	while(1)
	{
		struct epoll_event out_ev[8];
		int ret=epoll_wait(epollfd,out_ev,8,2000);
		if(ret>0)
		{
			for(int i=0;i<ret;i++)
			{
				struct epoll_event*p=&out_ev[i];
				if(p->data.fd==fd)
				{
					while(1)
					{
						int newfd=accept(fd,NULL,NULL);
						if(newfd<0)
						{
							if(errno==EAGAIN||errno==EINTR)
								break;
							else
								exit(1);
						}
						printf("has new client...\n");
						mySend(newfd,"hello...\n",strlen("hello...\n"));
						ev.data.fd=newfd;
						set_non_block(newfd);
						ev.events=EPOLLIN|EPOLLET|EPOLLOUT;
						epoll_ctl(epollfd,EPOLL_CTL_ADD,newfd,&ev);
					}
				}
				else
				{
					char buf[1024];
					while(1)
					{
						int ret=read(p->data.fd,buf,sizeof(buf));
						if(ret>0)
						{
							printf("Servrecv:%s\n",buf);
							bzero(p1,sizeof(msg_fd));		
							strncpy(p1->msg,buf,4);
							p1->fd=p->data.fd;
							sem_post(&sem);
							bzero(buf,sizeof(buf));
						}
						else if(ret<=0)
						{
							if(errno==EAGAIN||EINTR) break;
							epoll_ctl(epollfd,EPOLL_CTL_DEL,p->data.fd,&ev);
							close(p->data.fd);
							break;
						}
					}
				}
			}
		}
	}

	close(epollfd);
}




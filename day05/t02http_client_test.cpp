/* ************************************************************************
 *       Filename:  t02http_client_test.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/08/2016 08:39:56 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "../h.h"
#if 0
char a[]="abc"
"bcd";
char a[]="abcdcd"
#endif

char buf[]=
"GET /xxx.html HTTP/1.1\r\n"
"Host: 192.168.16.130:80\r\n"
"User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:28.0) Gecko/20100101 Firefox/28.0\r\n"
"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
"Accept-Language: en-US,en;q=0.5\r\n"
"Accept-Encoding: gzip, deflate\r\n"
"Connection: keep-alive\r\n\r\n";



int main()
{
	int fd=socket(AF_INET,SOCK_STREAM,0);
	
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(80);
	addr.sin_addr.s_addr=inet_addr("192.168.16.130");

	connect(fd,(struct sockaddr*)&addr,sizeof(addr));

	send(fd,buf,sizeof(buf)-1,0);

	char resp[4096];
	recv(fd,resp,sizeof(resp),0);

	printf("%s\n",resp);
}

#include "../h.h"
int main()
{
	int sock=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(9988);
	addr.sin_addr.s_addr=inet_addr("255,255,255,255");
	int opt=1;
	setsockopt(sock,SOL_SOCKET,SO_BROADCAST,&opt,
			sizeof(opt));

	char buf[]="hello all";
	sendto(sock,buf,sizeof(buf),0,
			(struct sockaddr*)&addr,sizeof(addr));

	return 0;

}

/* ************************************************************************
 *       Filename:  t01_multiprocess_server.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  11/05/2016 09:28:59 AM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include "../h.h"

// 子进程处理：通信
void handle_socket(int fd)
{
    char buf[1024];
    recv(fd, buf, sizeof(buf), 0);
    printf("%s\n", buf);
}

void signal_handle(int v)
{
    while(1)
    {
        pid_t pid = waitpid(-1, NULL, WNOHANG);
        if(pid <= 0) // ==0 表示没有进程有状态变化，<0表示出错
            break;
    }
}

int main()
{
    signal(SIGCHLD, signal_handle);
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9988);
    addr.sin_addr.s_addr = INADDR_ANY;

    int ret = bind(fd, (struct sockaddr*)&addr, sizeof(addr));
    if(ret < 0)
    {
        perror("bind");
        return 1;
    }

    listen(fd, 20);

    while(1)
    {
        int newfd = accept(fd, NULL, NULL);

        pid_t pid = fork();
        if(pid == 0)
        {
            handle_socket(newfd);
            return 0;
        }
        close(newfd);
    }
}




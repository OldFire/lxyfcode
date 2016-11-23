/* ************************************************************************
 *       Filename:  chat.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  10/27/2016 07:47:04 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "h.h"

char g_cmd[4096];
int g_fd; // user lock

typedef struct user
{
    pid_t pid; // 如果pid==-1表示该结构体是空闲的
    char username[100];
} user;

user* g_users;
user* g_me = NULL;
int total_user_count;

char* g_content;

void sig_handler(int v)
{
    flock(g_fd, LOCK_SH);
    printf("%s\n$ ", g_content);
    flock(g_fd, LOCK_UN);

    fflush(stdin);
}

void init_share_memory()
{
    int need_init_user = 0;
    int fd = shm_open("/mychat", O_RDWR|O_CREAT|O_EXCL, 0777);
    g_fd = fd;
    if(fd < 0)
    {
        fd = shm_open("/mychat", O_RDWR, 0777);
    }
    else
    {
        // 4K userinfo, 4K chat info
        ftruncate(fd, 8192);
        need_init_user = 1;
    }

    void* ptr = mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    g_content = ((char*)ptr) + 4096;
    g_users = (user*)ptr;
    total_user_count = 4096 / sizeof(user);

    // 创建该文件的进程需要初始化所有的结构体
    if(need_init_user)
    {
        int i;
        for(i=0; i<total_user_count; ++i)
        {
            user* pUser = g_users + i;
            pUser->pid = -1; 
        }
    }

}

void get_cmd()
{
    printf("$ ");
    fgets(g_cmd, sizeof(g_cmd), stdin);
    g_cmd[strlen(g_cmd)-1] = 0; // remove \n
}

void setname(const char* name)
{
    if(strlen(name) > 99)
        return;

    user* pUser;
    // 检查重名
    for(int i=0; i<total_user_count; ++i)
    {
        pUser = g_users + i;
        if(pUser->pid == -1)
           continue;
        
        if(kill(pUser->pid, 0) == -1)
        {
            pUser->pid = -1;
            continue;
        }

        if(strcmp(pUser->username, name) == 0)
        {
            printf("username %s exist\n", name);
            return;
        }
    }

    for(int i=0; i<total_user_count; ++i)
    {
        pUser = g_users + i;
        if(pUser->pid == -1)
            break;
    } 
    pUser->pid = getpid();
 //   strcpy(pUser->username, name);
    strncpy(pUser->username, name, sizeof(pUser->username));
    g_me = pUser;
}

void sendall(const char* content)
{
    // 把信号屏蔽
    flock(g_fd, LOCK_EX);
    sprintf(g_content, "%s:%s", g_me->username, content);
    flock(g_fd, LOCK_UN);
    // 把信号恢复
    for(int i=0; i<total_user_count; ++i)
    {
        user* pUser = g_users + i;
        if(pUser->pid != -1)
        {
            if(pUser->pid != getpid())
                kill(pUser->pid, SIGUSR1);
        }
    }
}

void sendone(const char* content, const char* touser)
{
    int find = 0;
    flock(g_fd, LOCK_EX);
    sprintf(g_content, "%s:%s", g_me->username, content);
    flock(g_fd, LOCK_UN);

    for(int i=0; i<total_user_count; ++i)
    {
        user* pUser = g_users + i;
        // set xxx --> exit
        // {xxx, -1}
        if(strcmp(pUser->username, touser) == 0
                && pUser->pid != -1)
        {
            if(kill(pUser->pid, SIGUSR1) == -1)
            {
                pUser->pid = -1;
                break;
            }
            find = 1;
            break;
        }
    }
    if(find == 0)
    {
        printf("not find user\n");
    }
}

void show_all_user()
{
    printf("userlist:\n");
    for(int i=0; i<total_user_count; ++i)
    {
        user* pUser = g_users + i;
        if(pUser->pid != -1 && kill(pUser->pid, 0) == 0)
        {
            printf("  %s\n", pUser->username);
        }
        else
        {
            pUser->pid = -1;
        }
    }
}

// cmd:
// set xxxx yyy
// send xx how are you
// send all how are you
void handle_cmd()
{
    char* saveptr = NULL;
    char* cmd = strtok_r(g_cmd, " \t", &saveptr);
    if(strcmp(cmd, "set") == 0)
    {
        // 设置用户名
        char* username = strtok_r(NULL, " \t", &saveptr);
        setname(username);
    }
    else if(strcmp(cmd, "send") == 0)
    {
        char* touser = strtok_r(NULL, " \t", &saveptr);
        char* content = saveptr;
        if(g_me == NULL)
        {
            printf("please set your username first\n");
            return;
        }

        if(strlen(content) > 3900)
        {
            printf("msg is too long\n");
            return;
        }

        if(strcmp(cmd, "all") == 0)
        {
            // 群发
            sendall(content);
        }
        else
        {
            // 单发
            sendone(content, touser);
        }
    }
    else if(strcmp(cmd, "list") == 0)
    {
        show_all_user();
    }
    else
    {
        printf("unknown command\n");
    }
}

int main()
{
     //初始化共享内存
    init_share_memory();
    signal(SIGUSR1, sig_handler);

    while(1)
    {
        get_cmd();
        if(strlen(g_cmd) == 0)
            continue;
        handle_cmd();
    }   
}

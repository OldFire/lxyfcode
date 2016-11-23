#include"h.h"
#include<list>
using namespace std;

pthread_mutex_t g_mutex;
pthread_cond_t g_cond;
list<int>tasks;
void*thread_func(void*arg)
{
    while(1)
    {
        pthread_mutex_lock(&g_mutex);
        pthread_cond_wait(&g_cond,&g_mutex);
        pthread_mutex_unlock(&g_mutex);

        while(1)
        {
            pthread_mutex_lock(&g_mutex);
            if(tasks.size()==0)
            {
                pthread_mutex_unlock(&g_mutex);
                break;
            }
            int task=tasks.front();
            tasks.pop_front();
            printf("task is %d\n",task);
            pthread_mutex_unlock(&g_mutex);
        }
    }
    return NULL;
}

int main()
{
    pthread_mutex_init(&g_mutex,NULL);
    pthread_cond_init(&g_cond,NULL);

    pthread_t tid;
    pthread_create(&tid,NULL,thread_func,NULL);

    while(1)
    {
        char buf[1024];
        fgets(buf,sizeof(buf),stdin);
        int task=atoi(buf);
        pthread_mutex_lock(&g_mutex);
        tasks.push_back(task);
        pthread_mutex_unlock(&g_mutex);

        pthread_cond_signal(&g_cond);
    }
    return 0;

}



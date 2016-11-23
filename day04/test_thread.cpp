#include "h.h"

int *p=NULL;
void*thread_func(void*arg)
{
    (*p)++;

    printf("*p=%d\n",*p);
    return NULL;
}

int main()
{   
    int a=1;

    p=&a;

    pthread_t tid;
    pthread_create(&tid,NULL,thread_func,NULL);
    sleep(1);
    printf("main:*p=%d\n",*p);
    pthread_join(tid,NULL);
    return 0;
}

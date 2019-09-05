#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

int var =100;

void *tfn(void * arg)
{
    //子线程修改var
    var = 200;
    printf("thread\n");

    return NULL;
}

int main(void)
{
    printf("At first var = %d\n",var);

    pthread_t tid;
    pthread_create(&tid,NULL,tfn,NULL);
    sleep(1);
    //等子线程退出后，再次打印var
    printf("after pthread_create, var = %d\n",var);

    return 0;
}

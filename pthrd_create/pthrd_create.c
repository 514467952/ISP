#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

void *thrd_func(void *arg)
{
    //子线程的ID
    printf(" In thread id = %lu,pid = %u\n",pthread_self(),getpid());
    return NULL;
}

int main(void)
{
    pthread_t tid;
    int ret;
    
    //主控线程ID
    printf(" In main1 id = %lu,pid = %u\n",pthread_self(),getpid());

    
    ret = pthread_create(&tid,NULL,thrd_func,NULL);

    if(ret != 0){
        fprintf(stderr,"pthread_create error:%s\n",strerror(ret));
        exit(1);
    }

    printf(" In main2 id = %lu,pid = %u\n",pthread_self(),getpid());
    sleep(1);//主控线程等待子线程1秒，让它打印

    return 0;
}

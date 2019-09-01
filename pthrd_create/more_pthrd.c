#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

void *thrd_func(void *arg)
{
   // int i=*((int*)arg);

    int i = (int)arg
    sleep(i);    
    //子线程的ID
   printf("%d th In thread id = %lu,pid = %u\n", i+1 ,pthread_self(),getpid());
    return NULL;
}

int main(void)
{
    pthread_t tid;
    int ret,i;
    
    for(i=0;i < 5; i++)
    {
        ret = pthread_create(&tid,NULL,thrd_func,(void *)i);
        if(ret != 0){
            fprintf(stderr,"pthread_create error:%s\n",strerror(ret));
            exit(1);
        }
    }
    
    sleep(i);// 主控线程等待子线程1秒，让它打印
    
    return 0;// 将当前进程退出
}

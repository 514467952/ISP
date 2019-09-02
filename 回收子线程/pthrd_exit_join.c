#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

typedef struct{
    int a;
    int b;
}exit_t;


void * tfn(void *arg)   //子线程函数
{
    //子线程函数中定义 ret;
    exit_t *ret; //用结构体定义一个变量
    ret=malloc(sizeof(exit_t));

    ret->a = 100;
    ret->b = 300;
    
    //返回ret 这个值，线程退出
    pthread_exit((void *)ret);
}


int main(void)
{
    pthread_t tid;
    exit_t *retval;

    pthread_create(&tid,NULL,tfn,NULL);

    /*调用pthread_join可以获取线程退出状态*/
    //第一个回收线程ID，第二个回收退出的值
    pthread_join(tid,(void **)&retval);   //wait(&status);
    printf("a = %d,b = %d\n",retval->a,retval->b);

    return 0;
}

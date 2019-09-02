#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>

typedef struct {
    char ch;
    int var;
    char str[64];
}exit_t;

void *thrd_func(void *arg)
{
    //创建结构体变量
    exit_t * retvar = (exit_t *)malloc(sizeof(exit_t));
    //赋值
    retvar->ch='m';
    retvar->var = 200;
    strcpy(retvar->str,"我的返回值");
    //子线程退出
    pthread_exit((void *)retvar);

}

int main(void)
{
    pthread_t tid;
    int ret;
    exit_t * retval;
    
    //主控线程ID
    printf(" In main1 id = %lu,pid = %u\n",pthread_self(),getpid());

    
    ret = pthread_create(&tid,NULL,thrd_func,NULL);

    if(ret != 0){
        fprintf(stderr,"pthread_create error:%s\n",strerror(ret));
        exit(1);
    }
    
    pthread_join(tid,(void **)&retval);
    printf("子线程返回值为\n");
    printf("ch = %c ,var = %d,str = %s\n",retval->ch,retval->var,retval->str);
    pthread_exit((void *)1);

    return 0;
}

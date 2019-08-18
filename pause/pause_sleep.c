/*
 * 模拟实现sleep
 */
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<errno.h>
void catch_sigalrm(int signo)//捕捉函数 保证pause不会被杀死
{
    ;
}


unsigned int mysleep(unsigned int seconds)
{
    int ret;
    struct sigaction act,oldact;
    act.sa_handler = catch_sigalrm;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    ret = sigaction(SIGALRM,&act,&oldact);//注册捕捉函数    改变了SIGALRM信号的设置
    if(ret == -1){
        perror("sigaction error");
        exit(1);
    }

    //屏蔽
    alarm(seconds);
    //-------------------假设此时刻失去cpu，等cpu再来就无时钟信号，无法调用pause
    ret =  pause();//主动挂起 等信号
    //解除屏蔽

    if(ret == -1 && errno == EINTR){
        printf("pause sucess\n");
    }
    
    alarm(0);//将闹钟清零
    sigaction(SIGALRM,&oldact,NULL);//恢复SIGALRN信号旧有的处理方式

    return ret;
}


int main(void)
{
    while(1){
        mysleep(3);
        printf("-----------------\n");
    }

    return 0;
}

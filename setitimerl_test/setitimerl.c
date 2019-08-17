#include<stdio.h>
#include<sys/time.h>
#include<signal.h>

void myfunc(int signo)
{
    printf("hello world\n");
}

int main(void)
{
    struct itimerval it,oldit;
    signal(SIGALRM,myfunc); //注册SIGALRM信号的捕捉处理函数

    //sighandler_t tml=signal(SIGALRM,myfunc);
    
    it.it_value.tv_sec=5;//定时5秒中
    it.it_value.tv_usec=0;//0微秒

    it.it_interval.tv_sec=3;//第一个和第二个之间间隔时间3秒
    it.it_interval.tv_usec=0;
    
    if(setitimer(ITIMER_REAL,&it,&oldit) == -1){
        perror("setitimer error");
        return -1;
    }
    while(1);

    
    return 0;
}

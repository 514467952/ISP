#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>

/*
 * 循环创建 5 个子进程
 */

#define N  5
int main()
{
    int i;
    pid_t pid,q;

    for(i=0;i<N;i++){
        pid = fork();
        if(pid == 0)
            break;
        if(i==2)
            q=pid;
    }
    if(i<5){
        while(1){
            printf("I am child %d,getpid= %d\n",i,getpid());
            sleep(1);
        }
    }else{
        sleep(1);
        kill(q,SIGKILL);
        while(1);
    }


    return 0;
}

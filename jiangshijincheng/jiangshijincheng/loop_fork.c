#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(int argc,char *argv[])
{
    int n=5,i; //默认创建5个进程
    pid_t p,q;
    
    pid_t wpid;
    if(argc==2){
        n=atoi(argv[1]);
    }

    for(i=0;i<n;i++){ //出口1，父进程专用出口
        p=fork();
        if(p==0){
            break;       //出口2，子进程出口，i不自增
        }else if(i==3){
            q=p;
        }
    }
    
    //父进程
    if(n==i){
        sleep(n);
        printf("I am parent,pid= %d\n",getpid(),getgid());
        do{
            wpid=waitpid(-1,NULL,WNOHANG);//====wait(NULL);
            if(wpid>0){
                n--;
            }
            //if wpid==0 说明子进程正在运行，
            sleep(1);
        }while(n>0);
        //循环回收多个子进程
        //while(wait(NULL));
        //while(1);
        printf("wait finish\n");

    //打印子进程
    }else{
        sleep(i);
        printf("I am %dth child,pid= %d,gpid=%d\n",i+1,getpid(),getgid());
    }
    return 0;
}


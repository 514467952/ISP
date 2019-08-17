/*
 * 打印未决信号集
 */

#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void printped(sigset_t * ped)
{
    int i;
    //常用的是前32个信号
    for(i = 1; i < 32; i++ ){
        if(sigismember(ped,i) == 1){
            //在集合中
            putchar('1');
        }else{
            putchar('0');
        }
    }
    printf("\n");
}



int main(void )

{
    sigset_t myset, oldset ,ped;

    sigemptyset(&myset);
    sigaddset(&myset,SIGQUIT);//屏蔽系统本身3号信号
    sigaddset(&myset,SIGINT);//屏蔽系统本身的2号信号
    sigaddset(&myset,SIGTSTP);
    sigaddset(&myset,SIGSEGV);
    sigaddset(&myset,SIGKILL);

    sigprocmask(SIG_BLOCK,&myset,&oldset);
    
    while(1){
        sigpending(&ped);
        //判断集合中每个信号的对应位是0还是1
        printped(&ped);
        sleep(1);
    }


    return 0;
}

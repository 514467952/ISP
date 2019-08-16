#include<stdio.h>
#include<unistd.h>

int main()
{
    int i;
    alarm(1);//1s后发信号

    for(i=0;;i++) //死循环看在闹钟的1s时间内跑多少下
        printf("%d\n",i);

    return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<sys/wait.h>

int var=100;

int main(void )
{
    int *p;
    pid_t pid;


    
    //不使用文件参数传-1
    p=(int *)mmap(NULL,4,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANON,-1,0);//对映射区各自独占
    if(p==MAP_FAILED){              //不是p==NULL时出错
        perror("mmap,error");       
        exit(1);
    }

    //完成数据传递
    pid=fork();
    if(pid==0){
        *p=2000;
        var=1000;
        printf("child,*p=%d,var = %d\n",*p,var);
    }else{
        sleep(1);
        
        printf("parent,*p = %d,var = =%d\n",*p,var);
        wait(NULL);

        int ret= munmap(p,4); 
        if(ret==-1){
            perror("munmap error");
            exit(1);
        }
    }
    return 0;
}

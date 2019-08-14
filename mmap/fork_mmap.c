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

    int fd;
    fd=open("temp",O_RDWR|O_CREAT|O_TRUNC,0644);
    if(fd<0){
        perror("open error:");
        exit(1);
    }

    unlink("temp");          //删除临时文件目录项，使之具备被释放条件,所有使用该文件的进程结束后该文件才释放
    ftruncate(fd,4);        //创建文件大小
    
    p=(int *)mmap(NULL,4,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);//父子进程共享映射区

   // p=(int *)mmap(NULL,4,PROT_READ|PROT_WRITE,MAP_PRIVATE,fd,0);//对映射区各自独占
    if(p==MAP_FAILED){              //不是p==NULL时出错
        perror("mmap,error");       
        exit(1);
    }
    close(fd);              //映射区建立完毕，即可关闭文件

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

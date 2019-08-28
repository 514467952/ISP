#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void mydaemond(void)
{
    pid_t pid,sid;
    
    int ret;

    pid = fork();
    if(pid > 0){
        //父进程退出
        return 0;
    }

    //创建会话
    sid = setsid();

    ret = chdir("/home/itcast/"); 

    if( ret == -1 ){
        perror("chdir error");
        exit(1);
    }

    umask(0022);

    close(STDOUT_FILENO);
    open("/dev/null",O_RDWR);
    dup2(0,STDOUT_FILENO);
    dup2(0,STDERR_FILENO);

}

int main(void)
{
    mydaemond();

    while(1){

    }

    return 0;
}

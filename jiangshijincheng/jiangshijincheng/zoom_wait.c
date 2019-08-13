#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>


int main(void)
{
    pid_t pid,wpid;
    pid=fork();
    
    int status;
    if(pid==0){
       // pritnf("---child,my parent= %d,going to sleep 10s\n",getppid());
        sleep(20);
        printf("----------------child die--------------\n");
        return 100 ;

    }else if(pid>0){

        wpid=wait(&status);
        if(wpid==-1){
            perror("wait error:");
            exit(1);
        }
        if(WIFEXITED(status)){
            printf("child exit with %d\n",WEXITSTATUS(status));
        }
        if(WIFSIGNALED(status)){
            printf("child killed by %d\n",WTERMSIG(status));
        }

        while(1){
           // printf("I am parent,pid= %d,myson = %d\n",getpid(),pid);
            sleep(1);
        }
    }else{
        perror("fork");
        return 1;
    }
    return 0;
}

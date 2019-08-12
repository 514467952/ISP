#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(void)
{
    pid_t pid;
    pid=fork();
    if(pid==-1)
    {
        perror("fork error:");
        exit(1);
    }else if(pid>0)
    {
        sleep(1);
        printf("parent\n");
    }else{
        
       // execlp("ls","ls","-l","-h",NULL);
       // execl("/bin/ls","ls","-l","-h",NULL);
       execl("./execl_test","execl_test","NULL");
    }

    return 0;
}

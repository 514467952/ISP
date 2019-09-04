#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>

void *tfn(void *arg)
{
    int n=3;
    
    while(n--){
        printf("thread count %d\n",n);
        sleep(1);
    }

    return (void *)1;
}

int main(void)
{
    pthread_t tid;
    void *tret;
    int err;
    
    pthread_create(&tid,NULL,tfn,NULL);
    pthread_detach(tid);        //让线程分离   ----自动退出，无系统残留资源
    
    while(1){
        err = pthread_join(tid,&tret);
        printf("---------err= %d\n",err);
        if(err != 0)
            fprintf(stderr,"thread error: %s\n",strerror(err));
        else
            fprintf(stderr,"thread exit code %d\n",(int)tret);

        sleep(1);
    }
    return 0;
}

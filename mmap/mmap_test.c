#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/mman.h>
int main(void)
{
    int len,ret;
    char *p=NULL;
    int fd = open("mytest.txt",O_CREAT|O_RDWR,0644);
    if(fd<0){
        perror("open error");
        exit(1);
    }
    //确定文件大小
     len = ftruncate(fd,4);
    if(len == -1){
        perror("ftruncate error:");
        exit(1);
    }

    p = mmap(NULL, 4 , PROT_READ|PROT_WRITE , MAP_SHARED, fd, 0);
    if(p == MAP_FAILED){
        perror("mmap error:");
        exit(1);
    }

    strcpy(p,"abc");//写数据

    ret = munmap(p,4);//释放映射区
    if(ret==-1){
        perror("munmap error:");
        exit(1);
    }
    close(fd);

    return 0;
}

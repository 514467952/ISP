#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void)
{
    char *val;
     const char *name="ABD";
    
    //从当前的环境变量表中获得名字为name的环境变量值，保存到val里
    val=getenv(name);
    printf("1, %s = %s\n",name,val);//获取不出来，出一个空值
    
    //覆盖原有的环境变量
    setenv(name,"haha-day-and-night",1);

    //再获取环境变量
    val=getenv(name);
    printf("2, %s = %s\n",name,val);

    
#if 1
    
    int ret=unsetenv("ABDFGH");//name=value:value
    printf("ret= %d\n",ret); 

    val=getenv(name);
    printf("3, %s = %s\n",name,val);
    
#else


    //删除刚添加的ABD
    int ret=unsetenv("ABD");//name=value:value
    printf("ret= %d\n",ret); 

    val=getenv(name);
    printf("3, %s = %s\n",name,val);
#endif
    return 0;
}

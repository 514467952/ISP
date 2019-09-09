/*使用信号量实现生产者与消费者模型
 *
 */

#include<iostream>
#include<queue>
#include<pthread.h>
#include<semaphore.h>

class RingQueue
{
    public:
        RingQueue(int cap = 10):_capacity(cap),_queue(cap){
            //1.信号量变量
            //2.参数取值    0：用于线程间同步与互斥
            //              非0：用于进程间同步与互斥
            //3.信号量初值
            sem_init(&_sem_lock,0,1);//互斥锁初始值只给1
            sem_init(&_sem_data,0,0);//初始数据资源数据为0
            sem_init(&_sem_space,0,cap);//初始空闲空间计数
        }
        ~RingQueue(){
            sem_destroy(&_sem_lock);
            sem_destroy(&_sem_data);
            sem_destroy(&_sem_space);
        }
        void QueuePush(int data){

            // ProWait();//空闲空间计数判断是否有空闲空间，若有返回，否则等待
            // 因为已经通过_sem_space的空闲空间计数知道是否有空闲空间
            sem_wait(&_sem_space);//添加数据之后，空闲空间计数-1

            sem_wait(&_sem_lock);//锁计数初始为1，一旦进入-1加锁
            _queue[_step_write]=data;
            _step_write = ( _step_write + 1) % _capacity;
            sem_post(&_sem_lock);//数据添加完毕后解锁，数据资源计数+1

            sem_post(&_sem_data);//数据添加完毕后，数据资源计数+1
            //ConWakeUp();

        }
        void QueuePop(int *data){

            sem_wait(&_sem_data);//取数据的时候，数据资源计数-1

            sem_wait(&_sem_lock);//锁最好仅仅保护临界区

            *data = _queue[_step_read];
            _step_read = (_step_read + 1) % _capacity;
            sem_post(&_sem_lock);

            sem_post(&_sem_space);//取数据之后，空闲空间计数+!

        }
    private:
        std::vector<int>_queue;
        int _capacity; //队列最大数量
        int _step_write;//当前写到哪里的下标
        int _step_read;//当前读到哪里了的下标

        sem_t _sem_lock;//实现互斥锁
        sem_t _sem_space;//空闲空间计数
        sem_t _sem_data;//数据资源计数
        
/*
        //队列加锁
        void QueueLock(){
            pthread_mutex_lock(&_mutex);
        }
        //队列解锁
        void QueueUnLock(){
            pthread_mutex_unlock(&_mutex);
        }
         
  */  
};


void *thr_productor(void *arg){
    RingQueue *q = (RingQueue*)arg;
    int i=0;
    while(1){
        q->QueuePush(i);
        std::cout<<"thread:"<<pthread_self()<<"put data"<<i++<<"\n";
    }
    return NULL;
}

void *thr_consumer(void *arg){
    RingQueue *q = (RingQueue*)arg;
    while(1){
        int data;
        q->QueuePop(&data);
        std::cout<<"thread:"<<pthread_self()<<"get data"<<data<<"\n";
    }
    return NULL;
}

int main(int argc,char *argv[])
{
    RingQueue q;
    pthread_t ptid,ctid[4];
    int i ,ret;

    ret = pthread_create(&ptid,NULL,thr_productor,(void *)&q);
    if(ret != 0){
        std::cout<<"thread create error\n";
        return -1;
    }

    for(i = 0;i < 4;i++){
        ret = pthread_create(&ctid[i],NULL,thr_consumer,(void *)&q);
        if(ret != 0){
            std::cout<<"thread create error\n";
            return -1;
        }
    }

    for(i = 0; i < 4; i++){
        pthread_join(ctid[i],NULL);
    }

    pthread_join(ptid,NULL);

    return 0;
}




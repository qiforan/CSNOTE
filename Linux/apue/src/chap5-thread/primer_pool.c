//
// 线程池：
// note:
//      1。 sched_yield
//      2。 临界区跳转语句特别注意
//
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define LEFT 2
#define RIGHT 100
#define THRNUM 20

static int num = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static void *thr_prime(void *p)
{
    int i = 0;
    while(1){
        pthread_mutex_lock(&mutex);
        // 确保 num 不为 0
        while(num == 0){
            pthread_mutex_unlock(&mutex);
            sched_yield();
            pthread_mutex_lock(&mutex);
        }
        i = num;
        if(num != -1)
            num = 0;
        pthread_mutex_unlock(&mutex);
        if(i == -1){
            break;
        }
        int flag = 1;
        for(int j = 2; j <= i/2; ++j)
            if(i % j == 0){
                flag = 0;
                break;
            }
        if(flag){
            printf("%d\n",i);
        }
    }
    pthread_exit(NULL);
}

int main()
{
    int i ,err;
    pthread_t tid[THRNUM];
    for(i = 0; i < THRNUM; ++i){
        err = pthread_create(tid+i, NULL, thr_prime, NULL);
        if(err){
            fprintf(stderr, "pthread_create():%s\n", strerror(err));
        }
    }
    for(i = LEFT; i <= RIGHT; ++i){
        pthread_mutex_lock(&mutex);
        // 确保 num 被改变
        while(num != 0){
            pthread_mutex_unlock(&mutex);
            sched_yield();
            pthread_mutex_lock(&mutex);
        }
        num = i;
        pthread_mutex_unlock(&mutex);
    }
    pthread_mutex_lock(&mutex);
    while (num != 0){
        pthread_mutex_unlock(&mutex);
        sched_yield();
        pthread_mutex_lock(&mutex);
    }
    num = -1;
    pthread_mutex_unlock(& mutex);
    for(int i = 0; i < THRNUM; ++i){
        pthread_join(tid[i],NULL);
    }
    return 0;
}
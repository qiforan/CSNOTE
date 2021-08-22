//
// Created by wch on 2020/12/8.
// 使用互斥量同步打印 abcd
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define THRNUM 4

static pthread_mutex_t mut[THRNUM];

static void *thr_func(void *p)
{
    int i = (int)p;
    int c = 'a' + i;
    while (1){
        pthread_mutex_lock(&mut[i]);
        write(1, &c, 1);
        pthread_mutex_unlock(&mut[(i+1)%THRNUM]);
    }
    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    pthread_t tid[THRNUM];
    int err;
    int i;
    for (i = 0; i < THRNUM; i++) {
        pthread_mutex_init(mut+i,NULL);
        pthread_mutex_lock(&mut[i]);
        err = pthread_create(tid + i, NULL, thr_func, (void *) i);
        if (err) {
            fprintf(stderr, "pthread_create():%s\n", strerror(err));
            exit(1);
        }
    }
    pthread_mutex_unlock(&mut[0]);
    alarm(5);
    for (i = 0; i < THRNUM; i++)
        pthread_join(tid[i], NULL);
    exit(0);
}

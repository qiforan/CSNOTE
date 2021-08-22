//
// Created by wch on 2020/12/8.
//
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

static void *func(void * p)
{
    puts("Thread is running");
    return NULL;
}

int main(int argc, char **argv)
{
    pthread_t tid;
    int err;
    puts("begin");
    err = pthread_create(&tid, NULL, func, NULL);
    if(err){
        fprintf(stderr, "pthread_create(): %s\n", strerror(err));
        exit(1);
    }
    pthread_join(tid, NULL);
    puts("end");
    exit(0);
}

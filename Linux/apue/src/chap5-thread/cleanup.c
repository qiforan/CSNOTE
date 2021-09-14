//
// Created by wch on 2020/12/8.
//
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

static void cleanup_func(void *p)
{
    puts(p);
}

static void *func(void *p)
{
    puts("thread is working");
    pthread_cleanup_push(cleanup_func,"cleanup:1");
    pthread_exit(NULL);
    pthread_cleanup_pop(1);
}

int main(int argc, char ** argv)
{
    pthread_t tid;
    int err;
    puts("begin");
    err = pthread_create(&tid, NULL,func,NULL);
    if(err){
        fprintf(stderr,"pthread_create(): %s\n", strerror(err));
        exit(1);
    }

    puts("end");
    exit(0);
}

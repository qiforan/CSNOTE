//
// Created by wch on 2020/12/6.
//

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

static int loop = 1;
static const t = 5;

static void fun1()
{
    time_t end;
    int64_t count = 0;
    end = time(NULL) + t;
    while(time(NULL) <= end)
        count++;
    printf("func1 %lld\n", count);
}

static void alarm_handler(int s)
{
    loop = 0;
}

static void fun2()
{
    int64_t count = 0;
    signal(SIGALRM,alarm_handler);
    alarm(t);
    while(loop)
        count++;
    printf("func2 %lld\n", count);
}

int main(int argc, char **agv)
{
    fun1();
    fun2();
    exit(0);
}

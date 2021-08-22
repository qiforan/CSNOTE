//
// Created by wch on 2020/12/6.
//
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void handle_signal(int x)
{
    signal(SIGALRM,SIG_DFL);
}

void mysleep(int seconds)
{
    signal(SIGALRM, handle_signal);
    alarm(seconds);
    pause();
}
int main(int argc, char **argv)
{
    puts("start");
    mysleep(4);
    printf("end");
    exit(0);
}


//
// Created by wch on 2020/12/3.
//
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static void int_handler(int s)
{
    write(1,"!",1);
}

int main(int argc, char ** argv)
{
    int i;
    signal(SIGINT,int_handler);
    for(i = 0; i < 10; i++)
    {
        write(1,"*",1);
        sleep(1);
    }
    exit(0);
}

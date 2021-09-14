//
// Created by wch on 2020/11/28.
//
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    puts("Begin!");
    execl("/bin/date","date","+%s",NULL);
    perror("execl");
    puts("end!");
    exit(0);
}


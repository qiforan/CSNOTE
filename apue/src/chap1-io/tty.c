//
// Created by wch on 2020/12/22.
//
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd = open("/tmp/test", O_RDWR | O_CREAT);
    dup2(fd,1);
    printf("current tty: %s\n", ttyname(1));
//    perror("ttyname()");
    exit(0);
}


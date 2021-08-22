//
// Created by wch on 2020/11/23.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char ** argv)
{
    int fd;
    if(argc < 2){
        fprintf(stderr, "Usage:...\n");
        exit(1);
    }
    fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if(fd < 0){
        perror("open()");
        exit(1);
    }

    //不使用LL就会溢出
    lseek(fd, 5LL*1024LL*1024LL*1024LL-1LL, SEEK_SET);
    write(fd,"", 1);
    close(fd);
    exit(0);
}

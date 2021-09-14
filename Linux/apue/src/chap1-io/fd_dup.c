//
// Created by wch on 2020/11/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

const char * FNAME = "/tmp/fd_dup";

int main(int argc, char ** argv)
{
    int fd;
    fd = open(FNAME,O_WRONLY|O_CREAT|O_TRUNC, 0600);
    if(fd < 0){
        perror("open()");
        exit(1);
    }
    close(1);
    // 此处可能被打断，1号描述符被其他线程利用，则 dup 达不到要求
    dup(fd);
    close(fd);
    puts("hello");
    exit(0);
}


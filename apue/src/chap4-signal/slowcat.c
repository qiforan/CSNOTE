//
// Created by wch on 2020/12/6.
//

#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define BUFSIZE 1024

int main(int argc, char **argv)
{
    int sfd, dfd = 1;
    char buf[BUFSIZE];
    int len, ret, pos;
    if (argc < 2) {
        fprintf(stderr, "Usage:...\n");
        exit(1);
    }
    do {
        sfd = open(argv[1], O_RDONLY);
        if (sfd < 0) {
            if (errno == EINTR) {
                perror("open()");
                exit(1);
            }
        }
    } while (sfd < 0);
    while (1) {
        len = read(sfd, buf, BUFSIZE);
        if(len < 0){
            if(errno == EINTR)
                continue;
            perror("read()");
        }
        if(len == 0) // end of file
            break;
        pos = 0;
        while(len > 0){
            ret = write(dfd, buf+pos, len);
            if(ret < 0){
                perror("write()");
                exit(1);
            }
            len -= ret;
            pos += ret;
        }
    }
    exit(0);
}

//
// Created by wch on 2020/11/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 1024

static int line_size(const char *str, int n)
{
    int i = 0;
    while (i < n && str[i++] != '\n');
    return i > n ? -1 : i;
}

static ssize_t read_lines(int fd, int n)
{
    char buf[BUFSIZE];
    int lines = 0;
    ssize_t sum_bytes = 0;
    while (1) {
        ssize_t read_bytes = read(fd, buf, BUFSIZE);
        if (read_bytes == 0) { // file End
            return -1;
        }
        int pos = 0;
        while (pos < read_bytes) {
            int line_bytes = line_size(buf + pos, read_bytes - pos);
            if(line_bytes < 0) // not get the line end
                break;
            if (lines++ < n) {
                sum_bytes += line_bytes;
                pos += line_bytes; // +1 because of  \n
            } else break;
        }
        if (lines >= n)
            break;
    }
    return sum_bytes;
}

int main(int argc, char **argv)
{
    int fd;
    ssize_t read_pos, write_pos;
    char buf[BUFSIZE];
    if (argc < 2) {
        perror("Usage: delete_line_10 filename");
        exit(1);
    }
    fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        perror("open()");
        exit(1);
    }
    ssize_t line_10_pos = read_lines(fd, 10 - 1);
    if (line_10_pos == -1) {
        close(fd);
        exit(0);
    }
    write_pos = line_10_pos;
    lseek(fd,write_pos,SEEK_SET);
    read_pos = write_pos + read_lines(fd, 1);
    while (1) {
        lseek(fd, read_pos, SEEK_SET);
        ssize_t read_bytes = read(fd, buf, BUFSIZE);
        if (read_bytes == 0)
            break;
        read_pos += read_bytes;
        ssize_t writen_bytes = 0;
        lseek(fd, write_pos, SEEK_SET);
        while (writen_bytes < read_bytes) {
            ssize_t write_bytes = write(fd, buf + writen_bytes, read_bytes - writen_bytes);
            writen_bytes += write_bytes;
        }
        write_pos += writen_bytes;
    }
    ftruncate(fd, write_pos);
    close(fd);
    exit(0);
}

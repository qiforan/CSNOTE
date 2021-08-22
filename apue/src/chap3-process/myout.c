//
// Created by wch on 2020/12/3.
// 不使用 1 号描述符，向终端输出字符
//

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

ssize_t get_lf_pos(const char *str)
{
    ssize_t pos = 0;
    int len = strlen(str);
    while(pos < len && str[pos] != '\n') pos++;
    return pos < len ? pos : -1;
}

int main(int argc, char ** argv)
{
    char path[1024];
    char buf[1024] = "hello world";
    int fd;
    int len;
    FILE *fp;
    //获取当前终端设备
    fp = popen("tty", "r");
    fgets(path,sizeof(path),fp);
    len = get_lf_pos(path);
    if(len < 0)
    {
        perror("popen");
        exit(1);
    }
    //截断到设备名
    path[len] = '\0';
    fd = open(path, O_RDWR);
    write(fd,buf,1024);
    close(fd);
    exit(0);
}

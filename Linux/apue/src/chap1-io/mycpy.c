//
// Created by wch on 2020/11/17.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *fps,*fpd;
    int ch;
    if(argc < 3){
        fprintf(stderr, "Usage: %s <sourcefile> <destfile>", argv[0]);
        exit(1);
    }
    fps = fopen(argv[1], "r");
    if(fps == NULL){
        perror("fopen()");
        exit(1);
    }
    fpd = fopen(argv[2], "w");
    if(fpd == NULL){
        fclose(fps);
        perror("fopen()");
        exit(1);
    }
    while (1){
        ch = fgetc(fps);
        if(ch == NULL)
            break;
        fputc(ch, fpd);
    }
    // 先关闭被依赖
    fclose(fpd);
    // 再关闭依赖
    fclose(fps);
    exit(0);
}


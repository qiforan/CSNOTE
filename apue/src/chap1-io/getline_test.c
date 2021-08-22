//
// Created by wch on 2020/11/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv)
{
    char *linebuf ;
    size_t linesize;
    FILE *fp;
    if(argc < 2){
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(1);
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL){
        perror("fopen()");
        exit(1);
    }
    while(1){
        if(getline(&linebuf, &linesize, fp) < 0)
            break;
        printf("%d\n",strlen(linebuf));
        printf("%d\n", linesize);
    }
    fclose(fp);
    exit(0);
}

//
// Created by wch on 2020/11/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

static long long flen(char *fname)
{
    struct stat statres;
    if(stat(fname, &statres) < 0){
        perror("stat()");
        exit(1);
    }
    return statres.st_size;
}

int main(int argc, char ** argv)
{
    if(argc < 2){
        fprintf(stderr, "Usage: ...\n");
        exit(1);
    }
    printf("%lld\n",flen(argv[1]));
    exit(0);
}

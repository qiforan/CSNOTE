//
// Created by wch on 2020/11/24.
//
#include <stdio.h>
#include <stdlib.h>
#include <glob.h>

#define PAT "/etc/*"
int errfunc_(const char *errpath, int errno)
{
    puts(errpath);
    fprintf(stderr, "ERROR MESSAGE: %s\n", errno);
}
int main()
{
    glob_t globres;
    int i,err;
    err = glob(PAT, 0, NULL, &globres);
    if(err){
        printf("ERROR CODE = %d\n", err);
    }
    for(i = 0; i < globres.gl_pathc; i++)
        puts(globres.gl_pathv[i]);
    globfree(&globres);
    exit(0);
}

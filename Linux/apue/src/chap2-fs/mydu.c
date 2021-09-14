//
// Created by wch on 2020/11/24.
//

#include <stdlib.h>
#include <stdio.h>
#include <glob.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define PATHSIZE 1024

static int path_noloop(const char *path)
{
    char *pos;
    pos = strrchr(path, '/');
    if (pos == NULL) {
        fprintf(stderr, "path_noloop() at %s failed", path);
        exit(1);
    }
    if (strcmp(pos + 1, ".") == 0 || strcmp(pos + 1, "..") == 0)
        return 0;
    return 1;
}

static int64_t mydu(const char *path)
{
    int i;
    struct stat statres;
    char nextpath[PATHSIZE];
    int64_t sum = 0;
    glob_t globres;
    if (lstat(path, &statres) < 0) {
        perror("lstat()");
        exit(1);
    }
    sum += statres.st_blocks;
    // if regular file
    if (!S_ISDIR(statres.st_mode))
        return statres.st_blocks;

    //if directory
    strncpy(nextpath, path, PATHSIZE);
    strncat(nextpath, "/*", PATHSIZE);
    glob(nextpath, 0, NULL, &globres);
    strncpy(nextpath, path, PATHSIZE);
    strncat(nextpath, "/.*", PATHSIZE);
    glob(nextpath, GLOB_APPEND, NULL, &globres);
    for (i = 0; i < globres.gl_pathc; i++)
        if (path_noloop((globres.gl_pathv[i])) == 1)
            sum += mydu(globres.gl_pathv[i]);
    globfree(&globres);
    return sum;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage: ...\n");
    }
    printf("total: %lld\n", mydu(argv[1]) / 2);
}


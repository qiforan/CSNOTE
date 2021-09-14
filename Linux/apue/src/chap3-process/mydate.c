//
// Created by wch on 2020/11/26.
//
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*
 * -y: year
 * -m: month
 * -d: day
 * -H: hour
 * -M: minute
 * -S: second
 * filename
 * */

#define TIMESTRSIZE 1024
#define FMTSTRSIZE 1024

int main(int argc, char **argv)
{
    time_t stamp;
    struct tm *tm;
    FILE *fp = stdout;
    char timestr[TIMESTRSIZE];
    int c;
    if (argc < 2) {
        fprintf(stderr, "Usage:...\n");
        exit(1);
    }
    stamp = time(NULL);
    tm = localtime(&stamp);
    char fmtstr[FMTSTRSIZE];
    fmtstr[0] = '\0';


    while (1) {
        c = getopt(argc, argv, "-H:MSy:md");
        if (c < 0)
            break;
        switch (c) {
            case 1:
                fp = fopen(argv[optind-1],"w");
                if(fp == NULL){
                    perror("fopen()");
                    fp = stdout;
                }
                break;
            case 'H':
                if (strcmp(optarg, "12") == 0)
                    strncat(fmtstr, "%I(%P) ", FMTSTRSIZE);
                else if(strcmp(optarg, "24") == 0)
                    strncat(fmtstr, "%H ", FMTSTRSIZE);
                else
                    fprintf(stderr,"Invalid argument -H\n");
                break;
            case 'M':
                strncat(fmtstr, "%M ", FMTSTRSIZE);
                break;
            case 'S':
                strncat(fmtstr, "%S ", FMTSTRSIZE);
                break;
            case 'y':
                if(strcmp(optarg, "2") == 0)
                    strncat(fmtstr, "%y ",FMTSTRSIZE);
                else if(strcmp(optarg, "4") == 0)
                    strncat(fmtstr, "%Y ", FMTSTRSIZE);
                else
                    fprintf(stderr,"Invalid argument -y\n");
                strncat(fmtstr, "%y ", FMTSTRSIZE);
                break;
            case 'm':
                strncat(fmtstr, "%m ", FMTSTRSIZE);
                break;
            case 'd':
                strncat(fmtstr, "%d ", FMTSTRSIZE);
                break;
            default:
                break;
        }
    }
    strftime(timestr, TIMESTRSIZE, fmtstr, tm);
    fputs(timestr,fp);
    exit(0);
}


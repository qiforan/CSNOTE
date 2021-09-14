//
// Created by wch on 2020/12/8.
//

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static void int_handler(int s)
{
    printf("!");
}

int main(int argc, char **argv)
{
    int i, j;
    sigset_t set, oset, saveset;
    signal(SIGINT, int_handler);
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigprocmask(SIG_UNBLOCK, &set, &saveset);
    for (j = 0; j < 100; j++) {
        sigprocmask(SIG_BLOCK, &set, NULL);
        for (int i = 0; i < 5; i++) {
            write(1, "*", 1);
            sleep(1);
        }
        write(1, "\n", 1);
        sigprocmask(SIG_UNBLOCK, &set, NULL);
    }
    sigprocmask(SIG_SETMASK, &saveset, NULL);
    exit(0);
}

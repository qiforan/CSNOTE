//
// Created by wch on 2020/11/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char ** argv)
{
    pid_t pid;
    printf("[%d]:Begin\n", getpid());
    pid = fork();
    if(pid < 0){
        perror("fork");
        exit(1);
    }
    //child
    if(pid == 0){
        printf("[%d] Child is working\n", getpid());
    }
    //parent
    else{
        printf("[%d] Parent is working\n", getpid());
    }
    printf("[%d]:End\n",getpid());
}


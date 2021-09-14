//
// Created by wch on 2020/11/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>

int main(int argc, char ** argv)
{
    struct passwd *pw;
    if (argc < 2){
        perror("Usage:...\n");
        exit(1);
    }
    pw = getpwuid(atoi(argv[1]));
    printf("uid: %s name: %s\n", argv[1], pw->pw_name);
    // 不能读取到用户口令
    printf("passwd: %s\n", pw->pw_passwd);
    exit(0);

}

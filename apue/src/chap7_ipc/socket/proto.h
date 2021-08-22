//
// Created by wch on 2021/7/26.
//

#ifndef APUE_PROTO_H
#define APUE_PROTO_H
#include <stdint.h>

# define RCVPORT "1989"
#define NAMESIZE 11

struct msg_st
{
    uint8_t name[NAMESIZE];
    uint32_t math;
    uint32_t chinese;
}__attribute((packed));

#endif //APUE_PROTO_H

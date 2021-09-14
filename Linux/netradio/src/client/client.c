#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include "client.h"
#include "proto.h"

//  -M/--mgroup     assign broadcast address
//  -P/--port       assign port
//  -p/--player     assign player
//  -H/--help       display help
//  configuration: default, config files, environment variables, command line

struct client_conf_st client_conf = {
        .rcvport = DEFAULT_RCVPORT,
        .mgroup = DEFAULT_MGROUP,
        .player_cmd = DEFAULT_PLAYERCMD
};

int main(int argc, char * argv[])
{
    // getopt_long
    int index = 0;
    int c;
    struct option argarr[] = {
            {"port", required_argument, NULL, 'P'},
            {"mgroup", required_argument, NULL, 'M'},
            {"player",required_argument,NULL,'p'},
            {"help",no_argument,NULL,"H"},
            {NULL,0,NULL,0}
    };
    while (1){
        c = getopt_long(argc,argv, "P:M:p:H",argarr, &index);
        if(c < 0)
            break;
        switch (c) {
            case 'P':
                client_conf.rcvport = optarg;
                break;
            case 'M':
                client_conf.mgroup = optarg;
                break;
            case 'p':
                client_conf.player_cmd = optarg;
                break;
            case 'H':
                printf("help\n");
                exit(0);
                break;
            default:
                abort();
                break;
        }
    }
    // socket
    int sd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sd < 0){
        perror("socket()");
        exit(1);
    }
    struct ip_mreqn mreq;
    struct sockaddr_in laddr;
    inet_pton(AF_INET, client_conf.mgroup, &mreq.imr_multiaddr);
    inet_pton(AF_INET, "0.0.0.0", &mreq.imr_address);
    mreq.imr_ifindex = if_nametoindex("lo1");
    int val = 1;
    int fail = setsockopt(sd, IPPROTO_IP, IP_MULTICAST_LOOP, &val,sizeof(val));
    if(!fail){
        perror("setsockopt()");
        exit(1);
    }
    fail = bind(sd, (void*)&laddr,sizeof(laddr));
    if(fail < 0){
        perror("bin()");
        exit(1);
    }


    // pipe
    // fork
    exit(0);
}
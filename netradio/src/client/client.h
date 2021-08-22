#ifndef NETRADIO_CLIENT_H
#define NETRADIO_CLIENT_H

#define DEFAULT_PLAYERCMD "/opt/homebrew/bin/mpg123 > /dev/null"

struct client_conf_st{
    char *rcvport;
    char *mgroup;
    char *player_cmd;
};

#endif
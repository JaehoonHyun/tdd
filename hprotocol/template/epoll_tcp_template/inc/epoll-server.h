#ifndef EPOLL_SERVER_H_
#define EPOLL_SERVER_H_

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#define MAXFDS 16 * 1024


typedef struct {

    int who;
    int what;
    int when;
    int why;
    int where;
    int how;
    
} My6W1H;

void run_server(int argc, char **argv);

#endif
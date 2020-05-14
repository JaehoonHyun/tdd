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

//max throughput : 16K
#define MAXFDS 16 * 1024

typedef enum
{
    INITIAL_ACK,
    WAIT_FOR_MSG,
    IN_MSG
} ProcessingState;

#define SENDBUF_SIZE 1024

typedef struct
{
    ProcessingState state;
    uint8_t sendbuf[SENDBUF_SIZE];
    int sendbuf_end;
    int sendptr;
} peer_state_t;

typedef struct
{
    bool want_read;
    bool want_write;

} fd_status_t;

fd_status_t on_peer_connected(int sockfd, const struct sockaddr_in *peer_addr, socklen_t peer_addr_len);
fd_status_t on_peer_ready_recv(int sockfd);
fd_status_t on_peer_ready_send(int sockfd);

#endif
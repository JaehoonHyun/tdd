#ifndef UTILS_H
#define UTILS_H

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#define H_MALLOC(type) (type *)malloc(sizeof(type{}))

void fatalf(const char* fmt, ...);

int make_stream_socket(int portnum);

int set_socket_non_blocking(int sockfd);

int add_to_epoll_fd(int p_epoll_fd, int p_listen_fd, void *p_data);

#endif
// Utility functions for socket servers in C.
//
// Eli Bendersky [http://eli.thegreenplace.net]
// This code is in the public domain.
#include "inc/utils.h"

#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/types.h>
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <netdb.h>

#define N_BACKLOG 64

void fatalf(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);
  fprintf(stderr, "\n");
  exit(EXIT_FAILURE);
}


int make_stream_socket(int portnum) {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    return -1;
  }

  // This helps avoid spurious EADDRINUSE when the previous instance of this
  // server died.
  int opt = 1;
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
    return -2;
  }

  struct sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portnum);

  if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
    return -3;
  }

  //https://meetup.toast.com/posts/54
  if (listen(sockfd, N_BACKLOG) < 0) {
    return -4;
  }

  return sockfd;
}

int set_socket_non_blocking(int sockfd) {
  int flags = fcntl(sockfd, F_GETFL, 0);
  if (flags == -1) {
    return -1;
  }

  //SOCKET 얻는 함수에서 open함수는 못사용하므로, fcntl을 이용해 NON_BLOCKING모드로 연다.
  if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1) {
    return -2;
  }

  return sockfd;
}

int add_to_epoll_fd(int p_epoll_fd, int p_listen_fd, void *p_data) {

  struct epoll_event accept_event;
	accept_event.data.ptr = p_data;
	accept_event.events = EPOLLIN;

	//listener socket을 epollfd에 등록한다
	if (epoll_ctl(p_epoll_fd, EPOLL_CTL_ADD, p_listen_fd, &accept_event) < 0)
	{
    return -1;
	}

  return 0;
}


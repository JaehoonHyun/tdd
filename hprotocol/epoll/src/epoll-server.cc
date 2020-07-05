#include <pthread.h>

#include "inc/epoll-server.h"
#include "inc/utils.h"

#define BUFSIZE 1024 * 1024
char recvbuf[BUFSIZE];

#define THREAD_POOL_SIZE 2
typedef struct {
  pthread_t t;
  int status;
  void *data;
  void *(*func)(void *);
} ThreadPool;

enum {
  eTHREAD_IDLE = 0,
  eTHREAD_RUNNING,
};

ThreadPool thread_pool[THREAD_POOL_SIZE];

void *t_func(void *p_thp) {

  ThreadPool *thp = (ThreadPool *)p_thp;

  thp->status = eTHREAD_RUNNING;
  thp->func(thp->data);
  thp->status = eTHREAD_IDLE;
}

int execute_pthread(void *(p_func)(void *), void *p_data) {
  int n = -1;
  for(int i = 0; i < THREAD_POOL_SIZE; i++) {
    if(thread_pool[i].status == eTHREAD_IDLE) {
      thread_pool[i].data = p_data;
      thread_pool[i].func = p_func;
      pthread_create(&thread_pool[i].t, NULL, t_func, &thread_pool[i]);
      n = i;
      break;
    }
  }

  return n;
}


void* t_function(void *p_bzz) {

  Bzz *bzz = (Bzz *)p_bzz;


  //blocking
  {
    sleep(3);
  }

  //copy
  {
    int n;

    strncpy(bzz->sendbuf,bzz->recvbuf, bzz->recvbufsize);
    bzz->sendbufsize = bzz->recvbufsize;
  }

  //just send to 
  {
    int n;
    int server_fd = bzz->server_fd;
    char *buf = bzz->sendbuf;
    size_t bufsize = bzz->sendbufsize;
    struct sockaddr_in *client_addr = &bzz->sockaddr;
    socklen_t client_len = sizeof(*client_addr);
    n = sendto(server_fd, buf, bufsize, 0, (struct sockaddr *)client_addr, client_len);

    printf("[SEND]:%d, %s\n", n, buf);
  }

  {
    free(bzz);
  }


}

void run_server(int argc, char **argv)
{
	int portnum = 9091;
	if (argc >= 2)
	{
		portnum = atoi(argv[1]);
	}
	printf("serving on port : %d\n", portnum);

  //make listen sock
	// int server_fd = set_socket_non_blocking(make_stream_socket(portnum));
  int server_fd = set_socket_non_blocking(make_datagram_socket(portnum));
  assert(server_fd >= 0);

  // create epoll
  int epoll_fd = epoll_create1(0);
  assert(epoll_fd >= 0);

  //server_fd add to epoll_fd repo
  assert(add_to_epoll_fd(epoll_fd, server_fd, (void *)server_fd) >= 0);

	//이벤트가 뜨면 담을 event 객체들 생성
	struct epoll_event *events = (struct epoll_event *)calloc(MAXFDS, sizeof(struct epoll_event));
  assert(events != NULL);

  printf("[START]\n");
	while (1)
	{
		int nready = epoll_wait(epoll_fd, events, MAXFDS, -1);
		for (int i = 0; i < nready; i++) 
		{

      if (events[i].events & EPOLLIN)
      {
        //if recv buffer have some bytes, epoll in event occured
        printf("[EPOLLIN]\n");

        Bzz *bzz = H_MALLOC(Bzz);
        bzz->server_fd = server_fd;
        int n;
        socklen_t client_len = sizeof(bzz->sockaddr);
        n = recvfrom(server_fd, recvbuf, BUFSIZE, 0, (struct sockaddr *) &bzz->sockaddr, &client_len);
        strncpy(bzz->recvbuf, recvbuf, n);
        bzz->recvbufsize = n;

        //toss to thread pool. and processing
        int thread_id;
        thread_id = execute_pthread(t_function, (void *)bzz);
        printf("[THREAD ID]: %d\n", thread_id);


      }
      else if (events[i].events & EPOLLOUT)
      {
        //if send buffer have not anymore, epoll in event occured
        printf("[EPOLLOUT]\n");

      }
		}
	}
}

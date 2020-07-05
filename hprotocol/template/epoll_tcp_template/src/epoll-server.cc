#include "inc/epoll-server.h"
#include "inc/utils.h"

void run_server(int argc, char **argv)
{
	int portnum = 9091;
	if (argc >= 3)
	{
		portnum = atoi(argv[2]);
	}
	printf("serving on port : %d\n", portnum);

  //make listen sock
	int listen_fd = set_socket_non_blocking(make_stream_socket(portnum));

  // create epoll
  int epoll_fd = epoll_create1(0);
  assert(epoll_fd >= 0);

  //listen_fd add to epoll_fd repo
  assert(add_to_epoll_fd(epoll_fd, listen_fd, (void *)listen_fd) >= 0);

	//이벤트가 뜨면 담을 event 객체들 생성
	struct epoll_event *events = (struct epoll_event *)calloc(MAXFDS, sizeof(struct epoll_event));
  assert(events != NULL);

	while (1)
	{
		int nready = epoll_wait(epoll_fd, events, MAXFDS, -1);
		for (int i = 0; i < nready; i++) 
		{
      //connect
			if (events[i].data.fd == listen_fd)
			{
				struct sockaddr_in peer_addr;
				socklen_t peer_addr_len = sizeof(peer_addr);
				int client_fd = accept(listen_fd, (struct sockaddr *)&peer_addr, &peer_addr_len);
				if (client_fd < 0)
				{
					if (errno == EAGAIN || errno == EWOULDBLOCK)
						fatalf("accept returned EAGAIN or EWOULDBLOCK\n");
					else
						fatalf("accept");
				}
				else
				{
          assert(add_to_epoll_fd(epoll_fd, set_socket_non_blocking(client_fd), H_MALLOC(My6W1H)) >= 0);
				}
			}
			else
			{
				if (events[i].events & EPOLLIN)
				{
					//if recv buffer have some bytes, epoll in event occured
					printf("[EPOLLIN]\n");
				}
				else if (events[i].events & EPOLLOUT)
				{
          //if send buffer have not anymore, epoll in event occured
					printf("[EPOLLOUT]\n");
				}
			}
		}
	}
}
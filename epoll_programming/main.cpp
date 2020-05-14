#include <stdio.h>

#include <gtest/gtest.h>

#include "inc/epoll-server.h"
#include "inc/epoll-client.h"
#include "inc/utils.h"


/**
 * 
 * TODO : 
 * 1. nonblocking 모드로 동작하므로 그에 따른 recv/send를 구현해야함
 * 2. peerstate 객체에 recv한 내용과 send한 내용을 알아야함
 * 3. server-client간의 통신중 처음에 몇개를 보낼지 알아야 nonblocking으로 구현가능
 * 4. 여기에 distruptor를 붙여서 TPS 측정
 * 5. serialize, deserialize를 구현하여 MQ 완성
 */

static int my_add(int a, int b)
{
	return a + b;
}

TEST(tdd_gtest, basic_gtest)
{
	ASSERT_EQ(2, my_add(1, 1));
}

void run_server(int argc, char **argv)
{

	int portnum = 9091;

	if (argc >= 3)
	{
		portnum = atoi(argv[2]);
	}

	printf("serving on port : %d\n", portnum);

	int listener_sockfd = listen_inet_socket(portnum);
	make_socket_non_blocking(listener_sockfd);

	int epollfd = epoll_create1(0);
	assert(epollfd >= 0);

	struct epoll_event accept_event;
	accept_event.data.fd = listener_sockfd;
	accept_event.events = EPOLLIN;

	//listener socket을 epollfd에 등록한다
	if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listener_sockfd, &accept_event) < 0)
	{
		perror_die("epoll ctl EPOLL_CTL_ADD");
	}

	//이벤트가 뜨면 담을 event 객체들 생성
	struct epoll_event *events = (struct epoll_event *)calloc(MAXFDS, sizeof(struct epoll_event));
	if (events == NULL)
	{
		die("Unable to allocate memory for epoll_events");
	}

	while (1)
	{
		int nready = epoll_wait(epollfd, events, MAXFDS, -1);

		for (int i = 0; i < nready; i++)
		{

			if (events[i].events & EPOLLERR)
			{
				perror_die("epoll_wait returned EPOLLERR");
			}

			if (events[i].data.fd == listener_sockfd)
			{
				struct sockaddr_in peer_addr;
				socklen_t peer_addr_len = sizeof(peer_addr);
				int newsockfd = accept(listener_sockfd, (struct sockaddr *)&peer_addr, &peer_addr_len);

				if (newsockfd < 0)
				{
					if (errno == EAGAIN || errno == EWOULDBLOCK)
					{
						printf("accept returned EAGAIN or EWOULDBLOCK\n");
					}
					else
					{
						perror_die("accept");
					}
				}
				else
				{
					make_socket_non_blocking(newsockfd);
					if (newsockfd >= MAXFDS)
					{
						die("socket fd (%d) >= MAXFDS (%d)", newsockfd, MAXFDS);
					}

					fd_status_t status = on_peer_connected(newsockfd, &peer_addr, peer_addr_len);
					struct epoll_event event = {0};

					event.data.fd = newsockfd;

					//NON, R
					if (status.want_read)
					{
						event.events |= EPOLLIN;
					}

					//NON, R, W,RW
					if (status.want_write)
					{
						event.events |= EPOLLOUT;
					}

					if (epoll_ctl(epollfd, EPOLL_CTL_ADD, newsockfd, &event) < 0)
					{
						perror_die("epoll_ctl EPOLL_CTL_ADD");
					}
				}
			}
			else
			{
				if (events[i].events & EPOLLIN)
				{

					//read //recv
					printf("[EPOLLIN]\n");

					int fd = events[i].data.fd;
					fd_status_t status = on_peer_ready_recv(fd);
					struct epoll_event event = {0};
					event.data.fd = fd;

					//NON, R
					if (status.want_read)
					{
						event.events |= EPOLLIN;
					}

					//NON, R, W,RW
					if (status.want_write)
					{
						event.events |= EPOLLOUT;
					}

					//NON
					if (event.events == 0)
					{
						printf("[EPOLLIN]:socket %d closing \n", fd);
						if (epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, NULL) < 0)
						{
							perror_die("epoll_ctl EPOLL_CTL_DEL");
						}
						close(fd);
					}
					else if (epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &event) < 0)
					{
						perror_die("epoll_ctl EPOLL_CTL_MOD");
					}
				}
				else if (events[i].events & EPOLLOUT)
				{
					//write //send
					printf("[EPOLLOUT]\n");
					int fd = events[i].data.fd;
					fd_status_t status = on_peer_ready_send(fd);

					//이 event를 다시 epollfd에 넣는다.
					struct epoll_event event = {0};
					event.data.fd = fd;

					//NON, R
					if (status.want_read)
					{
						event.events |= EPOLLIN;
					}

					//NON, R, W,RW
					if (status.want_write)
					{
						event.events |= EPOLLOUT;
					}

					//NON
					if (event.events == 0)
					{
						printf("[EPOLLOUT]:socket %d closing\n", fd);
						if (epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, NULL) < 0)
						{
							perror_die("epoll_ctl EPOLL_CTL_DEL");
						}
						close(fd);
					}
					else if (epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &event) < 0)
					{
						perror_die("epoll_ctl EPOLL_CTL_MOD");
					}
				}
			}
		}
	}
}

void run_client(int argc, char **argv)
{
	entrypoint_client(argc, argv);
}

int main(int argc, char **argv)
{

	setvbuf(stdout, NULL, _IONBF, 0);

	if (strcmp(argv[1], "-client") == 0)
	{
		run_client(argc, argv);
	}
	else if (strcmp(argv[1], "-server") == 0)
	{
		run_server(argc, argv);
	}

	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
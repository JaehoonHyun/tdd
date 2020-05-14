#include "inc/epoll-server.h"
#include "inc/utils.h"


peer_state_t global_state[MAXFDS];

const fd_status_t fd_status_R = {.want_read = true, .want_write = false};
const fd_status_t fd_status_W = {.want_read = false, .want_write = true};
const fd_status_t fd_status_RW = {.want_read = true, .want_write = true};
const fd_status_t fd_status_NORW = {.want_read = false, .want_write = false};

fd_status_t on_peer_connected(int sockfd, const struct sockaddr_in *peer_addr, socklen_t peer_addr_len)
{
    assert(sockfd < MAXFDS);
    report_peer_connected(peer_addr, peer_addr_len);

    //accept 함수 이후 초기화
    peer_state_t *peerstate = &global_state[sockfd];
    peerstate->state = INITIAL_ACK;
    peerstate->sendbuf[0] = '*';
    peerstate->sendptr = 0;
    peerstate->sendbuf_end = 1;

    //처음에는 쓰기를 원한다.
    // return fd_status_W;

    //처음에는 읽기를 원한다
    return fd_status_R;
}

//EPOLLIN 이면 이 함수가 호출됨
//EPOLLIN은 read이므로 recv
fd_status_t on_peer_ready_recv(int sockfd)
{
    assert(sockfd < MAXFDS);

    // peer_state_t *peerstate = &global_state[sockfd];

    // if (peerstate->state == INITIAL_ACK || peerstate->sendptr < peerstate->sendbuf_end)
    // {
    //     printf("initial_ack\n");
    //     return fd_status_W;
    // }

    uint8_t buf[1024];
    int nbytes = recv(sockfd, buf, sizeof buf, 0);
    printf("recv : %s\n", buf);

    // if (nbytes == 0)
    // {
    //     return fd_status_NORW;
    // }
    // else if (nbytes < 0)
    // {

    //     if (errno == EAGAIN || errno == EWOULDBLOCK)
    //     {
    //         return fd_status_R;
    //     }
    //     else
    //     {
    //         perror_die("recv");
    //     }
    // }

    // bool ready_to_send = false;
    bool ready_to_send = true;

    for(int i = 0 ; i < nbytes; i++){
        
    }

    // for (int i = 0; i < nbytes; i++)
    // {

    //     //특수문자가 하나라도 없으면, 정상 메세지이고, send할 준비가 되었다.
    //     switch (peerstate->state)
    //     {
    //     case INITIAL_ACK:
    //         assert(0 && "can't reach here");
    //         break;
    //     case WAIT_FOR_MSG:
    //         if (buf[i] == '^')
    //             peerstate->state = IN_MSG;
    //         break;
    //     case IN_MSG:
    //         if (buf[i] == '$')
    //         {
    //             peerstate->state = WAIT_FOR_MSG;
    //         }
    //         else
    //         {
    //             assert(peerstate->sendbuf_end < SENDBUF_SIZE);
    //             peerstate->sendbuf[peerstate->sendbuf_end++] = buf[i] + 1;
    //             ready_to_send = true;
    //         }
    //         break;
    //     }
    // }

    // return (fd_status_t) { .want_read = !ready_to_send, .want_write = ready_to_send };
    return (fd_status_t) { .want_read = false, .want_write = true };
}

//EPOLLOUT이면 이 함수가 호출됨
//EPOLLOUT은 write이므로 send
fd_status_t on_peer_ready_send(int sockfd)
{
    assert(sockfd < MAXFDS);
    // peer_state_t *peerstate = &global_state[sockfd];

    // if (peerstate->sendptr >= peerstate->sendbuf_end)
    // {
    //     return fd_status_RW;
    // }

    // int sendlen = peerstate->sendbuf_end - peerstate->sendptr;
    // int nsent = send(sockfd, &peerstate->sendbuf[peerstate->sendptr], sendlen, 0);

    int sendlen = strlen("helloWorld") + 1;
    int nsent = send(sockfd, "helloWorld", sendlen, 0);
    if (nsent == -1)
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
        {
            return fd_status_W;
        }
        else
        {
            perror_die("send");
        }
    }

    // if (nsent < sendlen)
    // {
    //     peerstate->sendptr += nsent;
    //     return fd_status_W;
    // }
    // else
    // {
    //     peerstate->sendptr = 0;
    //     peerstate->sendbuf_end = 0;

    //     if (peerstate->state == INITIAL_ACK)
    //     {
    //         peerstate->state = WAIT_FOR_MSG;
    //     }

    //     return fd_status_R;
    // }

    return fd_status_NORW;
}

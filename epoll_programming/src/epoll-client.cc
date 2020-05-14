#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <assert.h>

#define BUF_LEN 128

void entrypoint_client(int argc, char *argv[]){

    int sockfd, n;
    const char *haddr = "127.0.0.1";
    int portnum = 9092;
    struct sockaddr_in server_addr;

    if(argc == 3){
        haddr = argv[2];
    }else if(argc == 4){
        portnum = atoi(argv[3]);
    }

    if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0){
        printf("cannot create socket\n");
        exit(0);
    }

    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(haddr);
    server_addr.sin_port = htons(portnum);

    if(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr))){
        printf("cannot connect\n");
        exit(0);
    }

    const char *stream;
    char buf[256];

    stream = "helloWorld";
    send(sockfd, stream, strlen(stream) + 1, 0);
    n = recv(sockfd, buf, 256, 0);
    printf("recv : %s[%d]\n", buf, n);
    


    close(sockfd);

}
#include <sys/socket.h>

#include <unistd.h>

#include <stdio.h>

#include <arpa/inet.h>

#include <netinet/ip.h>

#include <strings.h>

int main(int argc, const char **argv)
{

    /*
     * create a raw socket
     */
    int sd = socket(PF_INET, SOCK_RAW, IPPROTO_UDP);
    if (sd < 0)
    {
        perror("socket() error");
        return -1;
    }

    char recvPacket[1024] = {
        0,
    };

    int pkt_size = 0;
    if ((pkt_size = recv(sd, recvPacket, 1024, 0)) < 0)
    {
        perror("recvfrom() failed");
        return -1;
    }
    printf("read succeeded");
    printf("pkt_size = %d\n", pkt_size);

    struct iphdr *iphdr = (struct iphdr *)&recvPacket[0];
    printf("iphdr.ihl = %d\n", iphdr->ihl);
    printf("iphdr.version = %d\n", iphdr->version);
    printf("iphdr.tos = %d\n", iphdr->tos);
    printf("iphdr.tot_len = %d\n", htons(iphdr->tot_len));
    printf("iphdr.frag_off = %d\n", iphdr->frag_off);
    printf("iphdr.ttl = %d\n", iphdr->ttl);
    printf("iphdr.protocol = %d\n", iphdr->protocol);

    return 0;
}

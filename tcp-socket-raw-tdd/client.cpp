#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <math.h>

u_int16_t get_checksum(u_int16_t *buf, int nwords)

{

    u_int32_t sum;
    for (sum = 0; nwords > 0; nwords--)
        sum += *buf++;
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    return (u_int16_t)(~sum);
}

//sudo 권한 필요
int main(int argc, const char **argv)
{
    /*
     * create a raw socket
     */
    int sd = socket(PF_INET, SOCK_RAW, IPPROTO_UDP /* not used */);
    if (sd < 0)
    {
        perror("socket() error");
        return -1;
    }

    int turn_on = 1;
    int turn_off = 0;
    /*
     * I will manipulate IP header myself
     */
    if (setsockopt(sd, IPPROTO_IP, IP_HDRINCL, &turn_on, sizeof(turn_on)) < 0)
    {
        perror("setsockopt() error");
        return -1;
    }

    struct sockaddr_in dst_addr;
    dst_addr.sin_family = AF_INET;
    dst_addr.sin_port = 0;
    dst_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    struct iphdr iphdr;
    iphdr.ihl = 5;
    iphdr.version = 4;
    iphdr.tos = 0;
    iphdr.tot_len = htons(sizeof(struct iphdr));
    iphdr.id = htons(rand() % 65535);
    iphdr.frag_off = 0;
    iphdr.ttl = 64;
    iphdr.protocol = 145;
    iphdr.saddr = inet_addr("127.0.0.2");
    iphdr.daddr = inet_addr("127.0.0.1");
    // iphdr.check = get_checksum((u_int16_t*)&iphdr, sizeof(struct iphdr));
    // IP_HDRINCL인 경우에는 checksum 계산 필요 없음. 하위 layer에서 시행됨.

    if (sendto(sd, &iphdr, sizeof(iphdr), 0, (struct sockaddr *)&dst_addr, sizeof(dst_addr)) < 0)
    {
        perror("sendto() error");
        return -1;
    }

    return 0;
}

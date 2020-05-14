#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
 
int main()
{
//    char *name = "www.google.co.kr";
    char *name="64.233.189.94";
    struct hostent *host;
 
    host = gethostbyname(name);
 
    printf("%s\n",host->h_name);
 
    for(int i=0; host->h_aliases[i] != NULL; i++)
        printf("aliases : %s\n",host->h_aliases[i]);
 
    for(int i=0; host->h_addr_list[i] != NULL; i++)
        printf("addrList : %s\n", inet_ntoa(*(struct in_addr*)host->h_addr_list[i]));
 
    return 0;
 
}
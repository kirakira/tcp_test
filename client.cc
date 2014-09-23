#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <signal.h>
#include <string>
#include <cstdlib>

using namespace std;

void signal_handler(int) {}

int main(int argc, char *argv[])
{
    signal(SIGPIPE, signal_handler);
    int sockfd = 0, n = 0;
    char recvBuff[1024];
    struct sockaddr_in serv_addr; 

    memset(recvBuff, '0',sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    int on;
    setsockopt (sockfd, SOL_TCP, TCP_NODELAY, &on, sizeof (on));

    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8000); 

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 

    if( connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\n Error : Connect Failed \n");
        return 1;
    } 

    bool fail = false;
    char buffer[1025];
    for (int i = 0; !fail && i < 100; ++i) {
        int value = rand();
        if (sizeof(value) != write(sockfd, &value, sizeof(value)))
            fail = true;

        if (sizeof(value) != read(sockfd, &value, sizeof(value)))
            fail = true;
        if (value != read(sockfd, buffer, value))
            fail = true;
    }

    if(n < 0 || fail)
    {
        printf("\n Read error \n");
    } 

    return 0;
}

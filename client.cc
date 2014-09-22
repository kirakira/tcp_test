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

bool WriteString(int fd, const string& str) {
    int len = str.length();
    if (write(fd, (const char*) &len, sizeof(len)) <= 0)
        return false;
    if (len > 0 && write(fd, str.c_str(), len) <= 0)
        return false;
    return true;
}

bool ReadString(int fd, string* str) {
    int len;
    if (read(fd, (char*) &len, sizeof(len)) <= 0)
        return false;
    char* buffer = new char[len];
    if (len > 0 && read(fd, buffer, len) <= 0)
        return false;
    *str = string(buffer, len);
    delete[] buffer;
    return true;
}

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

    char buffer[1025];
    for (int i = 0; i < 100; ++i) {
        /*
        int value = rand();
        if (sizeof(value) != write(sockfd, (const char*) &value, sizeof(value)))
            break;
        value = rand();
        if (sizeof(value) != write(sockfd, (const char*) &value, sizeof(value)))
            break;
        if (sizeof(value) != read(sockfd, (char*) &value, sizeof(value)))
            break;
        if (sizeof(value) != read(sockfd, (char*) &value, sizeof(value)))
            break;*/
        /*
        int value = rand();
        if (sizeof(value) != WriteN(sockfd, (const char*) &value, sizeof(value)))
            break;
        if (sizeof(value) != WriteN(sockfd, (const char*) &value, sizeof(value)))
            break;
        if (sizeof(value) != ReadN(sockfd, (char*) &value, sizeof(value)))
            break;
        if (sizeof(value) != ReadN(sockfd, (char*) &value, sizeof(value)))
            break;*/
        /*
        string str;
        if (!WriteString(sockfd, "aaaa"))
            break;
        if (!ReadString(sockfd, &str))
            break;*/
        /*
        int value = 4;
        if (4 != write(sockfd, (const char*) &value, sizeof(value)))
            break;
        if (4 != write(sockfd, "aaaa", 4))
            break;*/
        if (!WriteString(sockfd, "aaaa"))
            break;
        /*
        if (4 != read(sockfd, (char*) &value, sizeof(value)))
            break;
        if (4 != read(sockfd, buffer, value))
            break;*/
        string str;
        if (!ReadString(sockfd, &str))
            break;
        /*
        Message request(random_string(4), random_string(4));
        request.Serialize(sockfd);
        Message response;
        response.Deserialize(sockfd);*/
    }

    if(n < 0)
    {
        printf("\n Read error \n");
    } 

    return 0;
}

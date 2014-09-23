#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#include <string>
#include <map>

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

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr; 

    char buffer[1025];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    int on;
    setsockopt (listenfd, SOL_TCP, TCP_NODELAY, &on, sizeof (on));

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(8000); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10); 

    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
        setsockopt (connfd, SOL_TCP, TCP_NODELAY, &on, sizeof (on));

        map<string, string> table;
        while (true) {
            int value;
            string str;
            ReadString(connfd, &str);
            str = "aaaa";
            value = str.length();
                int len = str.length();
                write(connfd, (const char*) &len, sizeof(len));
                if (value > 0)
                    write(connfd, str.c_str(), value);
        }

        close(connfd);
        sleep(1);
    }
}

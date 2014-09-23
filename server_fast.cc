#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#include <string>
#include <map>
#include <signal.h>

using namespace std;

void signal_handler(int) {}

int main(int argc, char *argv[]) {
    signal(SIGPIPE, signal_handler);

    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr; 

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    int on;
    setsockopt(listenfd, SOL_TCP, TCP_NODELAY, &on, sizeof (on));

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(8000); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    listen(listenfd, 10); 

    connfd = accept(listenfd, (struct sockaddr*) NULL, NULL); 

    //map<string, string> unused;
    while (true) {
        int value;
        if (read(connfd, &value, sizeof(value)) <= 0)
            break;

        string str;
        str = "aaaa";
        value = str.length();
        write(connfd, (const char*) &value, sizeof(value));
        if (value > 0)
            write(connfd, str.c_str(), value);
    }

    close(connfd);

    close(listenfd);
    return 0;
}

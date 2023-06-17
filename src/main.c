#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
    int domain, type, protocol;
    domain = AF_INET;
    type = SOCK_STREAM;
    protocol = 0;
    int sockfd = socket(domain, type, protocol);

    const int PORT = 8080;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr*)&address, sizeof(address));

    listen(sockfd, 3);

    int new_socket;
    char buffer[1024] = { 0 };
    int valread;
    while(1){
        new_socket = accept(sockfd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        valread = read(new_socket, buffer, 1024);
        printf("%s\n", buffer);
        char* response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 10\r\n\r\npedramcode";
        send(new_socket, response, strlen(response), 0);
    }
    return 0;
}

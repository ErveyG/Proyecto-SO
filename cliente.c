//Libraries for use sockets
#include     <unistd.h>
#include     <netinet/in.h>
#include     <arpa/inet.h>
#include     <sys/types.h>
#include     <sys/socket.h>

//Standar Libraries
#include     <stdlib.h>
#include     <string.h>
#include     <stdio.h>

//Constants
#define PORT 2001
#define IP "10.0.2.15"
#define SIZE 255

int main(){
    int serverfd, tam , numBytes;
    char buf[SIZE];
    struct sockaddr_in server;

    //Server direcction
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    inet_aton(IP,&(server.sin_addr));
    memset(&(server.sin_zero),'\0',8);

    serverfd = socket(AF_INET, SOCK_STREAM, 0);

    tam = sizeof(struct sockaddr);

    connect(serverfd, (struct sockaddr*)&server, tam);

    numBytes = recv(serverfd, buf, SIZE - 1, 0);

    buf[numBytes] = '\0';

    printf("%d bytes recibidos\n", numBytes);
    printf("Recibido: %s\n", buf);
    close(serverfd);
}
//Libraries for use sockets
#include     <unistd.h>
#include     <netinet/in.h>
#include     <arpa/inet.h>
#include     <sys/types.h>
#include     <sys/socket.h>

//Standar Libraries
#include     <stdlib.h>
#include     <string.h>

//Constants
#define PORT 2001


int main() {

    int serverfd, clientfd , tam;
    struct sockaddr_in server;
    
    //Server Settings
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr  = INADDR_ANY;
    memset(&(server.sin_zero),0, 8);

    //Creation socket
    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    tam = sizeof(struct sockaddr);

    //Use bind function
    bind(serverfd, (struct sockaddr*)&server,tam);

    //Start listening
    listen(serverfd,5);

    //Functionality to server
    while(1) {
        clientfd = accept(serverfd, (struct sockaddr*)&server,&tam);
        if(fork() == 0) {
            close(serverfd);
            send(clientfd,"Bienvenido al nuestro restaurante\n",50,0);
            close(clientfd);
            exit(0);
        }else{
            close(clientfd);
        }
    }

}
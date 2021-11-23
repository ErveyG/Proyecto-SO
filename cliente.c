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
#define IP "127.0.0.1"
#define SIZE 255
#define MENU_1 "1.Hacer recervacion\n2.Verificar cupo\n3.Salir\nSeleccione una respuesta: "

struct menu  {
    char *menu_1;
    char *menu_2;
};
int main(){

    //Define variables
    struct menu menu;
    int server_fd, tam, res;
    struct sockaddr_in server;
    char buffer[SIZE];
    // define the struct
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    inet_pton(AF_INET,IP,&(server.sin_addr));
    memset( &(server.sin_zero), '\0', 8 );

    //Create to socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd < 0){
        perror("socket");
        exit(1);
    }

    tam = sizeof(struct sockaddr_in);

    connect(server_fd,(struct sockaddr*)&server,tam);
    //Logical procesedure
    recv(server_fd, buffer,sizeof(buffer),0);
    printf("%s", buffer);
    printf("%s",MENU_1);

    scanf("%d",&res);
    send(server_fd,&res,sizeof(res),0);

    recv(server_fd,buffer,sizeof(buffer),0);
    printf("%s",buffer);
    close(server_fd);
}
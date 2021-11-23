//que realice la venta de comida, el restaurante contará con un cupo de 10 mesas de 5 lugares cada una y se podrá hacer reservación y si llega cliente que no cuente con reservación, se verificará el cupo. 
// El usuario solicitará al servidor compra de comida, para lo cual el servidor pedirá un nombre de usuario, junto con una prueba de validación captcha, una vez validado se le da acceso al servidor, el servidor mostrará menús de 3 posibles, menú vegetariano, de carnes y de mariscos, el usuario seleccionará el menú y el servidor mostrará 10 distintos platillos, el cual se podrá seleccionar entradas, plato fuerte y postre, una vez seleccionado el menú, el servidor pedirá si hay más menús que comprar y repetirá proceso, de acuerdo al menú o menús se realizará un pago de la comida el cual tendrá la opción de aplicar propina o sin propina. El usuario pedirá y dará la clave de su reservación si la realizó y si no intentará reservar, para el cual el sistema le indicará si procede la reservación si o no en base al cupo del restaurante.

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
#include     <stdbool.h>

#define PORT 2001
#define SIZE 1024

bool verificarCupo(bool mesas[]);
int asignarMesa(bool mesas[]);
void comprarComida(int client_fd,int res);


int main(){

    // char menus[][20] = {"carnes","vegetariano","mariscos"};
    int server_fd, client_fd, len_in = 0,len_out = 0,len,i,mesa;
    struct sockaddr_in server, client;
    char buffer_in[SIZE];
    char buffer_out[SIZE] = "Welcome\n";
    int res;
    bool mesas[10];

    for (i = 0; i < 10; i++)
    {
        mesas[i] = true;
    }
    

    // define the struct
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;
    memset( &(server.sin_zero), '\0', 8 );

    //Create to socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd < 0){
        perror("socket");
        exit(1);
    }

    len = sizeof(client);

    //Union IP address with bind
    if(bind(server_fd, (struct sockaddr *)&server,sizeof(server)) < 0){
        perror("bind");
        exit(1);
    }

    //Inicilization
    if(listen(server_fd,1) < 0){
        perror("listen");
        exit(1);
    }

    //Infinity loop
    while(1){
        client_fd = accept(server_fd, (struct sockaddr * )&client, &len);
        send(client_fd,"Welcome\n",sizeof("Welcome\n"),0);
        recv(client_fd,&res,sizeof(res),0);
        switch(res){
            case 1:
                if(verificarCupo(mesas)){
                    send(client_fd,"Reservado\n",sizeof("Reservado\n"),0);
                    int number = asignarMesa(mesas);
                    mesas[number] = false;
                    comprarComida(client_fd,res);
                }else{
                    send(client_fd,"Ya no hay cupo\n",sizeof("Ya no hay cupo\n"),0);
                }
                break;
            case 2:
            case 3:

            default:
                send(client_fd,"Hubo un error\n",sizeof("Hubo un error\n"),0);
        }
        printf("Fin\n");
        close(client_fd);
    }
    
}

bool verificarCupo(bool mesas[]){
    int i;
    for (i = 0; i < 10; i++)
    {
        if(mesas[i] == true){
            return true;
        }  
    }
    return false;
}

int asignarMesa(bool mesas[]){
    int i;
    for (i = 0; i < 10; i++)
    {
        if(mesas[i] == true){
            return i;
        }  
    }
}

void comprarComida(int client_fd,int res){
    printf("Comida\n");
    return;
}
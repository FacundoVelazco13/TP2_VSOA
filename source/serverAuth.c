#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define IP_ADDR_SIZE 16
#define USER_SIZE 32
#define PASS_SIZE 32
#define TOKEN_SIZE 32
#define OPT_SIZE 32
#define CONT_SIZE 1024
#define TOKEN_BUFFER_SIZE 1024

#define PORT 8080

struct credencial{
    char user[USER_SIZE];
    char pass[PASS_SIZE];
};
typedef struct credencial credencial;

int autenticarUsuario(credencial credencial);

int getToken();

int main(int argc, char *argv[]) {

    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };
    char* inv_user = "Usuario invalido";
  
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
  
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET,SO_REUSEADDR, &opt,sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
  
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*)&address,sizeof(address))< 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address,(socklen_t*)&addrlen))< 0) {
        perror("accept");
        exit(EXIT_FAILURE);
        }
        credencial credencial;
        valread = read(new_socket, &credencial, sizeof(credencial));
        
        if(autenticarUsuario(credencial)==1){
            char token[TOKEN_BUFFER_SIZE] = {" "};
            getToken(token); 
            send(new_socket,token, strlen(token), 0);
            printf("Token enviado \n");
        }else{
            send(new_socket, inv_user, strlen(inv_user), 0);
            printf("Usuario invalido \n");
        }
        close(new_socket);
    }
    shutdown(server_fd, SHUT_RDWR);
    return 0;   
}

int autenticarUsuario(credencial credencial){
    FILE *file = fopen("credenciales.txt", "r");
    
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }
    char user[USER_SIZE];
    char pass[PASS_SIZE];
    int valid_user = 0;
    
    fscanf(file, "%s %s", user, pass);
    while (fscanf(file, "%s %s", user, pass) == 2){
        if ((strcmp(user, credencial.user) == 0) && (strcmp(pass, credencial.pass) == 0)){
            valid_user = 1;
        }
    }
    
    fclose(file);

    return valid_user;
}
int getToken(char* token){
    FILE *file = fopen("token.txt", "r");
    
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    char buffer[TOKEN_BUFFER_SIZE] = {" "};

    fgets(buffer,sizeof(buffer), file);

    fclose(file);

    strcpy(token,buffer);

    return EXIT_SUCCESS;
}
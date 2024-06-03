#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define IP_ADDR_SIZE 16
#define USER_SIZE 32
#define PASS_SIZE 32
#define TOKEN_SIZE 32
#define OPT_SIZE 32
#define CONT_SIZE 1024
#define TOKEN_BUFFER_SIZE 1024

#define AUTH_CONS 1
#define WRITE_CONS 2

#define PORT 8080

struct credencial{
    char user[USER_SIZE];
    char pass[PASS_SIZE];
};
typedef struct credencial credencial;


int gestorParametros(int argc, char *argv[],char* ip_address,credencial* credencial,char* token,char* option,char* content);

int gestorConexion(char* ip_address);

void imprimirEjemplos();

int main(int argc, char *argv[]) {
    int opt;
    char ip_address[IP_ADDR_SIZE];
    credencial credencial;
    char token[TOKEN_SIZE];
    char option[OPT_SIZE];
    char content[CONT_SIZE];

    if((opt = gestorParametros(argc,argv,ip_address,&credencial,token,option,content)) == -1){
        imprimirEjemplos();
        return EXIT_FAILURE;
    }
    //Caso auth y recibimiento del token
    if(opt == AUTH_CONS){
        printf("Voy a usar sockets \n");
        int client_fd, valread;
        char token[TOKEN_BUFFER_SIZE];
        
        if((client_fd = gestorConexion(ip_address)) == -1){
            printf("Error de conexión \n");
            return EXIT_FAILURE;
        }
        send(client_fd, &credencial, sizeof(credencial), 0);
        printf("----Credencial enviada\n");
        valread = read(client_fd, token, TOKEN_BUFFER_SIZE);
        printf("TOKEN : ");
        printf("%s \n",token);
        close(client_fd);
    }
    //Caso utilizacion de procedimiento remoto
    else if (opt == WRITE_CONS){
        printf("Voy a usar rcp \n");
    }
    return EXIT_SUCCESS;
}

int gestorParametros(int argc, char *argv[],char* ip_address,credencial* credencial,char* token,char* option,char* content){
    int opt;
    int opta = 0,optu = 0,optp = 0,optt = 0,opto = 0,optc = 0;

    //Procesamiento de parametros.
    while ((opt = getopt(argc, argv, ":a:u:p:t:o:c:")) != -1) {
        switch (opt) {
            case 'a':
                opta = 1;
                strcpy(ip_address,optarg);
                printf("Opción a encontrada : %s \n",optarg);
                break;
            case 'u':
                optu = 1;
                strcpy(credencial->user,optarg);
                printf("Opción encontrada : %s \n",optarg);
                break;
            case 'p':
                optp = 1;
                strcpy(credencial->pass,optarg);
                printf("Opción encontrada : %s \n",optarg);
                break;
            case 't':
                optt = 1;
                strcpy(token,optarg);
                printf("Opción encontrada : %s \n",optarg);
                break;
            case 'o':
                opto = 1;
                strcpy(option,optarg);
                printf("Opción encontrada : %s \n",optarg);
                break;
            case 'c':
                optc = 1;
                strcpy(content,optarg);
                printf("Opción encontrada : %s \n",optarg);
                break;
            case '?':
                return -1;
                break;
        }
    }
    //Validacion de flags recibidas
    if(opta==1 & optu==1 & optp==1 & (optt==0 & opto==0 & optc==0)){
        return AUTH_CONS;
    }else if (opta==1 & optt==1 & opto==1 & optc==1 & (optu==0 & optp==0))
    {
        return WRITE_CONS;
    }else{
        return -1;
    }
}
int gestorConexion(char* ip_address){
    int status, valread, client_fd;
    struct sockaddr_in serv_addr;
    
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
  
    if (inet_pton(AF_INET, ip_address, &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if ((status = connect(client_fd, (struct sockaddr*)&serv_addr,sizeof(serv_addr))) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    return client_fd;
}
void imprimirEjemplos(){
    printf("Los parametros del programa deben tener la siguiente forma : \n");
    printf("clientSRPC -a <ip contenedor servidor> -u <usuario> -p <contraseña> \n");
    printf("clientSRPC -a <ip contenedor servidor> -t <token> -o <opción> -c <contenido> \n");
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define IP_ADDR_SIZE 16
#define USER_SIZE 32
#define PASS_SIZE 32
#define TOKEN_SIZE 32
#define OPT_SIZE 32
#define CONT_SIZE 1024

int gestorParametros(int argc, char *argv[],char* ip_address,char* user,char* pass,char* token,char* option,char* content);

void imprimirEjemplos();

int main(int argc, char *argv[]) {
    int opt;

    char ip_address[IP_ADDR_SIZE];
    char user[USER_SIZE];
    char pass[PASS_SIZE];
    char token[TOKEN_SIZE];
    char option[OPT_SIZE];
    char content[CONT_SIZE];


    if(opt = gestorParametros(argc,argv,ip_address,user,pass,token,option,content) == EXIT_FAILURE){
        imprimirEjemplos();
        return EXIT_FAILURE;
    }
}

int gestorParametros(int argc, char *argv[],char* ip_address,char* user,char* pass,char* token,char* option,char* content){
    int opt;
    int opta = 0,optu = 0,optp = 0,optt = 0,opto = 0,optc = 0;

    //Validacion de flags
    while ((opt = getopt(argc, argv, ":a:u:p:t:o:c:")) != -1) {
        switch (opt) {
            case 'a':
                opta = 1;
                printf("Opción a encontrada : %s \n",optarg);
                printf("len : %d \n",strlen(optarg));
                break;
            case 'u':
                optu = 1;
                printf("Opción encontrada : %s \n",optarg);
                break;
            case 'p':
                optp = 1;
                printf("Opción encontrada : %s \n",optarg);
                break;
            case 't':
                optt = 1;
                printf("Opción encontrada : %s \n",optarg);
                break;
            case 'o':
                opto = 1;
                printf("Opción encontrada : %s \n",optarg);
                break;
            case 'c':
                optc = 1;
                printf("Opción encontrada : %c \n",opt);
                printf("Opción encontrada : %s \n",optarg);
                break;
            case '?':
                return EXIT_FAILURE;
                break;
        }
    }
    //Validar parametros recibidos.
    if(opta==1 & ((optu==1 & optp==1) | (optt==1&opto==1&optc==1))){
        return EXIT_SUCCESS;
    }else{
        return EXIT_FAILURE;
    }


}
void imprimirEjemplos(){
    printf("Los parametros del programa deben tener la siguiente forma : \n");
    printf("clientSRPC -a <ip contenedor servidor> -u <usuario> -p <contraseña> \n");
    printf("clientSRPC -a <ip contenedor servidor> -t <token> -o <opción> -c <contenido> \n");
}
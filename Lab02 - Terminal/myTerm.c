/*

    myTerm v0.4

    Be glateful to: STRNeoh and manogray

*/

#define _PROGRAM_NAME "myTerm"
#include <stdlib.h>
#include <stdio.h>
#include <pwd.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "myTermColors.h"

char* isolaComando(char comando[200], char resposta[200]){
    int i = 0;
    while((comando[i] != ' ') && (comando[i] != '\0')){
        resposta[i] = comando[i];
        i++;
    }
    resposta[i] = '\0';
    return resposta;
}

char* isolaOpcao(char comando[200], char resposta[200], char comandoIsolado[200]){
    int i = strlen(comandoIsolado)+1;
    int j = 0;
    while(comando[i] != '\0'){
        resposta[j] = comando[i];
        i++;
        j++;
    }   

    resposta[j] = '\0';
    return resposta;
}

void clear(){
    system("@cls||clear");
}

void pwd(int op,char user[400]){
    char* diretorioAtual;
    char buffer[400];
    int i;
    int j = 0;

    diretorioAtual = NULL;
    diretorioAtual = getcwd(diretorioAtual,0);
    if(op == 0){
        foreground(VERDE);
        printf("%s\n",diretorioAtual);
    }

    if(op == 1){
        printf(" ");
        i = strlen(diretorioAtual)-1;
        while(diretorioAtual[i] != '/'){
            i--;
        }
        i++;
        while(diretorioAtual[i] != '\0'){
            buffer[j] = diretorioAtual[i];
            i++;
            j++;
        }
        buffer[j] = '\0';

        if(strcmp(buffer,user) == 0){
            printf("~");
        }else{
            printf("%s",buffer);
        }

        foreground(VERMELHO);
        printf(" $ ");
        foreground(VERDE);
    }
}

void cd(char opcao[200]){
    if(chdir(opcao) < 0){
        foreground(VERMELHO);
        printf("%s: Diretorio nao encontrado\n",opcao);
    }
}

void listAll(char opcao[200]){
    //LS PADRAO
    if(strcmp(opcao,"hing") == 0){
        DIR* refDir = opendir(".");
        assert(refDir != NULL);
        struct dirent *diretorio;
        while((diretorio = readdir(refDir)) != NULL){
            if(diretorio->d_name[0] != '.'){
                if((int)diretorio->d_type == 4){
                    foreground(AZUL);
                    printf("%s\n",diretorio->d_name);
                }else {
                    foreground(BRANCO);
                    printf("%s\n",diretorio->d_name);
                }
            }
        }
        closedir(refDir);

    }else{//LS COM ARGUMENTO
        if(strcmp(opcao,"-l") == 0){
            DIR* refDir = opendir(".");
            assert(refDir != NULL);
            struct dirent *diretorio;
            struct stat arqStat;
            while((diretorio = readdir(refDir)) != NULL){
                if(diretorio->d_name[0] != '.'){
                    if((int)diretorio->d_type == 4){
                        foreground(AZUL);
                        if(stat(diretorio->d_name,&arqStat) < 0){
                            printf("erro!");
                            exit(1);
                        }
                        printf("%s \t -- Tamanho: %ld bytes | Links: %ld | inode: %ld | ",diretorio->d_name, arqStat.st_size,arqStat.st_nlink,arqStat.st_ino);
                        printf("d");
                        printf( (arqStat.st_mode & S_IRUSR) ? "r" : "-");
                        printf( (arqStat.st_mode & S_IWUSR) ? "w" : "-");
                        printf( (arqStat.st_mode & S_IXUSR) ? "x" : "-");
                        printf( (arqStat.st_mode & S_IRGRP) ? "r" : "-");
                        printf( (arqStat.st_mode & S_IWGRP) ? "w" : "-");
                        printf( (arqStat.st_mode & S_IXGRP) ? "x" : "-");
                        printf( (arqStat.st_mode & S_IROTH) ? "r" : "-");
                        printf( (arqStat.st_mode & S_IWOTH) ? "w" : "-");
                        printf( (arqStat.st_mode & S_IXOTH) ? "x" : "-");
                        printf("\n");
                    }else {
                        foreground(BRANCO);
                        if(stat(diretorio->d_name,&arqStat) < 0){
                            printf("erro!");
                            exit(1);
                        }
                        printf("%s \t -- Tamanho: %ld bytes | Links: %ld | inode: %ld | ",diretorio->d_name, arqStat.st_size,arqStat.st_nlink,arqStat.st_ino);
                        printf("-");
                        printf( (arqStat.st_mode & S_IRUSR) ? "r" : "-");
                        printf( (arqStat.st_mode & S_IWUSR) ? "w" : "-");
                        printf( (arqStat.st_mode & S_IXUSR) ? "x" : "-");
                        printf( (arqStat.st_mode & S_IRGRP) ? "r" : "-");
                        printf( (arqStat.st_mode & S_IWGRP) ? "w" : "-");
                        printf( (arqStat.st_mode & S_IXGRP) ? "x" : "-");
                        printf( (arqStat.st_mode & S_IROTH) ? "r" : "-");
                        printf( (arqStat.st_mode & S_IWOTH) ? "w" : "-");
                        printf( (arqStat.st_mode & S_IXOTH) ? "x" : "-");
                        printf("\n");
                    }
                }
            }
            closedir(refDir);
        }
        if((opcao[0] == '-')&&(opcao[1] == 'l')&&(strlen(opcao) > 3)){
            char dirOpt[200];
            int cont = 3;
            int cont2 = 0;
            while(opcao[cont] != '\0'){
                dirOpt[cont2] = opcao[cont];
                cont++;
                cont2++;
            }
            dirOpt[cont2] = '\0';

            DIR* refDir = opendir(dirOpt);
            //assert(refDir != NULL);
            if(refDir == NULL){
                printf("%s",dirOpt);
                exit(1);
            }
            struct dirent *diretorio2;
            struct stat arqStat2;
            while((diretorio2 = readdir(refDir)) != NULL){
                if(diretorio2->d_name[0] != '.'){
                    if((int)diretorio2->d_type == 4){
                        foreground(AZUL);
                        if(stat(diretorio2->d_name,&arqStat2) < 0){
                            printf("erro no item %s\n",diretorio2->d_name);
                            exit(1);
                        }
                        printf("%s \t -- Tamanho: %ld bytes | Links: %ld | inode: %ld | ",diretorio2->d_name, arqStat2.st_size,arqStat2.st_nlink,arqStat2.st_ino);
                        printf("d");
                        printf( (arqStat2.st_mode & S_IRUSR) ? "r" : "-");
                        printf( (arqStat2.st_mode & S_IWUSR) ? "w" : "-");
                        printf( (arqStat2.st_mode & S_IXUSR) ? "x" : "-");
                        printf( (arqStat2.st_mode & S_IRGRP) ? "r" : "-");
                        printf( (arqStat2.st_mode & S_IWGRP) ? "w" : "-");
                        printf( (arqStat2.st_mode & S_IXGRP) ? "x" : "-");
                        printf( (arqStat2.st_mode & S_IROTH) ? "r" : "-");
                        printf( (arqStat2.st_mode & S_IWOTH) ? "w" : "-");
                        printf( (arqStat2.st_mode & S_IXOTH) ? "x" : "-");
                        printf("\n");
                    }else {
                        foreground(BRANCO);
                        if(stat(diretorio2->d_name,&arqStat2) < 0){
                            printf("erro no item %s\n",diretorio2->d_name);
                            exit(1);
                        }
                        printf("%s \t -- Tamanho: %ld bytes | Links: %ld | inode: %ld | ",diretorio2->d_name, arqStat2.st_size,arqStat2.st_nlink,arqStat2.st_ino);
                        printf("-");
                        printf( (arqStat2.st_mode & S_IRUSR) ? "r" : "-");
                        printf( (arqStat2.st_mode & S_IWUSR) ? "w" : "-");
                        printf( (arqStat2.st_mode & S_IXUSR) ? "x" : "-");
                        printf( (arqStat2.st_mode & S_IRGRP) ? "r" : "-");
                        printf( (arqStat2.st_mode & S_IWGRP) ? "w" : "-");
                        printf( (arqStat2.st_mode & S_IXGRP) ? "x" : "-");
                        printf( (arqStat2.st_mode & S_IROTH) ? "r" : "-");
                        printf( (arqStat2.st_mode & S_IWOTH) ? "w" : "-");
                        printf( (arqStat2.st_mode & S_IXOTH) ? "x" : "-");
                        printf("\n");
                    }
                }
            }
            closedir(refDir);
            
        }
    }
}

void run(char opcao[200]){
    int rc = fork();
    int contador = 0;
    int espacosBrancos = 0;
    int redSaida = 0;
    int redEntrada = 0;

    if(rc < 0){
        printf("forkFail: Nao foi possivel executar o arquivo\n");
        exit(0);
    } else if (rc == 0){/*PROCESSO FILHO*/

        while(contador < strlen(opcao)){
            if(opcao[contador] == ' '){ //VERIFICA ESPACOS EM BRANCO
                espacosBrancos = espacosBrancos + 1;
            }

            if(opcao[contador] == '>'){ //VERIFICA SE TEM >
                redSaida = 1;
            }

            if(opcao[contador] == '<'){ //VERIFICA SE TEM <
                redEntrada = 1;
            }

            contador++;
        }

        if(espacosBrancos > 0){//EXECUTA COM ARGUMENTOS
            
            if(redSaida > 0 && espacosBrancos > 2) {
                printf("executa com argumentos redirecionando saida\n\n");
            }else if(redEntrada > 0 && espacosBrancos > 2){
                printf("executa com argumentos redirecionando entrada\n\n");
            }else if(redSaida > 0 && espacosBrancos == 2){
                printf("executa sem argumentos redirecionando saida\n\n");
            }else if(redEntrada > 0 && espacosBrancos == 2){
                printf("executa sem argumentos redirecionando entrada\n\n");
            }else if(redSaida == 0 && redEntrada == 0){
                //EXECUTA COM ARGUMENTOS
                char* argumentosReais[20];
                int cont = 0;
                while(cont < 20){
                    argumentosReais[cont] = malloc(sizeof(char)*200);

                    cont++;
                }
                int contadorArgumento = 0;
                int contadorCaracArgumento = 0;
                contador = 0;
                
                while(contador < strlen(opcao)){
                    if(opcao[contador] != ' '){
                        argumentosReais[contadorArgumento][contadorCaracArgumento] = opcao[contador];
                    }else{
                        argumentosReais[contadorArgumento][contadorCaracArgumento] = '\0';
                        contadorArgumento = contadorArgumento + 1;
                        contadorCaracArgumento = -1;
                    }

                    contador++;
                    contadorCaracArgumento++;
                }

                contadorArgumento = contadorArgumento + 1;

                argumentosReais[contadorArgumento] = NULL;

                execv(argumentosReais[0],argumentosReais);

            }

        }else { //EXECUTA SEM ARGUMENTOS
            char* argumentosTabela[200] = {opcao,NULL};
            
            execv(opcao,argumentosTabela);
        }

        exit(0);

    } else {/*PROCESSO PAI*/
        int wc = wait(NULL);
    }
}

int main(int argc, char *argv[]){

    clear();
    setbuf(stdin,NULL);

    register struct passwd *pw;
    register uid_t uid;
    uid = geteuid();
    pw = getpwuid(uid);
    
    char comando[200];
    char comandoIsolado[200];
    char resposta[200];
    char opcao[200];

    while(strcmp(comandoIsolado,"exit") != 0){
        strcpy(comando,"nothing"); 
        foreground(AZUL);
        printf("[%s",pw->pw_name);
        printf("@");
        printf("Computer]");
        foreground(VERDE);
        pwd(1,pw->pw_name);

        foreground(BRANCO);
        scanf("%[^\n]s",comando);
        setbuf(stdin,NULL);
        if(strcmp(comando,"nothing") != 0){
            strcpy(comandoIsolado,isolaComando(comando,resposta));
            strcpy(opcao,isolaOpcao(comando,resposta,comandoIsolado));

            if(strcmp(comandoIsolado,"cd") == 0){
                cd(opcao);
            }else if (strcmp(comandoIsolado,"clear") == 0) {
                clear();
            }else if (strcmp(comandoIsolado,"pwd") == 0) {
                pwd(0,"");
            }else if (strcmp(comandoIsolado,"ls") == 0) {
                listAll(opcao);
            }else if (strcmp(comandoIsolado,"run") == 0){
                run(opcao);
            }else if ( comando[0] == '.' && comando[1] == '/' ){
                printf("\nPor favor use run <programa>\n");
            }else if (strcmp(comandoIsolado,"exit") == 0){
            }else {
                //printf("%s: Comando nao encontrado\n", comandoIsolado);
                system(comando);
            }
        }
    }

    return 0;
}

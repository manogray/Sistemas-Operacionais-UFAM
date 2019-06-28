/*

    myTerm v0.3

    Alunos: Evaldo Patrik dos Santos Cardoso - 21453640
            Luis de Gonzaga Mota Pinto Filho - 21753684

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

void pwd(int op){
    char* diretorioAtual;
    int i;

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
            printf("%c",diretorioAtual[i]);
            i++;
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
    char argumentos[20][200];

    if(rc < 0){
        printf("forkFail: Nao foi possivel executar o arquivo\n");
        exit(0);
    } else if (rc == 0){/*PROCESSO FILHO*/
        int i = 0;
        int j = 0;
        int aux = 0;
        while(opcao[i] != '\0'){
            if(opcao[i] != ' '){
                argumentos[j][aux] = opcao[i];
                aux++;
            }else{
                argumentos[j][aux] = '\0';
                j++;
                aux = 0;
            }
            i++;
        }
        j++;
        char *myargs[20];
        int demo = 0;
        while(demo < j){
            myargs[demo] = strdup(argumentos[demo]);
            demo++;
        }
        myargs[demo] = NULL;

        if(*myargs[1] == '>'){
            FILE * arquivo = fopen(myargs[2],"w");
            stdout = arquivo;
            execl(argumentos[0],argumentos[0],stdout,NULL);
        }else if (*myargs[1] == '<'){
            
        }else {

        }

        //execv(argumentos[0], myargs);

    } else {/*PROCESSO PAI*/
        int wc = wait(NULL);
    }
}

int main(int argc, char *argv[]){

    system("clear");
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
        printf("[%s@Computer]",pw->pw_name);
        
        foreground(VERDE);
        pwd(1);

        foreground(BRANCO);
        scanf("%[^\n]s",comando);
        setbuf(stdin,NULL);
        if(strcmp(comando,"nothing") != 0){
            strcpy(comandoIsolado,isolaComando(comando,resposta));
            strcpy(opcao,isolaOpcao(comando,resposta,comandoIsolado));

            if(strcmp(comandoIsolado,"cd") == 0){
                cd(opcao);
            }else if (strcmp(comandoIsolado,"clear") == 0) {
                system("clear");
            }else if (strcmp(comandoIsolado,"pwd") == 0) {
                pwd(0);
            }else if (strcmp(comandoIsolado,"ls") == 0) {
                listAll(opcao);
            }else if (strcmp(comandoIsolado,"run") == 0){
                run(opcao);
            }else if (strcmp(comandoIsolado,"exit") == 0){
            }else {
                printf("%s: Comando nao encontrado\n", comandoIsolado); 
            }
        }
    }

    return 0;
}

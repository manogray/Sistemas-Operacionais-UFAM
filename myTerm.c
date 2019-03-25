#define _PROGRAM_NAME "myTerm"
#include <stdlib.h>
#include <stdio.h>
#include <pwd.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

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
        printf(" $ ");
    }
}

void cd(char opcao[200]){
    if(chdir(opcao) < 0){
        printf("%s: Diretorio nao encontrado\n",opcao);
    }
}

int main(int argc, char *argv[]){

    system("clear");

    register struct passwd *pw;
    register uid_t uid;
    uid = geteuid();
    pw = getpwuid(uid);
    
    char comando[200];
    char comandoIsolado[200];
    char resposta[200];
    char opcao[200];

    while(strcmp(comandoIsolado,"exit") != 0){
        
        printf("(%s@Computer)",pw->pw_name);
        pwd(1);

        scanf("%[^\n]s",comando);
        setbuf(stdin,NULL);

        strcpy(comandoIsolado,isolaComando(comando,resposta));
        strcpy(opcao,isolaOpcao(comando,resposta,comandoIsolado));

        if(strcmp(comandoIsolado,"cd") == 0){
            cd(opcao);
        }else if (strcmp(comandoIsolado,"clear") == 0) {
            system("clear");
        }else if (strcmp(comandoIsolado,"pwd") == 0) {
            pwd(0);
        }else if (strcmp(comandoIsolado,"exit") == 0){
        }else {
            printf("%s: Comando nao encontrado\n", comandoIsolado);
        }
    }

    return 0;
}

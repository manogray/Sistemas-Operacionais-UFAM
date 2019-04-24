/*

    myTerm

    Alunos: Evaldo Patrik dos Santos Cardoso - 21453640
            Luis de Gonzaga Mota Pinto Filho - 21753684

*/

#define _PROGRAM_NAME "myTerm"
#include <stdlib.h>
#include <stdio.h>
#include <pwd.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
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
                system("ls");
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

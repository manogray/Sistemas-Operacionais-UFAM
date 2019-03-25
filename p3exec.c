#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {// fork falhou
        fprintf(stderr, "fork falhou\n");
        exit(1);
    } else if (rc == 0) { // filho
        printf("hello, Sou o filho (pid:%d)\n", (int) getpid());
        char *myargs[3];
        myargs[0] = strdup("wc");   // programa: "wc"
        myargs[1] = strdup("p3.c"); // argumento: nome do arquivo
        myargs[2] = NULL;           // fim do vetor
        execvp(myargs[0], myargs);  // roda wc
        printf("Isso nao deve ser imprimido");
    } else {// Pai vem por aqui
        int wc = wait(NULL);
        printf("hello, sou o pai de %d (wc:%d) (pid:%d)\n",
	       rc, wc, (int) getpid());
    }
    return 0;
}

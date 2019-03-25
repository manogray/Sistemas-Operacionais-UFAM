#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork falhou\n");
        exit(1);
    } else if (rc == 0) {// Filho: Saida para um arquivo
	close(STDOUT_FILENO); 
	open("./p4.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);

        char *myargs[3];
        myargs[0] = strdup("wc");   // programa: "wc" 
        myargs[1] = strdup("p4saida.c"); // argumento: arquivo a contar
        myargs[2] = NULL;           // fim do vetor
        execvp(myargs[0], myargs);  // executa wc
    } else { // Processo original vem por aqui
        int wc = wait(NULL);
    }
    return 0;
}

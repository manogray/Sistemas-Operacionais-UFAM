#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) { // fork falhou
        fprintf(stderr, "fork falhou\n");
        exit(1);
    } else if (rc == 0) { // filho (processo novo)
        printf("Ola, Eu sou o filho (pid:%d)\n", (int) getpid());
    } else { // Pai vem por aqui
        int wc = wait(NULL);
        printf("Ola, Eu sou o pai de %d (wc:%d) (pid:%d)\n",
	       rc, wc, (int) getpid());
    }
    return 0;
}

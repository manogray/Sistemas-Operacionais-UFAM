#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
	printf("hello world (pid:%d)\n", (int) getpid());
	int rc = fork();
	if (rc < 0) {
	// fork falhou; saia do programa
		fprintf(stderr, "Erro no fork\n");
	exit(1);
	} else if (rc == 0) {
	// o filho entra aqui (novo processo)
		printf("Ola, Sou o filho (pid:%d)\n", (int) getpid());
	} else {
	// O pai entra aqui (processo original)
		printf("Ola, sou o pai de %d (pid:%d)\n",
		rc, (int) getpid());
	}
	return 0;
}

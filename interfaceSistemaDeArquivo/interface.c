//CRIACAO DE ARQUIVO
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(){
    int arq = open("arquivo",O_CREAT|O_WRONLY|O_TRUNC,S_IRUSR|S_IWUSR);
}
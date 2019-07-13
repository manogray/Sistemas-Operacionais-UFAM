#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

    int cont;
    
    printf("\nHello World\n");

    for(cont=0;cont < argc; cont++){
        printf("%d Parametro: %s\n",cont,argv[cont]);
    }

    return 0;
}
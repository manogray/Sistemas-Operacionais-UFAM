#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

int main(){

    //FILE* arquivo = fopen("seek.dat","wb");

    FILE* arquivo = fopen("seek.dat","r+b");

    //fseek(arquivo,2,SEEK_SET);

    char vet[3][10] = {"luis","evaldo","jonathas"};

    char vet2[3][10];

    //fwrite(vet,sizeof(char)*10,3,arquivo);
     
    fread(vet2,sizeof(char)*10,3,arquivo);
    int i;
    for(i=0;i<5;i++){
        printf("%s ",vet2[i]);
    }
    
    fflush(arquivo);
    fclose(arquivo);


    return 0;

}
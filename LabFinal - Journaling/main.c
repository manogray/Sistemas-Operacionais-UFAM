#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Journal {
    int numeroMagico;
    int tamanho;
    int crc;
    int id;
    char consulta[1000];
    int posicao;
    int contador;
}TJournal;

typedef struct Vetor {
    int tamanho;
    TJournal** vetor;
    int ocupacao;
}Tvetor;


void separaJournal(TJournal* journal, char linha[1000]){
    char delimitador[] = " ";

    char* auxiliar = strtok(linha,delimitador);

    journal->numeroMagico = atoi(auxiliar);
    auxiliar = strtok(NULL,delimitador);
    
    journal->tamanho = atoi(auxiliar);
    auxiliar = strtok(NULL,delimitador);
    
    journal->crc = atoi(auxiliar);
    auxiliar = strtok(NULL,delimitador);
    
    journal->id = atoi(auxiliar);
    auxiliar = strtok(NULL,delimitador);

    strcpy(journal->consulta,auxiliar);
    auxiliar = strtok(NULL,delimitador);

    journal->posicao = atoi(auxiliar);
    auxiliar = strtok(NULL,delimitador);

    journal->contador = atoi(auxiliar);
}


Tvetor* lerJournal(char* arquivo){
    Tvetor* vect = malloc(sizeof(Tvetor));
    vect->tamanho = 0;
    vect->ocupacao = 0;
    vect->vetor = malloc(sizeof(TJournal)*10000);
    char auxiliar[1000];
    FILE* arq = fopen(arquivo,"r");
    if(arq != NULL){
        while(!feof(arq)){
            TJournal* linhaAtual = malloc(sizeof(TJournal));
            fscanf(arq,"%[^\n]\n",auxiliar);
            separaJournal(linhaAtual,auxiliar);
            vect->vetor[vect->ocupacao] = linhaAtual;
            vect->ocupacao = vect->ocupacao + 1;
        }
    }else {
        printf("\nJournal nao encontrado\n");
        exit(1);
    }

    return vect;
}

int main(){

    Tvetor* journal = lerJournal("fakeJournaling.dat");

    int contador = 0;

    while(contador < journal->ocupacao){
        TJournal* linhaAtual = journal->vetor[contador];
        printf("%d - %s\n",linhaAtual->crc,linhaAtual->consulta);

        contador = contador + 1;
    }

    return 0;
}
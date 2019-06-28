#include <stdio.h>
#include <stdlib.h>

#define NumMagico  20192028

typedef struct journal_Token{
    int NumeroMagico;
    int tamanho;
    int crc;
    int id;
    char consulta;
    int posicao;
    int contador;
}Token;



Token journaling(char *linha){
    printf("%s",linha);
   // Token->NumeroMagico = NumMagico;
  
  // printf("%d", sizeof(linha)); 
}

void le_Consulta(char *caminho){
    FILE *arquivo = fopen(caminho, "r");
    char Linha[1000];
    char *resultado;
    if(arquivo == NULL){
       printf("Arquivo Zuado");
    }
    while(!feof(arquivo)){
        resultado = fgets(Linha, 1000, arquivo);
        if(resultado){
            journaling(Linha);
        }
    }
    fclose(arquivo);
}

int main(){
    le_Consulta("evaldo.txt");

    return 0;
}




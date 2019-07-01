#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define NumMagico  20192028

typedef struct journal_Token{
    int NumeroMagico;
    int tamanho;
    int crc;
    int id;
    char consulta[1000];
    int posicao;
    int contador;
}Token;


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

int atoiQueFunciona(char consult[1000]){
	int tamanho = strlen(consult);
    int somaAscii;
	char delim[] = " ";
	char *ptr = strtok(consult, delim);
	while(ptr != NULL){
		ptr = strtok(NULL, delim);
	}
    //consult é inteiro equivalente ao caractere na tabela Ascii
	for (int i = 0; i < tamanho; i++){
        somaAscii = somaAscii + consult[i];
	}
    return somaAscii;
}

int checksun(int id, int contador, int posicao, char consulta[1000]){
    int crc;
    int consult = atoiQueFunciona(consulta);
    crc = (id + contador + posicao + consult) % 227;
    return crc;
}

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
    fclose(arq);
    return vect;

}

TJournal* buscaNoJournal(Tvetor *Journal, int id ){
    int cont = 0;

    while(cont < Journal->ocupacao){
        TJournal* linhaAtual = Journal->vetor[cont];
        if( id == linhaAtual->id){
            printf("retornando linha atual");
            return linhaAtual;
        }
    }
    return NULL;
}

size_t arquivoTam(const char* filename) {
    struct stat st;
    if(stat(filename, &st) != 0) {
        return 0;
    }
    return st.st_size;
    //printf("%d\n",st.st_size);   
}

void journaling(Token *linhaConsulta){
    //JOURNAL
    const char* arqJournal = "journaling.dat";
    FILE* journal = fopen("journaling.dat","a+b");
   
    if(journal != NULL){
        printf("arquivo criado\n");
        if(arquivoTam(arqJournal) == 0){
            printf("entrou na primeira condição\n");
            fprintf(journal, "%d %d %d %d %s %d %d\n",
                linhaConsulta->NumeroMagico,
                linhaConsulta->tamanho,
                linhaConsulta->crc,
                linhaConsulta->id,
                linhaConsulta->consulta,
                linhaConsulta->posicao,
                linhaConsulta->contador
            );

        }else if(arquivoTam(arqJournal) < 1000){
            Tvetor * searchJour = lerJournal("journaling.dat");
            TJournal* linhaExistente = buscaNoJournal(searchJour,linhaConsulta->id);
            if( linhaExistente != NULL){
                linhaConsulta->contador = linhaExistente->contador + 1;
                linhaConsulta->crc = checksun(linhaConsulta->id,
                linhaConsulta->contador,
                linhaConsulta->posicao,
                linhaConsulta->consulta);

                fprintf(journal, "%d %d %d %d %s %d %d\n",
                linhaConsulta->NumeroMagico,
                linhaConsulta->tamanho,
                linhaConsulta->crc,
                linhaConsulta->id,
                linhaConsulta->consulta,
                linhaConsulta->posicao,
                linhaConsulta->contador);
            }

        }else if(arquivoTam(arqJournal) > 1000 && arquivoTam(arqJournal) <= 1024){
           // checkpoint();
        }
    }else{
        printf("Deu merda no arquivo\n");
    }
}

void separaConsulta(Token* linhaConsulta,char linha[1000]){
    char limite[] = " ";
    linhaConsulta->NumeroMagico = NumMagico;
    linhaConsulta->tamanho = strlen(linha);
    char* aux = strtok(linha, limite);
    linhaConsulta->id = atoi(aux);
    aux = strtok(NULL,limite);
    strcpy(linhaConsulta->consulta, aux);
    aux = strtok(NULL, limite);
    linhaConsulta->posicao = atoi(aux);
    linhaConsulta->contador = 1;
    linhaConsulta->crc = checksun(
        linhaConsulta->id,
        linhaConsulta->contador,
        linhaConsulta->posicao,
        linhaConsulta->consulta);
    journaling(linhaConsulta);
    printf("%d\n",linhaConsulta->tamanho);
}

void le_Consulta(char *caminho, Token* cafe){
    FILE *arquivo = fopen(caminho, "r");
    char Linha[1000];
    char *resultado;
    if(arquivo == NULL){
       printf("Arquivo Zuado\n");
    }
    while(!feof(arquivo)){
        resultado = fgets(Linha, 1000, arquivo);
        if(resultado){
            separaConsulta(cafe,Linha);
        }
    }
    fclose(arquivo);
}


int main(){
    printf("aaaaaaaaaahhhhhh\n");
    Token *cafe = malloc(sizeof(Token));
    le_Consulta("evaldo.txt",cafe);
    return 0;
}




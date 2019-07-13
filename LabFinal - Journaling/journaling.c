/*
    Alunos: Evaldo Patrik dos Santos Cardoso - 21453640
            Luis de Gonzaga Mota Pinto Filho - 21753684
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define NumMagico  20192028

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
    TJournal* vetor[50000];
    int ocupacao;
}Tvetor;

//?[FUNCIONAL]
size_t tamanhoArquivo(const char* filename) {
    struct stat st;
    if(stat(filename, &st) != 0) {
        return 0;
    }
    return st.st_size;   
}

//?[FUNCIONAL]
int asciiSoma(char consult[1000]){
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

//?[FUNCIONAL]
void checksum(TJournal* linha){
    int crc;
    int consult = asciiSoma(linha->consulta);
    crc = (linha->id + linha->contador + linha->posicao + consult) % 227;
    linha->crc = crc;
}

void checkpoint(int quant){
    
    Tvetor* journal = lerJournal(quant);

    //DADOS
    FILE* arq = fopen("dados.dat","ab");
    int contador = 0;
    if(arq != NULL){
        
        while(contador < journal->ocupacao){
            TJournal* linhaAtual = journal->vetor[contador];
            fseek(arq,linhaAtual->posicao,SEEK_SET);
            fwrite(linhaAtual->consulta,sizeof(char)*1000,1,arq);

            contador = contador + 1;
        }
    }

    fclose(arq);
    
    //CONTA
    contador = 0;
    FILE* arq2 = fopen("conta.dat","ab");
    if(arq2 != NULL){
        char* conta = malloc(sizeof(char)*50);
        while(contador < journal->ocupacao){
            TJournal* linhaAtual = journal->vetor[contador];
            
            fwrite(conta,sizeof(int),1,arq2);
            contador = contador + 1;
        }
    }
    fclose(arq2);

    //OFFSETS
    contador = 0;
    FILE* arq3 = fopen("offsets.dat","ab");
    if(arq3 != NULL){
        char offset[50];
        while(contador < journal->ocupacao){
            TJournal* linhaAtual = journal->vetor[contador];
            sprintf(offset,"%d",linhaAtual->posicao);
            fwrite(offset,sizeof(int),1,arq3);
            contador = contador + 1;
        }
    }
    fclose(arq3);
}

//PREENCHE OS VALORES VINDOS DO ARQUIVO NO TIPO JOURNAL
//?[FUNCIONAL]
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

//LE O JOURNAL E COLOCA EM MEMORIA
//?[FUNCIONAL]
Tvetor* lerJournal(int quant){
    Tvetor* vect = malloc(sizeof(Tvetor));
    int cont = 0;
    while(cont < quant){
        FILE* conteudoP = fopen("journal.dat","r+b");

        TJournal* linhaAtual = malloc(sizeof(TJournal)); 

        if(conteudoP != NULL){
            fseek(conteudoP,sizeof(TJournal)*cont+1,SEEK_SET);
            fread(linhaAtual,sizeof(TJournal)*quant,1,conteudoP);
            vect->vetor[cont] = linhaAtual;
            
        }else {
            printf("\nJournal nao encontrado\n");
            exit(1);
        }

        fclose(conteudoP);

        cont = cont + 1;
    }
    
    return vect;

}

//BUSCA NO JOURNAL EM MEMORIA
//?[FUNCIONAL]
int buscaNoJournal(Tvetor *Journal, int id ){
    int cont = 0;

    while(cont < Journal->ocupacao){
        TJournal* linhaAtual = Journal->vetor[cont];
        if( id == linhaAtual->id){
            return cont;
        }

        cont = cont + 1;
    }
    return -1;
}

//ESCREVE JOURNAL EM MEMORIA NO ARQUIVO
//?[FUNCIONAL]

void insereNoJournal(Tvetor* consultas, int quant){
    
    const char* arqJournal = "journal.dat";

    while(consultas->vetor[quant] != NULL){

        TJournal* linhaConsulta = consultas->vetor[quant];

        if(tamanhoArquivo(arqJournal) < 1024){
            //JOURNAL COM ESPACO
            printf("Journal Vazio\n");
            printf("Consulta nova - %s\n",linhaConsulta->consulta);
            FILE* journal = fopen("journal.dat","r+b");
            
            if(journal!=NULL){
                fseek(journal,0,SEEK_END);
                fwrite(linhaConsulta,sizeof(TJournal),1,journal);
            }else{
                printf("journal nao encontrado\n");
            }
            
            fclose(journal);

        }else{
            //JOURNAL CHEIO
            checkpoint(quant);
            insereNoJournal(consultas,quant);
            break;
        }

        quant = quant + 1;
    }
    
}

//PREENCHE E CALCULA OS VALORES VINDOS DO ARQUIVO NO TIPO JOURNAL
//?[FUNCIONAL]
void separaConsulta(TJournal* linhaConsulta,char linha[1000]){
    char limite[] = " ";
    linhaConsulta->numeroMagico = NumMagico;
    linhaConsulta->tamanho = strlen(linha);
    
    char* aux = strtok(linha, limite);
    linhaConsulta->id = atoi(aux);
    aux = strtok(NULL,limite);
    
    strcpy(linhaConsulta->consulta, aux);
    aux = strtok(NULL, limite);
    
    linhaConsulta->posicao = atoi(aux);
    
    linhaConsulta->contador = 1;
    checksum(linhaConsulta);
}

//LER ARQUIVO DE CONSULTAS
//?[FUNCIONAL]
Tvetor* lerConsultas(char *caminho){
    FILE *arquivo = fopen(caminho, "r");
    char linha[1000];
    char *resultado;
    int posicao;
    Tvetor* vetorzao = malloc(sizeof(Tvetor));
    vetorzao->ocupacao = 0;

    if(arquivo == NULL){
       printf("Arquivo Zuado\n");
       exit(1);
    }
    while(!feof(arquivo)){
        TJournal* linhaAtual = malloc(sizeof(TJournal));
        fscanf(arquivo,"%[^\n]\n",linha);
        separaConsulta(linhaAtual,linha);
        posicao = buscaNoJournal(vetorzao,linhaAtual->id);
        if(posicao != -1){
            TJournal * linhaUpdate = vetorzao->vetor[posicao];
            linhaUpdate->contador = linhaUpdate->contador + 1;
            checksum(linhaUpdate);
        }else{
            vetorzao->vetor[vetorzao->ocupacao] = linhaAtual;
            vetorzao->ocupacao = vetorzao->ocupacao + 1;
        }
    
    }
    fclose(arquivo);

    return vetorzao;
}


int main(){
    printf("JOURNALING INICIADO\n\n");

    Tvetor* Consultas = lerConsultas("ConsExemplo.txt");

    insereNoJournal(Consultas,0);

    return 0;
}
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

int main (int argc, char *argv[]){
    int PAGESIZE = 4096;
    int salto = PAGESIZE/sizeof(int);
    int npags;
    int ninteracao;

    if(argv[1] != NULL){
        npags = atoi(argv[1]);
    }else{
        npags = 10;
    }

    if(argv[2] != NULL){
        ninteracao = atoi(argv[2]);
    }else{
        ninteracao = 1;
    }
    
    int *vetor = (int*)malloc(sizeof(int)*PAGESIZE*npags);
    int j;
    int i;
    double tempo_sec;
    double tempo_total;
    clock_t inicio, fim;
    
    for(j=0;j<ninteracao;j++){
        inicio = clock();
        for(i=0;i<npags*salto;i+=salto){
            vetor[i]+=1;
        }
        fim = clock();
        tempo_sec = (double)(fim-inicio)/CLOCKS_PER_SEC;
        tempo_total += tempo_sec;
    }

    printf("%d %lf\n",npags,tempo_total/ninteracao);

}
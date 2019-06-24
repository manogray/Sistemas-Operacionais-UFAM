#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#define NTHREADS 50


char fechado = 0;

int numCliente=0, ncadeiras;


void* dentista(void* arg){
   int i,*n = (int*)arg;
   for(i=0;i<*n;i++){

      printf("Dentista eguando\n");

      //Cliente Chegou
      printf("Dentista atendendo cliente %d\n",numCliente);
      usleep(100);

      //Acabou o atendimento
      printf("Acabou o atendimento do dentista\n");

   }
}

void* cliente(void* arg){
   int n = *((int *)arg);
   if(0){// ALTERE ESTA CONDICAO: DENTISTA OCUPADO
      if(0){ // ALTERAR ESTA CONDICAO: Se existem cadeiras livres
         printf("Cliente %d sentando na cadeira %d da fila de espera\n",n,ncadeiras--);
      }
      else{
         printf("Consultorio lotado. Cliente %d ficou puto e foi embora\n",n);
         // Vai embora
      }
   }
   numCliente = n;
   printf("Cliente %d sendo atendido\n",n);

   // Acabou o Atendimento
   printf("Cliente %d indo embora\n",n);
   return NULL;
}

int main(int argc,char* argv[]){
   pthread_t tdentista,clientes[NTHREADS];
   int ids[NTHREADS],i,ncli;

   if(argc<3){
      fprintf(stderr,"Uso %s <nclientes> <ncadeiras>\n",argv[0]);
      return 1;
   }
   ncli = atoi(argv[1]);
   ncadeiras = atoi(argv[2]);
   pthread_create(&tdentista,NULL,dentista,&ncli);
   for(i=0;i<atoi(argv[1]);i++){
      ids[i]=i;
      pthread_create(&clientes[i],NULL,cliente,&ids[i]);
      usleep(100);//PODE USAR PRA TESTAR
   }

   for(i=0;i<atoi(argv[1]);i++){
      pthread_join(clientes[i],NULL);
   }
   pthread_join(tdentista,NULL);
   return 0;
}

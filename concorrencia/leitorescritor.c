#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define MAX 100000

typedef struct _rwlock_t {
   sem_t escrita;
   sem_t lock;
   int leitores;
} rwlock_t;

void rwlock_init(rwlock_t *lock) {
   lock->leitores = 0;
   sem_init(&lock->lock, 0,1); //SEMAFORO COMO MUTEX
   sem_init(&lock->escrita,0, 1); //SEMAFORO COMO MUTEX
}

int nescritas,counter;

rwlock_t lock;

void *leitor(void *arg) {
   int local;
   sem_wait(&lock.lock); //TRAVA
   lock.leitores++;
   if(lock.leitores == 1){
      sem_wait(&lock.escrita); //TRAVA ESCRITA
   }
   sem_post(&lock.lock); //DESTRAVA
   
   local = counter; //Leitura

   sem_wait(&lock.lock); //TRAVA
   lock.leitores--;
   if(lock.leitores == 0){
      sem_post(&lock.escrita); //DESTRAVA ESCRITA
   }
   sem_post(&lock.lock); //DESTRAVA
   printf("Leitor %d leu %d\n", *((int*)arg),local);
}

void *escritor(void *arg) {
   int i;
   for (i = 0; i < nescritas; i++) {
      sem_wait(&lock.escrita); //TRAVA ESCRITA
      counter++; //Escrita
      printf("Escritor %d escreveu %d\n",i,counter);
      sem_post(&lock.escrita); //DESTRAVA ESCRITA
      usleep(100);
   }
   printf("Escritor Acabou\n");
   return NULL;
}

int main(int argc, char *argv[]) {
   int leitores,i;
   if (argc != 3) {
      fprintf(stderr, "uso: rwlock leitores nescritas\n");
      exit(1);
   }
   leitores = atoi(argv[1]);
   nescritas = atoi(argv[2]);

   rwlock_init(&lock); 
   pthread_t esc, lei[MAX];
   pthread_create(&esc, NULL, escritor, NULL);
   for(i=0;i<leitores;i++){
      pthread_create(&lei[i], NULL, leitor, &i);
//      usleep(rand()%100000);
   }
   pthread_join(esc, NULL);
   for(i=0;i<leitores;i++){
      pthread_join(lei[i], NULL);
   }
   printf("Acabou!\n");
   return 0;
}



#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#define NUMCPUS 10

typedef struct __conta_t {
	int global; // contador global
	pthread_mutex_t glock; // global lock
	int local[NUMCPUS]; // contador por-cpu
	pthread_mutex_t llock[NUMCPUS]; // ... suas locks
	int limiar; // limiar de atualizacao
} conta_t;

// inicializa todas as variaveis
void inicializa(conta_t *c, int limiar) {
	c->limiar = limiar;
	c->global = 0;
	pthread_mutex_init(&c->glock, NULL);
	int i;
	for (i = 0; i < NUMCPUS; i++) {
		c->local[i] = 0;
		pthread_mutex_init(&c->llock[i], NULL);
	}
}
// update: atualiza o contador local.
// Se ele passar de limiar, atualiza o global
void update(conta_t *c, int threadID, int amt) {
	int cpu = threadID % NUMCPUS;
	pthread_mutex_lock(&c->llock[cpu]);
	c->local[cpu] += amt;
	if (c->local[cpu] >= c->limiar) {
		// transfer to global (assumes amt>0)
		pthread_mutex_lock(&c->glock);
		c->global += c->local[cpu];
		pthread_mutex_unlock(&c->glock);
		c->local[cpu] = 0;
	}
	pthread_mutex_unlock(&c->llock[cpu]);
}
// get: just return global amount (approximate)
int get(conta_t *c) {
	pthread_mutex_lock(&c->glock);
	int val = c->global;
	pthread_mutex_unlock(&c->glock);
	return val; // only approximate!
}

conta_t contador;

void* atualiza(int threadID){
	int i;
	int amt = 1;
	for(i=0;i<1000000;i++){
		update(&contador,(int)threadID,amt);
	}

	return NULL;
}

int main(int argc, char* argv[]){
	int i;
	int nthreads;
	inicializa(&contador,10);

	if(argv[1] != NULL){
		nthreads = atoi(argv[1]);
	}else {
		nthreads = 4;
	}

	pthread_t p[nthreads];
	int num[nthreads];

	for(i=0;i<nthreads;i++){
		num[i]=i;
		pthread_create(&p[i], NULL, atualiza,(void *) (int) num[i]);
	}

	for(i=0;i<nthreads;i++){
		pthread_join(p[i], NULL);
	}

	printf("contador %d\n\n",get(&contador));
	return 0;
}

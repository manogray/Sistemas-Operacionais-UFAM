#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

typedef struct __counter_t {
	int value;
	pthread_mutex_t trava;
} counter_t;

void init(counter_t *c) {
	pthread_mutex_init(&c->trava,NULL);
	c->value = 0;
}

void increment(counter_t *c) {
	pthread_mutex_lock(&c->trava);
	c->value++;
	pthread_mutex_unlock(&c->trava);
}

void decrement(counter_t *c) {
	pthread_mutex_lock(&c->trava);
	c->value--;
	pthread_mutex_unlock(&c->trava);
}

int get(counter_t *c) {
	return c->value;
}

counter_t conta;

void* atualiza(){
	int i;
	for(i=0;i<1000000;i++){
		increment(&conta);
	}

	return NULL;
}

int main(int argc, char* argv[]){
	int i;
	int nthreads;
	init(&conta);

	if(argv[1] != NULL){
		nthreads = atoi(argv[1]);
	}else {
		nthreads = 4;
	}

	pthread_t p[nthreads];

	for(i=0;i<nthreads;i++){
		pthread_create(&p[i], NULL, atualiza, NULL);
	}

	for(i=0;i<nthreads;i++){
		pthread_join(p[i], NULL);
	}

	printf("contador %d\n\n",get(&conta));
	return 0;
}

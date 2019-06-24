#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include "hash.h"


using namespace std;


void* acessa(void* arg){
	float ratio = 1000; //80% de put, 20% de get inicialmente
	meuhash* h = (meuhash*)arg;
	for(int i=0;i<1000;i++){
		printf("inicio do for\n");
		if(rand()%1000<ratio){
			printf("inserindo numero\n");
			h->put(rand()%2000,i);
			printf("sai do put\n");
		}else{
			printf("buscando numero\n");
			h->get(rand()%2000);
		}

		if(i%10==0){
			ratio=(150 + ratio)/2.71; // ajusta a taxa de put/get
		}
	}

}

int main(int argc,char* argv[]){
	meuhash* h = new meuhash();
	int i;
	pthread_t p[1];

	srand(0);

	for(i=0;i<1;i++){
		pthread_create(&p[i],NULL,acessa,(void*)&h);
	}
	for(i=0;i<1;i++)
		pthread_join(p[i],NULL);

	return 0;
}
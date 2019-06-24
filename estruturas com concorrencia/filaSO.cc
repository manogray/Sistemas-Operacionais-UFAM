#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define TAMFILA 10000
#define NTHREADS 10
#define NELEM 10000

using namespace std;

class Fila{
	int *vet;
	int inicio, fim, tamanho, n;
	pthread_mutex_t trava;
	int cheia(){ return (n==tamanho)? 1:0;}//Nao precisa fazer estas thread-safe, desde q qndo usadas em pop e push estejam ok
	int vazia(){ return (n==0)?1:0; }
	public:
	Fila(int tam){
		vet = new int[tam];
		tamanho = tam;
		inicio=fim=n=0;
		pthread_mutex_init(&trava,NULL);
	}
	~Fila(){ delete[] vet;}
/*	void esvazia(){
		inicio=fim=n=0;
	}*/
	void push(int val){
		pthread_mutex_lock(&trava);
		if(!cheia()){
			vet[fim]=val;
			fim = (fim+1)%tamanho;
			n++;
		}
		pthread_mutex_unlock(&trava);
	}
//	int top(){if(!vazia())return vet[inicio]; else return -1;}
	int pop(){
		int v=-1;
		pthread_mutex_lock(&trava);
		if(!vazia()){
			v = vet[inicio];
			inicio = (inicio+1) % tamanho;
			n--;
		}
		pthread_mutex_unlock(&trava);
		return v;
	}
};

Fila fglobal(TAMFILA);

void* poe(void* num){
	int* total = (int*) num;
	for(int i=0;i<*total;i++)
		fglobal.push(i);
}

void* tira(void* num){
	int* total = (int*) num,ret;
	for(int i=0;i<*total;i++){
		ret = fglobal.pop();
		if(ret!=-1)
			cout<<"Valor:"<<i<<endl;
		else cout<<"Fila vazia"<<endl;
	}
}

int main(){
	pthread_t p[NTHREADS];
	int i,r=NELEM;
	for(i=0;i<NTHREADS;i+=2){
		pthread_create(&p[i], NULL, poe, (void *) &r);
		pthread_create(&p[i+1], NULL, tira, (void *) &r);
	}
	for(i=0;i<NTHREADS;i++){
		pthread_join(p[i],NULL);
	}


}

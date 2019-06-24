#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include "hash.h"

Elemento::Elemento(int valorRecebido){
    this->valor = valorRecebido;
    this->proximo = NULL;
}

Elemento::~Elemento(){}

Encadeada::Encadeada(){
    this->primeiro = NULL;
    this->ocupacao = 0;
}

void Encadeada::inserir(Elemento* elem){
    printf("entrei na insereLista");
    if(this->primeiro==NULL){
        printf("Lista vazia");
        this->primeiro = elem;
        this->ocupacao = this->ocupacao + 1;
        printf("Inserido na cabeca\n");
    }else{
        printf("Lista populada");
        elem->proximo = this->primeiro;
        this->primeiro = elem;
        printf("Inserido no inicio\n");
        this->ocupacao += 1;
        printf("tamanho atual: %d\n",ocupacao);
    }
}

int Encadeada::buscar(int valorRecebido){
    Elemento* elementoAux =  this->primeiro;
    int retorno = 0;

    while(elementoAux != NULL){
        if(elementoAux->valor == valorRecebido){
            retorno = 1;
        }

        elementoAux = elementoAux->proximo;          
    }

    return retorno;
}

meuhash::meuhash(){
    for(int i=0;i<TAMBUCKET;i++){
        this->tabelahash[i] = new Encadeada();
    }
    this->ocupacao = 0;
}

int meuhash::get(int chave){
    int hashGerado = fhash(chave);
    Encadeada* listaAuxiliar = this->tabelahash[hashGerado];
    listaAuxiliar->buscar(chave);
}

void meuhash::put(int chave,int val){
    int hashGerado = fhash(chave);
    printf("valorGerado: %d \nhashGerado: %d\n",chave,hashGerado);
    Encadeada* lista = this->tabelahash[hashGerado];
    Elemento* elem = new Elemento(chave);
    printf("criei os elementos dos caras\n");
    lista->inserir(elem);
    printf("sai da inserelista\n");
}

meuhash::~meuhash(){}
#include <stdlib.h>
#include <stdio.h>

class Elemento{
    public:
        int valor;
        Elemento* proximo;

        Elemento(int valorRecebido);
        ~Elemento();
};


Elemento::Elemento(int valorRecebido){
    valor = valorRecebido;
    proximo = NULL;
}


class Encadeada{
    public:
        
        Elemento* primeiro;     
        int ocupacao;

        Encadeada();

        void inserir(Elemento* elem);

        int buscar(int valorRecebido);

        int remover(Elemento* elem);

        ~Encadeada();
};

//Construtor Encadeada
Encadeada::Encadeada(){
    primeiro = NULL;
    ocupacao = 0;
}

void Encadeada::inserir(Elemento* elem){
    if(primeiro==NULL){
        primeiro = elem;
        ocupacao += 1;
        printf("Inserido na cabeca\n");
    }else{
        elem->proximo = primeiro;
        primeiro = elem;
        printf("Inserido no inicio\n");
        ocupacao += 1;
        printf("tamanho atual: %d\n",ocupacao);
    }
}

int Encadeada::buscar(int valorRecebido){
    Elemento* elementoAux =  primeiro;
    int retorno = 0;

    while(elementoAux != NULL){
        if(elementoAux->valor == valorRecebido){
            retorno = 1;
        }

        elementoAux = elementoAux->proximo;          
    }

    return retorno;
}
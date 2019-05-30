#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

char nome[256];
volatile int n;
#define LOOPS 100
#define NTHREADS 5

static const char * unidades[]  = { "Zero", "Um", "Dois", "Tres", "Quatro", "Cinco", "Seis", "Sete", "Oito", "Nove" };
static const char * dez_vinte[] = { "", "Onze", "Doze", "Treze", "Quatorze", "Quinze", "Dezesseis", "Dezessete", "Dezoito", "Dezenove" };
static const char * dezenas[]   = { "", "Dez", "Vinte", "Trinta", "Quarenta", "Cinquenta", "Sessenta", "Setenta", "Oitenta", "Noventa" };
static const char * centenas[]  = { "", "Cento", "Duzentos", "Trezentos", "Quatrocentos", "Quinhentos", "Seiscentos", "Setecentos", "Oitocentos", "Novecentos" };

char * strcatb( char * dst, const char * src )
{
   size_t len = strlen(src);
   memmove( dst + len, dst, strlen(dst) + 1 );
   memcpy( dst, src, len );
   return dst;
}



// Modifique esta funcao para rodar constantemente, esperando por alguma thread geraNumeros avise que tem um novo numero para ser escrito por extenso.
// Apos a escrita na variavel nome, a thread deve voltar a esperar por uma nova requisicao
void* porExtenso(void*arg){
//   while(1){
   int c = n / 100;
   int d = n / 10 - c * 10;
   int u = n - (n / 10) * 10;
   int dv = d * 10 + u;
   if( n < 10 )
      return nome;

   if ( (dv > 10) && (dv < 20) )
   {
      strcpy( nome, dez_vinte[ dv - 10 ] );
   }
   else
   {
      if( u == 0 )
      {
         strcpy( nome, dezenas[ d ] );
      }
      else
      {
         strcatb( nome, " e " );
         strcatb( nome, dezenas[d] );
      }
   }

   if( n < 100 )
      return nome;

   if( (d == 0) && ( u == 0 ) )
   {
      if( c == 1 )
         strcpy( nome, "Cem" );
      else
         strcpy( nome, centenas[c] );
   }
   else
   {
      strcatb( nome, " e " );
      strcatb( nome, centenas[c] );
   }
//   }
}

void geraNumeros(void* arg){
   int id = *((int*)arg),i;
   for(i=0;i<LOOPS;i++){
      n = rand()%1000;
      // Avisa a thread porExtenso que pode escrever o numero por extenso
      printf("Thread %d Numero %d:%s\n",id,i,nome);
   }
}


int main(){
   int i;
   pthread_t p[NTHREADS],ext;

   /*Exemplo de funcionamento de porExtenso*/
   n=111;
   porExtenso(NULL);
   printf("%s\n",nome);
   /************* Geracao de threads ****************/
/*
   pthread_create(&ext,NULL,porExtenso,NULL);
   for(i=0;i<NTHREADS;i++){
      pthread_create(&p[i];NULL,geraNumero,(void*)&i);
   }

   for(i=0;i<NTHREADS;i++){
      pthread_join(&p[i];NULL);
   }*/

}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

char nome[256];
volatile int n;
int ok = 1;
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


typedef struct __synchronizer_t {
    pthread_mutex_t lock;
    pthread_cond_t cond;
    int done;
} synchronizer_t;

synchronizer_t s;

void signal_init(synchronizer_t *s) {
    pthread_mutex_init(&s->lock, NULL);
    pthread_cond_init(&s->cond, NULL);
    s->done = 0;
}

void signal_done(synchronizer_t *s) {
    pthread_mutex_lock(&s->lock);
    s->done = 1;
    pthread_cond_signal(&s->cond);
    pthread_mutex_unlock(&s->lock);
}

void signal_wait(synchronizer_t *s) {
    pthread_mutex_lock(&s->lock);
    while (s->done == 0)
	   pthread_cond_wait(&s->cond, &s->lock);
    pthread_mutex_unlock(&s->lock);
}


// Modifique esta funcao para rodar constantemente, esperando por alguma thread geraNumeros avise que tem um novo numero para ser escrito por extenso.
// Apos a escrita na variavel nome, a thread deve voltar a esperar por uma nova requisicao
void* porExtenso(void*arg){
  while(ok==1){
   signal_wait(&s);
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
   }
}

void* geraNumeros(void* arg){
   int id = *((int*)arg),i;
   for(i=0;i<LOOPS;i++){
      n = rand()%1000;
      signal_done(&s);
      printf("Thread %d Numero %d:%s\n",id,i,nome);
   }
}


int main(){
   int i;
   pthread_t p[NTHREADS],ext;
   signal_init(&s);

   pthread_create(&ext,NULL,porExtenso,NULL);
   for(i=0;i<NTHREADS;i++){
      pthread_create(&p[i],NULL,geraNumeros,(void*)&i);
   }

   for(i=0;i<NTHREADS;i++){
      pthread_join(p[i],NULL);
      if(i==0){
         pthread_join(ext,NULL);
         ok = 0;
      }
   }

}

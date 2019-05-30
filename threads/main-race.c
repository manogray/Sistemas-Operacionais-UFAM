#include <stdio.h>

#include "mythreads.h"

int balance = 0;

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;

void* worker(void* arg) {
    pthread_mutex_lock(&m1);
    balance++; // unprotected access
    pthread_mutex_unlock(&m1); 
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    Pthread_create(&p, NULL, worker, NULL);
    //pthread_mutex_lock(&m1);
    balance++; // unprotected access
    //pthread_mutex_unlock(&m1);
    Pthread_join(p, NULL);
    return 0;
}

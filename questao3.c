#include<stdio.h>
#include<semaphore.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define MAXINTERACOES 20
#define MAXBUFFER 10

int buffer[MAXBUFFER];
int ultimo = 0; 
int primeiro  = 0;
int itens = 0;

void escreve(int valor) {
    buffer[ultimo] = valor;    
    ultimo = (ultimo + 1) % MAXBUFFER; }

int le() {
    int tmp;
    
    if (itens==0) 
       return -1; 
  
    tmp = buffer[primeiro];   
    primeiro = (primeiro + 1) % MAXBUFFER;   
    return tmp;
}

void *produtor1(void *arg) {
    int i;
    for (i = 0; i < MAXINTERACOES/2; i++) {  
        usleep( 1000.0 * (float)random()/RAND_MAX);  
        itens++;
        escreve(i);                                      
    }
}

void *produtor2(void *arg) {
    int i;
    for (i = MAXINTERACOES/2; i < MAXINTERACOES; i++) { 
        usleep( 1000.0 * (float)random()/RAND_MAX); 
        itens++;  
        escreve(i);
    }
}

void *consumidor(void *arg) {
    int i, item;
    for (i = 0; i < MAXINTERACOES; i++) {
        item = le();
        if (item != -1)  {
           itens--;
           usleep( 3000.0 * (float)random()/RAND_MAX);
           printf("\nConsumidor: %d - Itens restantes no buffer: %d", item, itens);
        }
        else {
           printf("\nConsumidor: sem item para consumir");
           i--; /* volta o contador de interacoes */
        }
    }
}


int main(int argc, char *argv[]) {
    int i;
    pthread_t pid1, pid2, cid; 
 
    pthread_create(&pid1, NULL, produtor1, NULL); 
    pthread_create(&pid2, NULL, produtor2, NULL); 
    pthread_create(&cid, NULL, consumidor, NULL); 

    pthread_join(pid1, NULL); 
    pthread_join(pid2, NULL); 
    pthread_join(cid, NULL); 

    printf("\n\n");

    return 0;


}
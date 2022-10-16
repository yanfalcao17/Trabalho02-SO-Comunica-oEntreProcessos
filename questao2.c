#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<limits.h>

#define TRUE 1;
#define FALSE 0;
#define GATOS 10;
#define CACHORROS 10;
pthread_mutex_t salaDeDescanso;
int cachorroNaSala;
int gatoNaSala;

// assinaturas das funções

void dogWantsToEnter(void);
void catWnatsToEnter(void);
void dogLeaves(void);
void catLeaves(void);
void salaDeRepouso(void);

// funções

void dogLeaves() {
    if (cachorroNaSala != 0) {
        cachorroNaSala = cachorroNaSala - 1;
    }
    else {
        print("não há cachorros na sala");
    }
}

void catLeaves() {
    if (gatoNaSala != 0) {
        gatoNaSala = gatoNaSala - 1;
    }
    else {
        print("não há gatos na sala");
    }
}

void dogWantsToEnter(void){
    while (TRUE) {
        
        pthread_mutex_lock(&salaDeDescanso);
        cachorroNaSala = cachorroNaSala + 1;

        salaDeRepouso();
        printf("cachoros presentes");
        dogLeaves();

        if (cachorroNaSala == 0)
        {
            pthread_mutex_unlock(&salaDeDescanso);
        }
    }
}

void catWantsToEnter(void){
    while (TRUE) {
        
        pthread_mutex_lock(&salaDeDescanso);
        gatoNaSala = gatoNaSala + 1;

        salaDeRepouso();
        printf("gatos presentes");
        catLeaves();

        if (gatoNaSala == 0)
        {
            pthread_mutex_unlock(&salaDeDescanso);
        }
    }
}

int main()
{
    pthread_t numeroDeGatos[GATOS], numeroDeCachorros[CACHORROS];
	pthread_mutex_init(&salaDeDescanso, NULL);
    int i;


	for (int i = 0; i < GATOS; i++) {
		pthread_create(&numeroDeGatos[i], NULL, (void *)catWantsToEnter, NULL);
	}
	for (int i = 0; i < CACHORROS; i++) {
		pthread_create(&numeroDeCachorros[i], NULL, (void *)dogWantsToEnter, NULL);
	}

	for (int i = 0; i < GATOS; i++) {
		pthread_join(numeroDeGatos[i], NULL);
	}
	for (int i = 0; i < CACHORROS; i++) {
		pthread_join(numeroDeCachorros[i], NULL);
	}

    return 0;
}

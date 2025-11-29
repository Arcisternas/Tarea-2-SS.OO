#ifndef BARRERA_H
#define BARRERA_H

#include <pthread.h>

typedef struct barrera {
	int count;
	int N;
	int etapa;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
} barrera_t;

int barrera_inicializar(barrera_t *b, int total);

int barrera_destruir(barrera_t *b);

int barrera_wait(barrera_t *b);

#endif


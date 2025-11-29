#include "barrera.h"
#include <stdlib.h>
#include <errno.h>

int barrera_inicializar(barrera_t *b, int N) {
	if (!b || N <= 0) {
		errno = EINVAL;
		return -1;
	}
	b -> count = 0;
	b -> N = N;
	b -> etapa = 0;
	if (pthread_mutex_init(&b->mutex, NULL) != 0) {
		return -1;
	}
	if (pthread_cond_init(&b->cond, NULL) != 0) {
		pthread_mutex_destroy(&b->mutex);
		return -1;
	}
	return 0;
}

int barrera_destruir(barrera_t *b) {
	if (!b) {
		errno = EINVAL;
		return -1;
	}
	int err = 0;
	if (pthread_mutex_destroy(&b->mutex) != 0) err = -1;
	if (pthread_cond_destroy(&b->cond) != 0) err = -1;
	return err;
}

int barrera_wait(barrera_t *b) {
	if (!b) {
		errno = EINVAL;
		return -1;
	}

	if (pthread_mutex_lock(&b->mutex) != 0) return -1;

	int mi_etapa = b->etapa;
	b->count++;
	if (b->count == b->N) {
		b->etapa++;
		b->count = 0;
		if (pthread_cond_broadcast(&b->cond) != 0) {
			pthread_mutex_unlock(&b->mutex);
			return -1;
		}
		pthread_mutex_unlock(&b->mutex);
		return 0;
	}

	while (mi_etapa == b->etapa) {
		if (pthread_cond_wait(&b->cond, &b->mutex) != 0) {
			pthread_mutex_unlock(&b->mutex);
			return -1;
		}
	}

	pthread_mutex_unlock(&b->mutex);
	return 0;
}


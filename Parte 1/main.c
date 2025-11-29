#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include "barrera.h"

typedef struct thread_arg {
    int tid;
    int E;
    barrera_t *b;
} thread_arg_t;

static void *worker(void *arg) {
    thread_arg_t *a = (thread_arg_t *)arg;
    int tid = a->tid;
    int E = a->E;
    barrera_t *b = a->b;

    unsigned int seed = (unsigned int)time(NULL) ^ (unsigned int)tid;

    for (int e = 0; e < E; ++e) {
        // trabajo simulado con jitter (nanosleep)
        {
            long usec = (long)((rand_r(&seed) % 100000) + 10000);
            struct timespec ts;
            ts.tv_sec = 0;
            ts.tv_nsec = usec * 1000L;
            nanosleep(&ts, NULL);
        }

        printf("[%d] esperando en etapa %d\n", tid, e);
        fflush(stdout);

        if (barrera_wait(b) != 0) {
            fprintf(stderr, "[%d] error en barrera_wait\n", tid);
            pthread_exit(NULL);
        }

        printf("[%d] paso barrera en etapa %d\n", tid, e);
        fflush(stdout);
    }

    return NULL;
}

int main(int argc, char **argv) {
    int N = 5;
    int E = 4;

    if (argc >= 2) N = atoi(argv[1]);
    if (argc >= 3) E = atoi(argv[2]);
    if (N <= 0) N = 5;
    if (E <= 0) E = 4;

    pthread_t *ths = malloc(sizeof(pthread_t) * N);
    thread_arg_t *args = malloc(sizeof(thread_arg_t) * N);
    if (!ths || !args) {
        perror("malloc");
        return 1;
    }

    barrera_t b;
    if (barrera_inicializar(&b, N) != 0) {
        fprintf(stderr, "No se pudo inicializar la barrera\n");
        return 1;
    }

    for (int i = 0; i < N; ++i) {
        args[i].tid = i;
        args[i].E = E;
        args[i].b = &b;
        if (pthread_create(&ths[i], NULL, worker, &args[i]) != 0) {
            perror("pthread_create");
            // intentar continuar creando menos hilos
        }
    }

    for (int i = 0; i < N; ++i) {
        pthread_join(ths[i], NULL);
    }

    barrera_destruir(&b);

    free(ths);
    free(args);

    return 0;
}
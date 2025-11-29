#include <stdio.h>
#include <stdlib.h>
#include "Algoritmos.h"

// algoritmo de reemplazo de pagina tipo reloj
int clockReplacement(int references[], int n, int frames, int *marcos, int *useBit, int *fallosPorReferencia) {
    int pageFaults = 0; // contador de fallos de pagina
    int pointer = 0;    // puntero circular para el algoritmo de reloj
    int count = 0;      // cantidad de marcos ocupados

    // inicializar marcos y bits de uso
    for (int i = 0; i < frames; i++) {
        marcos[i] = -1; // -1 indica marco vacio
        useBit[i] = 0;  // bit de uso en 0
    }

    // procesar cada referencia de pagina
    for (int i = 0; i < n; i++) {
        int page = references[i];
        int found = 0;
        int marco = -1;
        // buscar si la pagina ya esta en los marcos
        for (int j = 0; j < count; j++) {
            if (marcos[j] == page) {
                found = 1;
                useBit[j] = 1; // marcar como usada
                marco = j;
                break;
            }
        }
        // si no esta es fallo de pagina
        if (!found) {
            pageFaults++;
            if (count < frames) {
                // hay espacio libre en los marcos
                marcos[count] = page;
                useBit[count] = 1;
                marco = count;
                count++;
            } else {
                // buscar marco con bit de uso en 0 
                while (useBit[pointer] == 1) {
                    useBit[pointer] = 0;
                    pointer = (pointer + 1) % frames;
                }
                marcos[pointer] = page;
                useBit[pointer] = 1;
                marco = pointer;
                pointer = (pointer + 1) % frames;
            }
        }
        // registrar si fue fallo o hit
        fallosPorReferencia[i] = found ? 0 : 1;
    }
    return pageFaults;
}
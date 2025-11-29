
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Algoritmos.h" 


int main(int argc, char *argv[]) {
    int frames, pageSize; // numero de marcos y tamano de pagina
    char *filename; // nombre del archivo de trazas
    int verbose = 0; // flag para modo vrbose

    // validar argumentos
    if (argc < 4 || argc > 5) {
        printf("Uso: %s Nmarcos tamanoMarco [--verbose] traza.txt\n", argv[0]);
        return 1;
    }

    frames = atoi(argv[1]);
    pageSize = atoi(argv[2]);
    filename = argv[argc - 1];
    if (argc == 5 && strcmp(argv[3], "--verbose") == 0) {
        verbose = 1;
    }

    // validar que el tamano de pagina sea una potencia de 2
    if (pageSize <= 0 || (pageSize
         & (pageSize - 1)) != 0) {
        printf("Error: El tamano de marco debe ser potencia de 2.\n");
        return 1;
    }

    // abrir el archivo de trazas
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error al abrir el archivo: %s\n", filename);
        return 1;
    }

    // calcular mascara y bits para extraer el offset y el numero de pagina virtual
    int MASK = pageSize - 1;
    int b = 0;
    int tmp = pageSize;
    while (tmp >>= 1) ++b;

    // variables para el control del algoritmo 
    int pointer = 0, count = 0, referencias = 0;

    // buffer para leer el archivo
    char linea[64];

    // procesar cada linea del archivo de trazas y almacenar los datos
    unsigned int DV_refs[10000];
    int npv_refs[10000];
    int offset_refs[10000];
    int total_refs = 0;
    while (fgets(linea, sizeof(linea), file)) {
        unsigned int DV;
        linea[strcspn(linea, "\r\n")] = 0;
        if (strlen(linea) == 0) continue;
        if (linea[0] == '0' && (linea[1] == 'x' || linea[1] == 'X')) {
            sscanf(linea, "%x", &DV);
        } else {
            sscanf(linea, "%u", &DV);
        }
        int offset = DV & MASK;
        int npv = DV >> b;
        DV_refs[total_refs] = DV;
        npv_refs[total_refs] = npv;
        offset_refs[total_refs] = offset;
        total_refs++;
    }
    fclose(file);

    // buffers para el algoritmo
    int marcos[frames];
    int useBit[frames];
    int fallosPorReferencia[10000];
    // ejecutar el algoritmo de reemplazo de pagina reloj
    int fallos = clockReplacement(npv_refs, total_refs, frames, marcos, useBit, fallosPorReferencia);

    // imprimr tabla en modo verbose
    if (verbose) {
        printf("%-12s %-6s %-6s %-8s %-6s %-10s\n", "DV", "npv", "offset", "HIT/FALLO", "marco", "DF");
        printf("---------------------------------------------------------------\n");
        int pointer = 0, count = 0;
        for (int i = 0; i < total_refs; i++) {
            int marco = -1;
            int hit = 0;
            // buscar si la pagina esta en los marcos
            for (int j = 0; j < count; j++) {
                if (marcos[j] == npv_refs[i]) {
                    marco = j;
                    hit = 1;
                    break;
                }
            }
            if (!hit) {
                if (count < frames) {
                    marco = count;
                    count++;
                } else {
                    while (useBit[pointer] == 1) {
                        useBit[pointer] = 0;
                        pointer = (pointer + 1) % frames;
                    }
                    marco = pointer;
                    pointer = (pointer + 1) % frames;
                }
            }
            int DF = (marco << b) | offset_refs[i];
            printf("%-12u %-6d %-6d %-8s %-6d %-10u\n", DV_refs[i], npv_refs[i], offset_refs[i], hit ? "HIT" : "FALLO", marco, DF);
        }
    }
    // imprimir totales
    printf("Referencias: %d, Fallos de pagina: %d, Tasa de fallos: %.2f\n", total_refs, fallos, (float)fallos/total_refs);
    return 0;
}

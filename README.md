# Tarea-2-SS.-OO.


# Ejercicio 2

Compilación sencilla:
```sh
gcc "Ejercicio 2/src/main.c" "Ejercicio 2/src/Algoritmos.c" -I"Ejercicio 2/include" -o Ejercicio2
```
o, utilizando make:
```sh
make -f "Ejercicio 2/Makefile"
```

## Ejecución:
```sh
./Ejercicio2 {Numero marcos} {Tamano marco} "Ejercicio 2/referencias/{archivo de traza}"
```
o para ver el detalle paso a paso:
```sh
./Ejercicio2 {Numero marcos} {Tamano marco} [--verbose] "Ejercicio 2/referencias/{archivo de traza}"
```
- Numero marcos: numero de marcos de pagina a utilizar (numero natural)
- Tamano marco: tamano de cada marco a utilizar (numero natural potencia de 2)
- archivo de traza: nombre del archivo con las referencias a probar

# Tarea-2-SS.-OO.
En este repositorio se encuentra todo el código relacionado a la tarea n°2 de la asignatura Sistemas Operativos.
Integrantes: Ariel Cisternas Bustos y Felipe Tilleria Morales. 

## Parte 1 — Barrera reutilizable

Instrucciones para compilar y ejecutar la implementación de la barrera reutilizable (carpeta `Parte 1`).

Compilar:
```sh
cd "Parte 1"
make
```

Limpiar:
```sh
cd "Parte 1"
make clean
```

Ejecutar (si no hay argumentos, usa valores por defecto N=5, E=4):
```sh
cd "Parte 1"
./main [N] [E]
# ejemplo: 8 hebras, 6 etapas
./main 8 6
```

Salida esperada:
- Cada etapa `e` mostrará varias líneas de la forma `[{tid}] esperando en etapa e` (en cualquier orden),
  seguidas sólo después por las líneas `[{tid}] paso barrera en etapa e` para todos los `tid`.

# Ejercicio 2

## Compilación sencilla:
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
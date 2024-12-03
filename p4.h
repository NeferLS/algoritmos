#define TAM 256000
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>

#define intercambiar(a, b) { int temp = a; a = b; b = temp; }

struct monticulo {
    int ultimo;
    int vector[TAM];
};

typedef struct monticulo * pmonticulo;


void iniMonticulo(pmonticulo m);
void flotar(pmonticulo m, int i);
void hundir(pmonticulo m, int i);
void insertarMonticulo(pmonticulo m, int x);
void quitarMenor(pmonticulo m);
int consultarMenor(const pmonticulo m);
void crearMonticulo(pmonticulo m, int v [], int n);
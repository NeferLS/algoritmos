#define TAM 256000
#include <stdio.h>
#define intercambiar(a, b) { \
    typeof(a) temp = a; \
    a = b; \
    b = temp; \
}

struct monticulo {
    int ultimo;
    int vector[TAM];
};

typedef struct monticulo * pmonticulo;


void iniMonticulo(pmonticulo m);
void insertarMonticulo(pmonticulo m, int x);
void quitarMenor(pmonticulo m);
int consultarMenor(const pmonticulo m);
void crearMonticulo(pmonticulo m, int v [], int n);
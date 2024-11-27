#include "p4.h"

void iniMonticulo(pmonticulo m){
    m->ultimo = 1;
}



void flotar(pmonticulo m, int i){
    while ((i > 1) && (m->vector[i/2] < m->vector[i])){
        intercambiar(m->vector[i/2],m->vector[i]);
        i = i/2;
    }
}

void insertarMonticulo(pmonticulo m, int x){
    if(m->ultimo == TAM){
        printf("Error: Monticulo lleno");
    } else{
        m->ultimo = m->ultimo +1;
        m->vector[m->ultimo] = x;
        flotar(m, m->ultimo);
    }
}
void quitarMenor(pmonticulo m){
    
}
int consultarMenor(const pmonticulo m);
void crearMonticulo(pmonticulo m, int v [], int n);
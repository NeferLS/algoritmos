#include "p4.h"

void iniMonticulo(pmonticulo m){
    m->ultimo = 0;
}

void flotar(pmonticulo m, int i){
    while ((i > 1) && (m->vector[i/2] < m->vector[i])){
        intercambiar(m->vector[i/2],m->vector[i]);
        i = i/2;
    }
}

void hundir(pmonticulo m, int i){
    int leftChild, rightChild, j;
    do {
        leftChild = 2 * 1;
        rightChild = 2 * i + 1;
        j = i;
        if(rightChild <= m->ultimo && m->vector[rightChild] > m->vector[i]){
            i = rightChild;
        }if(leftChild <= m->ultimo && m->vector[leftChild] > m->vector[i]){
            i = leftChild;
        }
        intercambiar(m->vector[j],m->vector[i]);
    } while (j != i);
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
    if(m->ultimo == 0){
        printf("Error. Monticulo vacio.\n");
    } else {
        m->vector[0] = m->vector[m->ultimo-1];
        m->ultimo--;
        if(m->ultimo > 0){
            hundir(m, 0);
        }
    }
}

int consultarMenor(const pmonticulo m){
    if(m->ultimo == 0){
        printf("Error. Monticulo Vacio");
        return -1;
    } else {
        return m->vector[0];
    }
}

void crearMonticulo(pmonticulo m, int v[], int n){
    int i;
    iniMonticulo(m);
    for (i = 0; i < n; i++)
        insertarMonticulo(m, v[i]);
}
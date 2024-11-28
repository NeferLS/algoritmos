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
    int hijo, tmp = m->vector[i];
    while ((hijo = 2*i) <= m->ultimo) {
        if (hijo < m->ultimo && m->vector[hijo+1] > m->vector[hijo])
            hijo++;
        if (tmp >= m->vector[hijo])
            break;
        m->vector[i] = m->vector[hijo];
        i = hijo;
    }
    m->vector[i] = tmp;
}

void insertarMonticulo(pmonticulo m, int x){
    if(m->ultimo >= TAM -1){
        printf("Error: Monticulo lleno\n");
        return;
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
        m->vector[1] = m->vector[m->ultimo];
        m->ultimo--;
        if(m->ultimo > 1){
            hundir(m, 1);
        }
    }
}

int consultarMenor(const pmonticulo m){
    if(m->ultimo == 0){
        printf("Error. Monticulo Vacio");
        return -1;
    } else {
        return m->vector[1];
    }
}

void crearMonticulo(pmonticulo m, int v[], int n){
    int i;
    iniMonticulo(m);
    for (i = 0; i < n && i < TAM - 1; i++)
        insertarMonticulo(m, v[i]);
}
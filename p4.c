/*
* Autores:
*  --> Nefer Labrada Suarez
*  --> Pablo Castro Freire
*  --> Adrián Formigo Gómez
*
* Grupo 3.3
*/

#include "p4.h"

// Gestión del tiempo:

double microsegundos(){
    struct timeval t;
    gettimeofday(&t,NULL);
    return t.tv_sec * 1000000.0 + t.tv_usec;
}

double fixSmallTimes(pmonticulo m, int n,
                     void (*func)(pmonticulo, int *, int)) {
    int i, k = 1000;
    double init, end, time;
    int *dummyArray = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++) {
        dummyArray[i] = rand() % 1000000;
    }

    init = microsegundos();
    for (i = 0; i < k; i++) {
        iniMonticulo(m);
        func(m, dummyArray, n);
    }
    end = microsegundos();

    free(dummyArray);
    time = (end - init) / k;
    return time;
}

void auxInsertarMonticulo(pmonticulo m, int *v, int n) {
    for (int i = 0; i < n; i++) {
        insertarMonticulo(m, v[i]);
    }
}

double timeInsertarMonticulo(int n, int *ajustado){
    if (n > TAM -1) n = TAM -1;
    pmonticulo m = (pmonticulo)malloc(sizeof(struct monticulo));
    int *v = (int *)malloc(n * sizeof(int));
    double init, end, time;
    int i;
    *ajustado = 0;

    // Crear el vector aleatorio antes de medir
    for (i = 0; i < n; i++) {
        v[i] = rand() % 1000000;
    }

    iniMonticulo(m);

    init = microsegundos();
    for (i = 0; i < n; i++){
        insertarMonticulo(m, v[i]);
    }
    end = microsegundos();
    time = end-init;
    if (time < 500){
        time = fixSmallTimes(m, n, auxInsertarMonticulo);
        *ajustado = 1;
    }
    
    free(m);
    free(v);
    return time;
}

double timeCrearMonticulo(int n, int *ajustado){
    if (n > TAM -1) n = TAM -1;
    pmonticulo m = (pmonticulo)malloc(sizeof(struct monticulo));
    int *v = (int *)malloc(n * sizeof(int));
    double init, end,time ;
    int i;
    *ajustado = 0;

    for (i = 0; i < n; i++)
        v[i] = rand() % 1000000; // elementos aleatorios

    init = microsegundos();
    crearMonticulo(m, v, n);
    end = microsegundos();
    time = end-init;
    if (time < 500){
        time = fixSmallTimes(m, n, crearMonticulo);
        *ajustado = 1;
    }
    free(m);
    free(v);
    return time;
}

// Cotas:

double n(int n) { return n; }
double nlogn(int n) { return n*log(n); }
double n2(int n) { return n * n; }
double n0_5(int n) { return pow(n,0.5); }


// Printeo de tablas:

void printBothHeaps(double (*tiempometodo)(int, int *), double (*fn)(int),
                     double (*gn)(int), double (*hn)(int))
{
    int n;
    
    printf("\nTabla de %s:\n", (tiempometodo == timeInsertarMonticulo)
             ? "Insertar monticulo" : "Crear monticulo");
    printf("     n    |   Time (µs)  |   t(n)/f(n)  |   t(n)/g(n)  "
            "|   t(n)/h(n)\n");
    printf("-----------------------------------------------------------"
            "-------------\n");

    for (n = 500; n <= 32000; n = n*2) {
        int ajustado = 0;
        double t = tiempometodo(n, &ajustado);
        double f_n = fn(n);
        double g_n = gn(n);
        double h_n = hn(n);

        printf("%s%8d | %12.4f | %12.8f | %12.8f | %12.9f\n", 
                ajustado ? "*" : " ", n, t, t/f_n, t/g_n, t/h_n);
    }

    printf("-----------------------------------------------------------"
            "-------------\n\n");
}


//Main:

int main(){
    srand(time(NULL));
    
    printf("Tablas de Insertar y Crear Monticulo:\n");

    for(int i = 1; i <= 3; i++) {
        printBothHeaps(timeInsertarMonticulo, n, nlogn, n2); //en 32000 ocurre una anomalía siempre. REVISAR CÓDIGO
        printBothHeaps(timeCrearMonticulo, n0_5, n, n2); //sin fallos
    }   
}
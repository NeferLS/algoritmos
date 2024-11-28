#include "p4.h"

double microsegundos(){
    struct timeval t;
    gettimeofday(&t,NULL);
    return t.tv_sec * 1000000.0 + t.tv_usec;
}

double fixSmallTimes(pmonticulo m, int n, void (*func)(pmonticulo, int *, int)) {
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
    double init, end, time;
    int i, x;
    *ajustado = 0;

    iniMonticulo(m);
    init = microsegundos();
    for (i = 0; i < n; i++){
        x = rand() % 1000000; //creamos vectores aleatorios
        insertarMonticulo(m, x);
    }
    end = microsegundos();
    time = end-init;
    if (time < 500){
        time = fixSmallTimes(m, n, auxInsertarMonticulo);
        *ajustado = 1;
    }
    
    free(m);
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

void testBothHeaps(double (*timeInsert)(int, int *), double (*timeCreate)(int, int *),
                   double (*fn)(int), double (*gn)(int), double (*hn)(int)) {
    int sizes[] = {500, 1000, 2000, 4000, 8000, 16000, 32000};
    int num_tries = sizeof(sizes) / sizeof(int);

    printf("Comparacion para insertarMonticulo:\n");
    printf("n\tTiempo\t\tT/(n)\t\tT/nlog(n)\tT/n^2\t\n");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < num_tries; i++) {
        int ajustado = 0;
        int n = sizes[i];

        double t = timeInsert(n, &ajustado);
        double f_n = fn(n);
        double g_n = gn(n);
        double h_n = hn(n);

        printf("%s%d\t%.6f\t%.6f\t%.6f\t%.6f\t\n",ajustado ? "*" : " ", n, t, t/f_n, t/g_n, t/h_n);
    }

    printf("\nComparacion para crearMonticulo:\n");
    printf("n\tTiempo\t\tT/(n)\t\tT/nlog(n)\tT/n^2\t\n");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < num_tries; i++) {
        int ajustado = 0;
        int n = sizes[i];

        double t = timeCreate(n, &ajustado);
        double f_n = fn(n);
        double g_n = gn(n);
        double h_n = hn(n);

        printf("%s%d\t%.6f\t%.6f\t%.6f\t%.6f\t\n",ajustado ? "*" : " ", n, t, t/f_n, t/g_n, t/h_n);
    }
}

double n(int n) { return n; }
double nlogn(int n) { return n*log(n); }
double n2(int n) { return n * n; }

int main(){
    srand(time(NULL));
    
    printf("Pruebas de insertarMonticulo y crearMonticulo:\n");
    testBothHeaps(timeInsertarMonticulo, timeCrearMonticulo, n, nlogn, n2);

}
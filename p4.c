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

    init = microsegundos();
    for (i = 0; i < k; i++) {
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
    if (n > TAM) n = TAM;
    pmonticulo m = (pmonticulo)malloc(sizeof(struct monticulo));
    clock_t init, end;
    double time;
    int i, x;
    iniMonticulo(m);
    init = microsegundos();
    for (i = 0; i < n; i++){
        x = rand() % 1000000; //creamos vectores aleatorios
        insertarMonticulo(m, x);
    }
    end = microsegundos();
    time = ((double)(end-init));
    if (time < 500){
        time = fixSmallTimes(m, n, auxInsertarMonticulo);
        *ajustado = 1;
    }
    
    free(m);
    return time;
}

double timeCrearMonticulo(int n, int *ajustado){
    if (n > TAM) n = TAM;
    pmonticulo m = (pmonticulo)malloc(sizeof(struct monticulo));
    int *v = (int *)malloc(n * sizeof(int));
    clock_t init, end;
    double time;
    int i;

    for (i = 0; i < n; i++)
        v[i] = rand() % 1000000; // elementos aleatorios

    init = clock();
    crearMonticulo(m, v, n);
    end = clock();
    time = ((double)(end-init));
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

    printf("n\tTime Insert\tAdjust\tTime Create\tAdjust\n");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < num_tries; i++) {
        int ajustadoInsert = 0, ajustadoCreate = 0;
        int n = sizes[i];

        double tInsert = timeInsert(n, &ajustadoInsert);
        double tCreate = timeCreate(n, &ajustadoCreate);

        printf("%d\t%.6f\t%s\t%.6f\t%s\n", n, tInsert, ajustadoInsert ? "*" : " ",
               tCreate, ajustadoCreate ? "*" : " ");
    }

    printf("\nComparaciones:\n");
    printf("t(n)/f(n), t(n)/g(n), t(n)/h(n)\n");
    for (int i = 0; i < num_tries; i++) {
        int ajustado = 0;
        int n = sizes[i];

        double t = timeInsert(n, &ajustado);
        double f_n = fn(n);
        double g_n = gn(n);
        double h_n = hn(n);

        printf("%d\t%.6f\t%.6f\t%.6f\n", n, t / f_n, t / g_n, t / h_n);
    }
}

double logn(int n) { return n > 0 ? log(n) : 0; }
double nlogn(int n) { return n * logn(n); }
double n2(int n) { return n * n; }

int main(){
    srand(time(NULL));
    
    printf("Pruebas de insertarMonticulo y crearMonticulo:\n");
    testBothHeaps(timeInsertarMonticulo, timeCrearMonticulo, logn, nlogn, n2);

}
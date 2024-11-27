#include "p4.h"

double microsegundos(){
    struct timeval t;
    gettimeofday(&t,NULL);
    return t.tv_sec * 1000000.0 + t.tv_usec;
}

double fixSmallTimes(pmonticulo m, int n, void (*func)(int)){
    int i, j, x, k = 1000; //n de iteraciones
    double init, end, *time;

    init = microsegundos();
    for (i = 0; i < k; i++){
        for (j = 0; j < n; j++){
            x = rand() % 1000000; //creamos vectores aleatorios
            func(n);
        }
    }
    end = microsegundos();
    *time = (init - end) / k;
    return *time;
}

double timeInsertarMonticulo(int n){
    pmonticulo m = (pmonticulo)malloc(sizeof(struct monticulo));
    clock_t init, end;
    double *time;
    int i, x;
    iniMonticulo(m);
    init = microsegundos();
    for (i = 0; i < n; i++){
        x = rand() % 1000000; //creamos vectores aleatorios
        insertarMonticulo(m, x);
    }
    end = microsegundos();
    *time = ((double)(end-init));
    if (*time < 500){
        //fixSmallTimes(m,n, insertarMonticulo(n));
    }
    
    free(m);
    return *time;
}

double timeCrearMonticulo(int n){
    pmonticulo m = (pmonticulo)malloc(sizeof(struct monticulo));
    int *v = (int *)malloc(n * sizeof(int));
    clock_t init, end;
    double time;
    int i, x;

    for (i = 0; i < n; i++)
        v[i] = rand() % 1000000; // elementos aleatorios

    init = clock();
    crearMonticulo(m, v, n);
    end = clock();
    time = ((double)(end-init)) / CLOCKS_PER_SEC;
    free(m);
    free(v);
    return time;
}

void testInsertCreate(int size[], int num_elements){
    int i, n;
    double timeInsert, timeCreate;

    printf("Size\tTime Insert\tTime Create\n");
    for (i = 0; i < num_elements; i++){
        n = size[i]; 
        timeInsert = timeInsertarMonticulo(n);
        timeCreate = timeCrearMonticulo(n);
        printf("%d\t%.6f\t\t%.6f\n", n, timeInsert, timeCreate);
    }
}

int main(){
    srand(time(NULL));
    int sizes[] = {};
}
/*
* Autores:
*  --> Nefer Labrada Suarez
*  --> Pablo Castro Freire
*  --> Adrián Formigo Gómez
*
* Grupo 3.3
*/

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


void inicializar_semilla() {
    srand(time(NULL));
}


// Implementación del Montículo de Mínimos:

void iniMonticulo(pmonticulo m){
    m->ultimo = 0;
}

void flotar(pmonticulo m, int i){
    while ((i > 1) && (m->vector[i/2] > m->vector[i])){
        intercambiar(m->vector[i/2],m->vector[i]);
        i = i/2;
    }
}

void hundir(pmonticulo m, int i){
    int hijo, tmp = m->vector[i];
    while ((hijo = 2*i) <= m->ultimo) {
        if (hijo < m->ultimo && m->vector[hijo+1] < m->vector[hijo])
            hijo++;
        if (tmp <= m->vector[hijo])
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
        m->ultimo++;
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


// Algoritmo de ordenación:

void OrdenarPorMontículos (int v[], int n) {   
    int i;
    pmonticulo m = (pmonticulo)malloc(sizeof(struct monticulo));
    crearMonticulo (m, v, n);
    for (i = 0; i < n; i++) {
        v[i] = consultarMenor(m);
        quitarMenor(m);
    }
    free(m);
}


// Casos:

void ascendente(int v[], int n) {
    int i;
    for (i = 0; i < n; i++)
        v[i] = i;
}

void descendente(int v[], int n) {
    int i;
    for (i = 0; i < n; i++)
        v[i] = n - i - 1;
}

void aleatorio(int v[], int n) {
    int m = 2 * n + 1, i;
    for (i = 0; i < n; i++)
        v[i] = (rand() % m) - n;
}


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
    int i;
    for (i = 0; i < n; i++) {
        insertarMonticulo(m, v[i]);
    }
}

double timeInsertarMonticulo(int n, int *ajustado){
    int i, *v;
    double init, end, time;
    pmonticulo m = (pmonticulo)malloc(sizeof(struct monticulo));

    if (n > TAM -1) n = TAM -1;
    v = (int *)malloc(n * sizeof(int));
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
    int i, *v;
    double init, end, time;
    pmonticulo m = (pmonticulo)malloc(sizeof(struct monticulo));

    if (n > TAM -1) n = TAM -1;
    v = (int *)malloc(n * sizeof(int));
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

// Gestión del tiempo para ordenación de vectores:

void ajuste_tiempo(void (*ini)(int [], int),
                    int v[], int n, double *t_n)
{
    int k = 1000;
    int i;
    double start, end, tiempo_init;

    start = microsegundos();
    for (i = 0; i < k; i++) {
        ini(v, n);  //Solo el tiempo de la inicialización
    }
    end = microsegundos();
    tiempo_init = (end - start) / k; //tiempo tardado en inicializar

    
    start = microsegundos();
    for (i = 0; i < k; i++) {
        OrdenarPorMontículos(v, n);
        ini(v, n);  //restaura el vector para cada ejecución
    }
    end = microsegundos();
    *t_n = (end - start) / k -tiempo_init;  //tiempo promedio de 1000 repet.
}

void medirTiempo(void(*ini)(int[], int),int n,
double *t_n,int *t)
{
    int *v = malloc(n * sizeof(int));
    double start, end;

    ini(v, n);
    start = microsegundos();
    OrdenarPorMontículos(v, n);
    end = microsegundos();

    *t_n = end - start;
    *t = 0;

    if (*t_n < 500) {
        ajuste_tiempo(ini, v, n, t_n);
        *t = 1;  // marca como ajustado
    }
    free(v);
}


// Cotas:

double n_1(int n) { return n; }
double n_log_n(int n) { return n*log(n); }
double n_2(int n) { return n * n; }
double n_0_5(int n) { return pow(n,0.5); }


// Funcion para test y auxiliares:

void imprimir_vector(int v[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d", v[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf("\n");
}

int esta_ordenado(int v[], int n) {
    int i;
    for (i = 1; i < n; i++) {
        if (v[i - 1] > v[i]) {
            return 0; // No está ordenado
        }
    }
    return 1; // Está ordenado
}

void test_ordenacion_monticulos(void (*inicializacion)(int[], int),
                                 const char* caso){
    int n = 7; //tamaño test
    int v[n];

    printf("\nOrdenacion por monticulo con inicializacion %s\n", caso);
    inicializacion(v, n);
    imprimir_vector(v, n);
    printf("ordenado? %d\n", esta_ordenado(v, n));
    printf("ordenando...\n");
    OrdenarPorMontículos(v, n);
    imprimir_vector(v, n);
    printf("ordenado? %d\n\n", esta_ordenado(v, n));
}


// Printeo de tablas:

void printBothHeaps(double (*tiempometodo)(int, int *), double (*fn)(int),
                     double (*gn)(int), double (*hn)(int))
{
    int n, ajustado;
    double t_n, f_n, g_n, h_n;
    
    printf("\n***** Tabla de %s:\n\n", (tiempometodo == timeInsertarMonticulo)
             ? "Insertar monticulo" : "Crear monticulo");
    printf("     n    |   Time (µs)  |   t(n)/f(n)  |   t(n)/g(n)  "
            "|   t(n)/h(n)\n");
    printf("-----------------------------------------------------------"
            "-------------\n");

    for (n = 500; n <= 32000; n = n*2) {
        ajustado = 0;
        t_n = tiempometodo(n, &ajustado);
        f_n = fn(n);
        g_n = gn(n);
        h_n = hn(n);

        printf("%s%8d | %12.4f | %12.8f | %12.8f | %12.9f\n", 
                ajustado ? "*" : " ", n, t_n, t_n/f_n, t_n/g_n, t_n/h_n);
    }

    printf("-----------------------------------------------------------"
            "-------------\n\n");
}

void printResultados(void (*inicializacion)(int [], int),
                     const char* caso, double (*fn)(int), double (*gn)(int),
                     double (*hn)(int)){

    int n, ajustado;
    double t_n, f_n, g_n, h_n;

    printf("\n***** Ordenacion por Monticulo - Caso %s:\n\n", caso);
    printf("     n    |   Time(µs)   |    t(n)/f(n)   |   t(n)/g(n)   "
            "|   t(n)/h(n)\n");
    printf("-----------------------------------------------------------"
            "----------------\n");

    for (n = 500; n <= 32000; n = n*2) {

        f_n = fn(n);
        g_n = gn(n);
        h_n = hn(n);
        
        medirTiempo(inicializacion, n, &t_n, &ajustado);

        printf("%s%8d | %12.4f |   %12.9f |   %11.9f |   %11.9f\n",
                ajustado ? "*" : " ", n, t_n, t_n / f_n, t_n / g_n,
                t_n / h_n);
    }

    printf("-----------------------------------------------------------"
            "----------------\n\n");
}


//Main:

int main(){
    
    int i;
    int rep1 = 1;
    int rep2 = 1;

    inicializar_semilla();
    
    printf("Tablas de Insertar y Crear Monticulo:\n");

    for(i = 0; i < rep1; i++) {
        printBothHeaps(timeInsertarMonticulo, n_1, n_log_n, n_2);
        printBothHeaps(timeCrearMonticulo, n_0_5, n_1, n_2);
    }

    test_ordenacion_monticulos(ascendente, "Ascendente");
    test_ordenacion_monticulos(descendente, "Descendente");
    test_ordenacion_monticulos(aleatorio, "Aleatoria");

    for(i=0; i < rep2; i++) {
        printResultados(ascendente, "Ascendente", n_0_5, n_log_n, n_2);
        printResultados(descendente, "Descendente", n_0_5, n_log_n, n_2);
        printResultados(aleatorio, "Aleatorio", n_0_5, n_log_n, n_2);
    }

    return 0;
}
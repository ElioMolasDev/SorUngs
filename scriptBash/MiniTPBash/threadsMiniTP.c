#include <stdio.h>
#include <pthread.h>
#include <time.h>

void* calculo_aritmetico(void* arg) {
    int contador = 0;
    while (contador < 2147483647) {
        contador++;
    }
    return NULL;
}


int main() {
    pthread_t hilos[5];
    time_t inicio = time(NULL);
    for (int i = 0; i < 5; i++) {
        pthread_create(&hilos[i], NULL, calculo_aritmetico, NULL);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(hilos[i], NULL);
    }
    time_t fin = time(NULL);
    printf("Tiempo total con threads: %ld segundos\n", fin - inicio);
    return 0;
}



#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

// Semáforos
sem_t sem_fotocopiadora;
sem_t sem_bandeja;
sem_t sem_trabajoA;
sem_t sem_trabajoB;
sem_t sem_enfriamiento;
sem_t sem_contadores;

int contador_trabajosB_seguidos = 0;
int trabajosA_espera = 0;
int trabajosB_espera = 0;

void imprimir_estado(const char* dinosaurio, char tipo, int enfriamiento) {
    printf("[Estado] Dinosaurio %s - Tipo %c - Enfriamiento: %s\n",
           dinosaurio, tipo,
           enfriamiento ? "SI" : "NO");
}


void fotocopiar(char tipo, const char* dinosaurio) {
    int tiempo = (tipo == 'A') ? 1 : 4;   //1 para trabajos A, 4 Seg para trabajos B
    printf("%s está fotocopiando un trabajo tipo %c (%d segundos)...\n", 
           dinosaurio, tipo, tiempo);
    sleep(tiempo);
}


void esperar_enfriamiento() {
    printf("La fotocopiadora necesita enfriarse (5 segundos)...\n");
    sleep(5);
    contador_trabajosB_seguidos = 0;
}


void colocar_trabajo_en_bandeja(char tipo, const char* dinosaurio) {
    sem_wait(&sem_bandeja);
    printf("%s está colocando un trabajo tipo %c en la bandeja...\n", dinosaurio, tipo);
    sem_wait(&sem_contadores);
    if (tipo == 'A') {
        trabajosA_espera++;
        sem_post(&sem_trabajoA);
    } else {
        trabajosB_espera++;
        sem_post(&sem_trabajoB);
    }
    sem_post(&sem_contadores);
    
    sem_post(&sem_bandeja);
}


void usar_fotocopiadora(char tipo, const char* dinosaurio) {
    colocar_trabajo_en_bandeja(tipo, dinosaurio);

    if (tipo == 'A') {
        sem_wait(&sem_trabajoA);
    } else {
        sem_wait(&sem_contadores);
            int dar_prioridad_A = (trabajosB_espera > 3 && trabajosA_espera > 0);
        sem_post(&sem_contadores);
        
        if (dar_prioridad_A) {
            sem_post(&sem_trabajoA); 
        }
        sem_wait(&sem_trabajoB); 
    }
    sem_wait(&sem_fotocopiadora);
        sem_wait(&sem_contadores);
        if (tipo == 'A') {
            trabajosA_espera--;
        } else {
            trabajosB_espera--;
        }
    
        sem_post(&sem_contadores);
        int necesita_enfriamiento = 0;
        if (tipo == 'B') {
            contador_trabajosB_seguidos++;
            if (contador_trabajosB_seguidos >= 2) {
                necesita_enfriamiento = 1;
            }
        } else {
            contador_trabajosB_seguidos = 0;
        }
    
        imprimir_estado(dinosaurio, tipo, necesita_enfriamiento);
        fotocopiar(tipo, dinosaurio);
    sem_post(&sem_fotocopiadora);
    
    if (necesita_enfriamiento) {
        sem_wait(&sem_enfriamiento);
            esperar_enfriamiento();
        sem_post(&sem_enfriamiento);
    }
    if (tipo == 'A') {
        sem_post(&sem_trabajoA);
    } else {
        sem_post(&sem_trabajoB);
    }
}

// estructura para datos del dinosaurio
typedef struct {
    char tipo_trabajo;  
    char nombre[50];    
} DinosaurioData;


void* dinosaurio_thread(void* arg) {
    DinosaurioData* dino = (DinosaurioData*)arg;
    sleep(rand() % 3);  //cuando se crea el hilo dino espera un tiempo para querer usar la fotocopiadora
    usar_fotocopiadora(dino->tipo_trabajo, dino->nombre);
    free(dino); 
    return NULL;
}

int main() {
    srand(time(NULL));

    sem_init(&sem_fotocopiadora, 0, 1);
    sem_init(&sem_bandeja, 0, 1);
    sem_init(&sem_trabajoA, 0, 1);
    sem_init(&sem_trabajoB, 0, 1);
    sem_init(&sem_enfriamiento, 0, 1);
    sem_init(&sem_contadores, 0, 1);
    pthread_t dinosaurios[10];
    const char* nombres[10] = {"Dino1", "Dino2", "Dino3", "Dino4", "Dino5", "Dino6", "Dino7", "Dino8", "dino9", "dino10" };
    char tipos[10] = {'A', 'B', 'A', 'B','A', 'B', 'B', 'A','B' ,'A'};
    
    for (int i = 0; i < 10; i++) {
        DinosaurioData* dino = malloc(sizeof(DinosaurioData));
        dino->tipo_trabajo = tipos[i];
        strncpy(dino->nombre, nombres[i], sizeof(dino->nombre));
        dino->nombre[sizeof(dino->nombre)-1] = '\0'; 
        
        pthread_create(&dinosaurios[i], NULL, dinosaurio_thread, dino);
    }
    
    for (int i = 0; i < 10; i++) {
        pthread_join(dinosaurios[i], NULL);
    }
    sem_destroy(&sem_fotocopiadora);
    sem_destroy(&sem_bandeja);
    sem_destroy(&sem_trabajoA);
    sem_destroy(&sem_trabajoB);
    sem_destroy(&sem_enfriamiento);
    sem_destroy(&sem_contadores);
    
    return 0;
}

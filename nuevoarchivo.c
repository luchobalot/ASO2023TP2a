#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUMBER_OF_THREADS 2
#define CANTIDAD_INICIAL_HAMBURGUESAS 20

int cantidad_restante_hamburguesas = CANTIDAD_INICIAL_HAMBURGUESAS;
int turno = 0; // Variable para controlar el turno de los hermanos

void *comer_hamburguesa(void *tid) {
    int mi_turno = *((int *)tid); // Cada hermano tiene su número de turno

    while (cantidad_restante_hamburguesas > 0) {
        if (turno == mi_turno) {
            if (cantidad_restante_hamburguesas > 0) {
                printf("Hola, soy el hermano %d, me voy a comer una hamburguesa. Quedan %d hamburguesas.\n", mi_turno, cantidad_restante_hamburguesas);
                cantidad_restante_hamburguesas--;
                turno = (turno + 1) % NUMBER_OF_THREADS; // Cambia el turno al otro hermano
            } else {
                printf("Se terminaron las hamburguesas para el hermano %d. :(\n", mi_turno);
            }
        }
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUMBER_OF_THREADS];
    int tids[NUMBER_OF_THREADS];

    for (int i = 0; i < NUMBER_OF_THREADS; i++) {
        tids[i] = i;
        pthread_create(&threads[i], NULL, comer_hamburguesa, &tids[i]);
    }

    for (int i = 0; i < NUMBER_OF_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Se han terminado todas las hamburguesas.\n");

    return 0;
}


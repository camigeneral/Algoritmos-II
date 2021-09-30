#include "cola.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>

static void prueba_cola_vacia(void) {
    cola_t *cola = cola_crear();

    print_test("> la cola esta vacia", cola_esta_vacia(cola) == true);
    print_test("> ver primero devuleve null", cola_ver_primero(cola) == NULL);
    print_test("> desencolar devuleve null", cola_desencolar(cola) == NULL);

    cola_destruir(cola, NULL);
}


static void prueba_encolar_y_desencolar(void) {
    cola_t *cola = cola_crear();
    
    print_test("> la cola esta vacia", cola_esta_vacia(cola) == true);
    int valor1 = 1;
    int valor2[] = {2,3,4};
    double valor3 = 5.678;
    print_test("> encolo un elemento", cola_encolar(cola, &valor1));
    print_test("> ver primero muestra el elemento encolado", cola_ver_primero(cola) == &valor1);
    print_test("> desencolo ese elemnto", cola_desencolar(cola) == &valor1);
    print_test("> encolo otro elemnto", cola_encolar(cola, &valor2));
    print_test("> encolo otro elemnto", cola_encolar(cola, &valor3));
    print_test("> desencolo el primer elemnto", cola_desencolar(cola) == &valor2);
    print_test("> desencolo el primer elemnto", cola_desencolar(cola) == &valor3);
    print_test("> la cola esta vacia", cola_esta_vacia(cola) == true);
    print_test("> intento desencolar un elemento de una cola vacia" , cola_desencolar(cola) == NULL);

    cola_destruir(cola, NULL);
}


static void prueba_volumen(void) {
    cola_t *cola = cola_crear();

    int valor1 = 0;
    cola_encolar(cola, &valor1);
    for (int i = 1; i < 1999; i++) {
        cola_encolar(cola, &i);
    }
    int valor2 = 2000;
    print_test("> se encolaron 2000 elementos", cola_encolar(cola, &valor2));
    print_test("> ver primero muestra el primer elemento agregado", cola_ver_primero(cola) == &valor1);
    for (int i = 0; i < 1999; i++) {
        cola_desencolar(cola);
    }
    print_test("> se desencolaron 2000 elementos", cola_desencolar(cola));
    print_test("> la cola esta vacia", cola_esta_vacia(cola) == true);

    cola_destruir(cola, NULL);
}


static void prueba_null(void) {
    cola_t *cola = cola_crear();

    print_test("> se puede encolar un elemento NULL", cola_encolar(cola, NULL));
    print_test("> la cola no esta vacia", cola_esta_vacia(cola) == false);
    print_test("> desencolo el NULL", cola_desencolar(cola) == NULL);
    print_test("> la cola esta vacia", cola_esta_vacia(cola) == true);

    cola_destruir(cola, NULL);
}


static void prueba_destruir_free(void) {
    cola_t *cola = cola_crear();

    int *vector1 = malloc((sizeof(int)*5));
    float *vector2 = malloc((sizeof(float)*6));
    char *vector3 = malloc((sizeof(char)*7));
    print_test("> encolo un vector", cola_encolar(cola, vector1));
    print_test("> encolo otro vector", cola_encolar(cola, vector2));
    print_test("> encolo otro vector y destruyo la cola pasando como parametro la funcion free", cola_encolar(cola, vector3));

    cola_destruir(cola, free);
} 


void cola_destruir_aux(cola_t *cola) {
    cola_destruir(cola, NULL);
}


static void prueba_destruir_cola_destruir(void) {
    cola_t *cola1 = cola_crear();
    cola_t *cola2 = cola_crear();
    print_test("> encolo una cola y luego destruyo la primera cola pasando como parametro la funcion cola_destruir",cola_encolar(cola2, cola1));

    cola_destruir_aux(cola1);
    cola_destruir(cola2, NULL);
}


void pruebas_cola_estudiante(void) {
    printf("PRUEBAS CON UNA COLA VACIA\n\n");
    prueba_cola_vacia();
    printf("\n");
    printf("PRUEBA ENCOLAR Y DESENCOLAR\n\n");
    prueba_encolar_y_desencolar();
    printf("\n");
    printf("PRUEBAS DE VOLUMEN\n\n");
    prueba_volumen();
    printf("\n");
    printf("PRUEBAS CON ELEMENTOS NULL\n\n");
    prueba_null();
    printf("\n");
    printf("PRUEBAS DE DESTRUCCION\n\n");
    prueba_destruir_free();
    prueba_destruir_cola_destruir();
    printf("\n"); 
}


#ifndef CORRECTOR

int main(void) {
    pruebas_cola_estudiante();
    return failure_count() > 0;
}

#endif

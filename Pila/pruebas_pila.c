#include "pila.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>

static void prueba_pila_vacia(void) {
    pila_t *pila = pila_crear();

    print_test("> la pila esta vacia", pila_esta_vacia(pila) == true);
    print_test("> ver tope devuleve null", pila_ver_tope(pila) == NULL);
    print_test("> desapilar devuleve null", pila_desapilar(pila) == NULL);

    pila_destruir(pila);
}


static void prueba_apilar_y_desapilar(void) {
    pila_t *pila = pila_crear();

    print_test("> la pila esta vacia", pila_esta_vacia(pila) == true);
    int valor1 = 1;
    int valor2[] = {2,3,4};
    double valor3 = 5.678;
    print_test("> apilo un elemento", pila_apilar(pila, &valor1));
    print_test("> ver tope muestra el elemento apilado", pila_ver_tope(pila) == &valor1);
    print_test("> desapilo ese elemnto", pila_desapilar(pila) == &valor1);
    print_test("> apilo otro elemnto", pila_apilar(pila, &valor2));
    print_test("> apilo otro elemnto", pila_apilar(pila, &valor3));
    print_test("> desapilo el ultimo elemnto", pila_desapilar(pila) == &valor3);
    print_test("> desapilo el ultimo elemnto", pila_desapilar(pila) == &valor2); 
    print_test("> la pila esta vacia", pila_esta_vacia(pila) == true);
    print_test("> intento desapilar un elemento de una pila vacia" , pila_desapilar(pila) == NULL);
    
    pila_destruir(pila);
}


static void prueba_volumen(void) {
    pila_t *pila = pila_crear();

    for (int i = 0; i < 3999; i++) {
        pila_apilar(pila, &i);
    }
    int valor = 4000;
    print_test("> se apliaron 4000 elementos", pila_apilar(pila, &valor));
    print_test("> la pila no esta vacia", pila_esta_vacia(pila) == false);
    print_test("> ver tope muestra el ultimo elemento apilado", pila_ver_tope(pila) == &valor);
    for (int i = 0; i < 3999; i++) {
        pila_desapilar(pila);   
    }
    print_test("> se desapliaron 4000 elementos", pila_desapilar(pila));
    print_test("> la pila esta vacia", pila_esta_vacia(pila) == true);

    pila_destruir(pila);
}


static void prueba_null(void) {
    pila_t *pila = pila_crear();

    print_test("> se puede apilar un elemnto NULL", pila_apilar(pila, NULL));
    print_test("> la pila no esta vacia", pila_esta_vacia(pila) == false);
    print_test("> desapilo el NULL", pila_desapilar(pila) == NULL);
    print_test("> la pila esta vacia", pila_esta_vacia(pila) == true);

    pila_destruir(pila);
}


void pruebas_pila_estudiante(void) {
    printf("PRUEBAS CON UNA PILA VACIA\n\n");
    prueba_pila_vacia();
    printf("\n");
    printf("PRUEBA APILAR Y DESAPILAR\n\n");
    prueba_apilar_y_desapilar();
    printf("\n");
    printf("PRUEBAS DE VOLUMEN\n\n");
    prueba_volumen();
    printf("\n");
    printf("PRUEBAS CON ELEMENTOS NULL\n\n");
    prueba_null();
    printf("\n");
}


/* Función main() que llama a la función de pruebas. */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_pila_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif

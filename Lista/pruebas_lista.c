#include "lista.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>

static void prueba_lista_vacia(void) {
    lista_t *lista = lista_crear();

    print_test("> Prueba crear una lista", lista != NULL);
    print_test("> Inicialmente esta vacia", lista_esta_vacia(lista));
    print_test("> El largo de la lista es 0", lista_largo(lista) == 0);
    print_test("> Ver primero devuleve NULL", lista_ver_primero(lista) == NULL);
    print_test("> Ver ultimo devuleve NULL", lista_ver_ultimo(lista) == NULL);
    print_test("> Borrar primero devuleve NULL", lista_borrar_primero(lista) == NULL);

    lista_destruir(lista, NULL);
}

static void prueba_insertar_borrar(void) {
    lista_t *lista = lista_crear();

    int valor1 = 12;
    int valor2 = 24;
    int valor3 = 36;

    print_test("> Prueba insertar un elemento en el primer lugar", lista_insertar_primero(lista, &valor1));
    print_test("> Prueba insertar un elemento en el ultimo lugar", lista_insertar_ultimo(lista, &valor2));
    print_test("> Prueba insertar un elemento en el primer lugar", lista_insertar_primero(lista, &valor3));
    print_test("> La lista no esta vacia", !lista_esta_vacia(lista));
    print_test("> Ver primero muestra el elemento correcto", lista_ver_primero(lista) == &valor3);
    print_test("> Prueba borrar el primer elemento", lista_borrar_primero(lista) == &valor3);
    print_test("> Prueba borrar el primer elemento", lista_borrar_primero(lista) == &valor1);
    print_test("> Prueba borrar el primer elemento", lista_borrar_primero(lista) == &valor2);
    print_test("> La lista esta vacia", lista_esta_vacia(lista));
    print_test("> Prueba insertar un elemento en el primer lugar", lista_insertar_primero(lista, &valor3));
    print_test("> Ver primero muestra el elemento correcto", lista_ver_primero(lista) == &valor3);
    print_test("> Ver ultimo muestra el elemento correcto", lista_ver_ultimo(lista) == &valor3);
    print_test("> Prueba borrar el primer elemento", lista_borrar_primero(lista) == &valor3);
    
    lista_destruir(lista, NULL);
}   

static void prueba_volumen(void) {
    lista_t *lista = lista_crear();

    int valor1 = 12;
    int valor2 = 24;
    int valor3 = 36;

    for (int i = 0; i < 999; i++) {
        if (i % 3 == 0) lista_insertar_primero(lista, &valor1);
        else if (i % 3 == 1) lista_insertar_primero(lista, &valor2);
        else lista_insertar_primero(lista, &valor3);
    }

    for (int i = 999; i < 1998; i++) {
        if (i % 3 == 0) lista_insertar_primero(lista, &valor1);
        else if (i % 3 == 1) lista_insertar_primero(lista, &valor2);
        else lista_insertar_primero(lista, &valor3);
    }
    
    // la lista deberia haber quedado: 36, 24, 12, ... 12, 36, 24, 12 ... 36, 24, 12

    int *prim = lista_ver_primero(lista);
    int *ult = lista_ver_ultimo(lista);

    print_test("> Prueba insertar 3600 elementos", lista_largo(lista) == 1998);
    print_test("> Ver primero muestra el elemento correcto", *prim == 36);
    print_test("> Ver ultimo muestra el elemento correcto", *ult == 12);
    for (int i = 0; i < 1998; i++) {
        lista_borrar_primero(lista);
    }
    print_test("> Prueba borrar todos los elementos de la lista", lista_esta_vacia(lista));

    lista_destruir(lista, NULL);
}

static void prueba_null(void) {
    lista_t *lista = lista_crear();

    print_test("> Prueba insertar un elemnto NULL", lista_insertar_primero(lista, NULL));
    print_test("> La lista no esta vacia", !lista_esta_vacia(lista));
    print_test("> Ver primero muestra el elemento correcto", lista_ver_primero(lista) == NULL);
    print_test("> Ver ultimo muestra el elemento correcto", lista_ver_ultimo(lista) == NULL);
    print_test("> Prueba borrar el NULL", lista_borrar_primero(lista) == NULL);

    lista_destruir(lista, NULL); 
}

static void prueba_destruccion(void) {
    lista_t *lista1 = lista_crear();
    int *vector1 = malloc((sizeof(int)*8));
    print_test("> Prueba destruir una lista que contiene un vector usando free", lista_insertar_primero(lista1, vector1));
    lista_destruir(lista1, free);

    lista_t *lista2 = lista_crear();
    print_test("> Prueba destruir una lista vacia usando free", true);
    lista_destruir(lista2, free);
}

static void prueba_iterador_externo(void) {
    lista_t *lista = lista_crear();
    lista_iter_t *iter = lista_iter_crear(lista);

    int valor1 = 4;
    int valor2 = 5;
    int valor3[] = {6, 7, 8};
    int valor4[] = {9, 10, 11};

    print_test("> Inicialmente el iterador se encentra al final de la lista", lista_iter_al_final(iter));
    print_test("> Prueba insertar elemento al prinicpo de la lista", lista_iter_insertar(iter, &valor1));
    print_test("> Prueba insertar elemento al prinicpo de la lista", lista_iter_insertar(iter, &valor2));
    print_test("> Prueba insertar elemento al prinicpo de la lista", lista_iter_insertar(iter, &valor3));
    print_test("> Prueba avanzar el iterador", lista_iter_avanzar(iter));
    print_test("> Prueba avanzar el iterador", lista_iter_avanzar(iter));
    print_test("> Prueba insertar elemento en el medio de la lista", lista_iter_insertar(iter, &valor4));
    
    //la lista deberia haber quedado: valor3, valor2, valor4, valor1 

    print_test("> El iterador apunta al elemento correcto", lista_iter_ver_actual(iter) == &valor4);
    print_test("> Ver primero muestra el elemento correcto", lista_ver_primero(lista) == &valor3);
    print_test("> Ver ultimo muestra el elemento correcto", lista_ver_ultimo(lista) == &valor1);
    print_test("> Prueba borrar un elemento", lista_iter_borrar(iter));
    print_test("> Prueba que el largo de la lista sea correcto", lista_largo(lista) == 3);
    print_test("> Prueba avanzar el iterador", lista_iter_avanzar(iter));
    print_test("> El iterador se encentra al final de la lista", lista_iter_al_final(iter));

    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);    
}


bool sumar(void* dato, void* extra) {
    *(int*) extra += *(int*) dato;
    return true;
}

bool multiplicar_primeros(void* dato, void* extra) {
    if (*(int*) extra >= 20) return false;
    *(int*) extra *= *(int*) dato;
    return true;
}


static void prueba_iterador_interno(void) {
    lista_t *lista = lista_crear();

    int valor1 = 1;
    int valor2 = 2;
    int valor3 = 3;

    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0) lista_insertar_ultimo(lista, &valor1);
        else if (i % 3 == 1) lista_insertar_ultimo(lista, &valor2);
        else lista_insertar_ultimo(lista, &valor3);
    }

    // la lista deberia haber quedado: 1, 2, 3, 1, 2, 3, 1, 2, 3

    int suma = 0;
    lista_iterar(lista, sumar, &suma);
    print_test("> Prueba sumar los elementos de la lista", suma == 18);

    int prod = 1;
    lista_iterar(lista, multiplicar_primeros, &prod);
    print_test("> Prueba multiplicar los elementos de la lista hasta que el resultado sea menor o igual a 20", prod == 36);

    lista_destruir(lista, NULL);
} 


void pruebas_lista_estudiante(void) { 
    printf("PRUEBAS CON UNA LISTA VACIA\n\n");
    prueba_lista_vacia();
    printf("\n");
    printf("PRUEBA INSERTAR Y BORRAR ELEMENTOS DE LA LISTA\n\n");
    prueba_insertar_borrar();
    printf("\n");
    printf("PRUEBAS DE VOLUMEN\n\n");
    prueba_volumen();
    printf("\n");
    printf("PRUEBAS CON ELEMENTOS NULL\n\n");
    prueba_null();
    printf("\n");
    printf("PRUEBAS DE DESTRUCCION\n\n");
    prueba_destruccion();
    printf("\n");
    printf("PRUEBAS CON EL ITERADOR EXTERNO\n\n");
    prueba_iterador_externo();
    printf("\n");
    printf("PRUEBAS CON EL ITERADOR INTERNO\n\n");
    prueba_iterador_interno();
    printf("\n");
}

#ifndef CORRECTOR

int main(void) {
    pruebas_lista_estudiante();
    return failure_count() > 0;
}

#endif

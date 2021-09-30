#include "heap.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//--------------------------------------- funciones auxiliares --------------------------------------- 


int comparar_numeros(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

int comparar_cadenas(const void* a, const void* b) {
    return strcmp((char*)a, (char*)b);
}

//---------------------------------------------- pruebas --------------------------------------------- 


static void pruebas_heap_vacio() {
    heap_t* heap = heap_crear(comparar_cadenas);

    print_test("> Prueba crear un heap", heap);
    print_test("> Prueba heap inicialmente esta vacio", heap_esta_vacio(heap));
    print_test("> Prueba la cantidad de elementos en el heap es 0", heap_cantidad(heap) == 0);
    print_test("> Prueba ver maximo devuelve NULL", heap_ver_max(heap) == NULL);
    print_test("> Prueba desencolar devuelve NULL", !heap_desencolar(heap));

    heap_destruir(heap, NULL);
}


static void pruebas_encolar_desencolar() {
    heap_t* heap = heap_crear(comparar_cadenas);

    char* valores[] = {"dodo", "esmerejon", "flamenco", "aguila", "buho", "canario"};

    print_test("> Prueba crear un heap", heap);
    print_test("> Prueba encolar un valor", heap_encolar(heap, valores[0]));
    print_test("> Prueba heap no esta vacio", !heap_esta_vacio(heap));
    print_test("> Prueba heap cantidad es 1", heap_cantidad(heap) == 1);
    print_test("> Prueba ver maximo devuelve el valor encolado", strcmp(heap_ver_max(heap), valores[0]) == 0);
    print_test("> Prueba desencolar el elemento", strcmp(heap_desencolar(heap), valores[0]) == 0);
    print_test("> Prueba desencolar otra vez devuelve NULL", heap_desencolar(heap) == NULL);
    print_test("> Prueba heap esta vacio", heap_esta_vacio(heap)); 

    bool ok = true;
    for (int i = 0; i < 6; i++) {
        if (!heap_encolar(heap, valores[i])){    
            ok = false; 
            break;
        }
    }
    
    print_test("> Prueba insertar 6 elementos", ok);
    print_test("> Prueba heap cantidad es 6", heap_cantidad(heap) == 6);
    print_test("> Prueba ver maximo devuelve el maximo", strcmp(heap_ver_max(heap), valores[2]) == 0);
    print_test("> Prueba desencolar devuelve el maximo", strcmp(heap_desencolar(heap), valores[2]) == 0);
    print_test("> Prueba heap cantidad es 5", heap_cantidad(heap) == 5);
    print_test("> Prueba ver maximo devuelve el maximo", strcmp(heap_ver_max(heap), valores[1]) == 0);
    print_test("> Prueba desencolar devuelve el maximo", strcmp(heap_desencolar(heap), valores[1]) == 0);
    print_test("> Prueba ver maximo devuelve el maximo", strcmp(heap_ver_max(heap), valores[0]) == 0);
    print_test("> Prueba desencolar devuelve el maximo", strcmp(heap_desencolar(heap), valores[0]) == 0);
    print_test("> Prueba ver maximo devuelve el maximo", strcmp(heap_ver_max(heap), valores[5]) == 0);
    print_test("> Prueba desencolar devuelve el maximo", strcmp(heap_desencolar(heap), valores[5]) == 0);
    print_test("> Prueba ver maximo devuelve el maximo", strcmp(heap_ver_max(heap), valores[4]) == 0);
    print_test("> Prueba desencolar devuelve el maximo", strcmp(heap_desencolar(heap), valores[4]) == 0);
    print_test("> Prueba ver maximo devuelve el maximo", strcmp(heap_ver_max(heap), valores[3]) == 0);
    print_test("> Prueba desencolar devuelve el maximo", strcmp(heap_desencolar(heap), valores[3]) == 0);
    print_test("> Prueba heap cantidad es 0", heap_cantidad(heap) == 0);
    print_test("> Prueba desencolar otra vez devuelve NULL", heap_desencolar(heap) == NULL);
    print_test("> Prueba heap esta vacio", heap_esta_vacio(heap));

    heap_destruir(heap, NULL);
}


static void pruebas_insertar_arreglo() {
    char* valores[] = {"somormujo", "trepador azul", "urraca", "paloma", "quebrantahuesos", "ruiseñor"};
    heap_t* heap = heap_crear_arr((void**)valores, 6, comparar_cadenas);

    print_test("> Prueba insertar 6 elementos", heap);
    print_test("> Prueba heap cantidad es 6", heap_cantidad(heap) == 6);
    print_test("> Prueba ver maximo devuelve el maximo", strcmp(heap_ver_max(heap), valores[2]) == 0);
    print_test("> Prueba desencolar devuelve el maximo", strcmp(heap_desencolar(heap), valores[2]) == 0);
    print_test("> Prueba heap cantidad es 5", heap_cantidad(heap) == 5);
    print_test("> Prueba ver maximo devuelve el maximo", strcmp(heap_ver_max(heap), valores[1]) == 0);
    print_test("> Prueba desencolar devuelve el maximo", strcmp(heap_desencolar(heap), valores[1]) == 0);
    print_test("> Prueba ver maximo devuelve el maximo", strcmp(heap_ver_max(heap), valores[0]) == 0);
    print_test("> Prueba desencolar devuelve el maximo", strcmp(heap_desencolar(heap), valores[0]) == 0);
    print_test("> Prueba ver maximo devuelve el maximo", strcmp(heap_ver_max(heap), valores[5]) == 0);
    print_test("> Prueba desencolar devuelve el maximo", strcmp(heap_desencolar(heap), valores[5]) == 0);
    print_test("> Prueba ver maximo devuelve el maximo", strcmp(heap_ver_max(heap), valores[4]) == 0);
    print_test("> Prueba desencolar devuelve el maximo", strcmp(heap_desencolar(heap), valores[4]) == 0);
    print_test("> Prueba ver maximo devuelve el maximo", strcmp(heap_ver_max(heap), valores[3]) == 0);
    print_test("> Prueba desencolar devuelve el maximo", strcmp(heap_desencolar(heap), valores[3]) == 0);
    print_test("> Prueba heap esta vacio", heap_esta_vacio(heap));

    heap_destruir(heap, NULL);
}


static void pruebas_elementos_null() {
    heap_t* heap = heap_crear(comparar_cadenas);

    print_test("> Prueba insertar un elemnto NULL", heap_encolar(heap, NULL));
    print_test("> Prueba el heap no esta vacio", !heap_esta_vacio(heap));
    print_test("> Prueba heap cantidad es 1", heap_cantidad(heap) == 1);
    print_test("> Prueba ver maximo devuelve NULL", heap_ver_max(heap) == NULL);
    print_test("> Prueba borrar el NULL", heap_desencolar(heap) == NULL);
    
    heap_destruir(heap, NULL);
}


static void pruebas_destruccion() {
    heap_t* heap = heap_crear(comparar_cadenas);
    
    int *vector1 = malloc((sizeof(int)*5));
    vector1[0] = 12;
    int *vector2 = malloc((sizeof(int)*6));
    vector2[0] = 36;
    int *vector3 = malloc((sizeof(int)*7));
    vector3[0] = 24;

    heap_encolar(heap, vector1);
    heap_encolar(heap, vector2);
    print_test("> Prueba encolar 3 vectores y destruirlos usando free", heap_encolar(heap, vector3));

    heap_destruir(heap, free);
}


static void pruebas_volumen() { 
    heap_t* heap = heap_crear(comparar_numeros);

    int largo = 5000;
    int* valores[largo];
    
    bool ok = true;
    for (int i = 0; i < largo; i++) {
        valores[i] = malloc(sizeof(int));
        *valores[i] = i;
        ok = heap_encolar(heap, valores[i]);
        if (!ok) break;
    }

    print_test("> Prueba encolar 5000 elementos", ok);
    print_test("> Prueba heap cantidad es 5000", heap_cantidad(heap) == 5000);

    for (int i = 0; i < largo; i++) {
        ok = heap_desencolar(heap) == valores[4999-i];
        if (!ok) {
            printf("%d\n", i);
            break;
        }
    }

    print_test("> Prueba desencolar 5000 elementos", ok);
    print_test("> Prueba heap esta vacio", heap_esta_vacio(heap));

    heap_destruir(heap, NULL);
    for (int i = 0; i < largo; i++) free(valores[i]);
}


static void pruebas_heapsort() {
    char* valores[] = {"pino", "alamo", "palmera", "acacia", "araucaria", "ombu", "roble", "cipres", "alerce"};
    heap_sort((void**)valores, 9, comparar_cadenas);
    bool ordenado = true;

    for (int i = 1; i < 9; i++) {
        if (strcmp(valores[i], valores[i-1]) < 0) ordenado = false;
    }

    print_test("> Prueba ordenar un arreglo de cadenas usando heapsort", ordenado);
}


void pruebas_heap_estudiante() {
    printf("PRUEBAS HEAP VACIO\n");
    pruebas_heap_vacio();
    printf("\n\nPRUEBAS ENCOLAR Y DESENCOLAR\n");
    pruebas_encolar_desencolar();
    printf("\n\nPRUEBAS CON EL CONSTRUCTOR ALTERNO\n");
    pruebas_insertar_arreglo();
    printf("\n\nPRUEBAS ELEMENTOS NULL\n");
    pruebas_elementos_null();
    printf("\n\nPRUEBAS DE DESTRUCCION\n");
    pruebas_destruccion();
    printf("\n\nPRUEBAS DE VOLUMEN\n");
    pruebas_volumen();
    printf("\n\nPRUEBAS HEAPSORT\n");
    pruebas_heapsort();
}


#ifndef CORRECTOR

int main(void) {
    pruebas_heap_estudiante();
    return failure_count() > 0;
}

#endif



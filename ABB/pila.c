#include "pila.h"
#include <stdlib.h>

/* Definición del struct pila proporcionado por la cátedra.*/


struct pila {
    void **datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};


/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/


pila_t *pila_crear(void) {
    pila_t *pila = malloc(sizeof(pila_t));

    if (pila == NULL) {
        return NULL;
    }

    pila->cantidad = 0;
    pila->capacidad = 10;

    pila->datos = malloc(pila->capacidad * sizeof(void*));

    if (pila->datos == NULL) {
        free(pila);
        return NULL;
    }

    return pila;
}


void pila_destruir(pila_t *pila) {
    free(pila->datos);
    free(pila);
}


bool pila_esta_vacia(const pila_t *pila) {
    if (pila->cantidad == 0) {
        return true;
    }

    return false;
}


void *pila_ver_tope(const pila_t *pila) {
    if (pila_esta_vacia(pila)) {
        return NULL;
    }

    return pila->datos[pila->cantidad-1];
}


bool pila_redimensionar(pila_t *pila, size_t capacidad_nueva) {
    void** datos_nuevos = realloc(pila->datos, capacidad_nueva * sizeof(void*));

    if (capacidad_nueva > 0 && datos_nuevos == NULL) {
        return false;
    }

    pila->datos = datos_nuevos;
    pila->capacidad = capacidad_nueva;
    return true;
}


bool pila_apilar(pila_t *pila, void *valor) {
    size_t cantidad = pila->cantidad;
    size_t capacidad = pila->capacidad;

    pila->datos[cantidad] = valor;
    pila->cantidad++;

    if (pila->cantidad == capacidad) {
        if (pila_redimensionar(pila, cantidad*2) == false){
            return false;
        }
    }

    return true;
}


void *pila_desapilar(pila_t *pila) {
    if (pila_esta_vacia(pila)) {
        return NULL;
    }

    void* valor = pila->datos[pila->cantidad-1];
    size_t capacidad = pila->capacidad;

    pila->cantidad--;

    if (pila->cantidad <= capacidad/4 && pila->cantidad/2 != 0) {
        pila_redimensionar(pila, pila->capacidad/2);
    }

    return valor;
}

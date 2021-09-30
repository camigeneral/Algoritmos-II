#include "heap.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

// ------------------------------ FUNCIONES AUXILIARES --------------------------------- //

struct heap{
    void** datos;
    size_t cantidad;
    size_t capacidad;
    cmp_func_t cmp;
};

void swap(void** datos, size_t pos_padre, size_t pos_hijo){
    void* aux = (datos[pos_padre]);
    datos[pos_padre] = datos[pos_hijo];
    datos[pos_hijo] = aux;

}

void upheap(void** datos, size_t pos_elemento, cmp_func_t cmp){
    if (pos_elemento == 0) return; 
    size_t pos_padre = ((pos_elemento - 1)/2);
    while (cmp(datos[pos_elemento], datos[pos_padre]) > 0){
        swap(datos, pos_padre, pos_elemento);
        pos_elemento = pos_padre;
        if (pos_elemento == 0) pos_padre = 0;
        else pos_padre = ((pos_elemento-1)/2);
    }
}

void downheap(void** datos, size_t pos_elemento, cmp_func_t cmp, size_t cant){
    size_t pos_hijo_izq = ((pos_elemento * 2) + 1);
    size_t pos_hijo_der = ((pos_elemento * 2) + 2);

    if (pos_hijo_izq >= cant) return;
    else if (pos_hijo_der >= cant) pos_hijo_der = pos_hijo_izq;

    while (cmp(datos[pos_elemento], datos[pos_hijo_izq]) < 0 || cmp(datos[pos_elemento], datos[pos_hijo_der]) < 0){
        if (cmp(datos[pos_hijo_izq], datos[pos_hijo_der]) > 0){
            swap(datos, pos_elemento, pos_hijo_izq);
            pos_elemento = pos_hijo_izq;
        } 
        else{
            swap(datos, pos_elemento, pos_hijo_der);
            pos_elemento = pos_hijo_der;
        }
        pos_hijo_izq = ((pos_elemento * 2) + 1);
        pos_hijo_der = ((pos_elemento * 2) + 2);

        if (pos_hijo_izq >= cant) return;
        else if (pos_hijo_der >= cant) pos_hijo_der = pos_hijo_izq;
    }
}

bool heap_redimensionar(heap_t* heap, size_t capacidad_nueva) {
    void** datos_nuevos = realloc(heap->datos, capacidad_nueva * sizeof(void*));
    if (!datos_nuevos) return false;

    heap->datos = datos_nuevos;
    heap->capacidad = capacidad_nueva;
    return true;
}

void heapify(void* elementos[], size_t cant, cmp_func_t cmp) {
    for (int i = (int)cant-1; i >= 0; i--) {
        downheap(elementos, (size_t)i, cmp, cant);
    }
}

// ------------------------------ PRIMITIVAS ------------------------------------------- //

heap_t *heap_crear(cmp_func_t cmp){
    heap_t* heap = malloc(sizeof(heap_t));
    if (!heap) return NULL;
    heap->cantidad = 0;
    heap->capacidad = 10;
    heap->cmp = cmp;
    heap->datos = malloc(heap->capacidad * sizeof(void*)); 
    if (!heap->datos){
        free(heap);
        return NULL;
    }
    return heap;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
    heap_t* heap = heap_crear(cmp);
    if (!heap) return NULL;
    for (size_t i = 0; i < n; i++){
        if (!heap_encolar(heap, arreglo[i])){
            heap_destruir(heap, NULL);
            return NULL;
        }
    }
    return heap;
}

void heap_destruir(heap_t *heap, void (*destruir_elemento)(void *e)){
    
    while(!heap_esta_vacio(heap)){
        void* elemento_a_destruir = heap_desencolar(heap);
        if (destruir_elemento) {
            destruir_elemento(elemento_a_destruir);
        }
    }
    free(heap->datos);
    free(heap);
}

size_t heap_cantidad(const heap_t *heap){
    return heap->cantidad;
}

bool heap_esta_vacio(const heap_t *heap){
    return heap->cantidad == 0;
}

bool heap_encolar(heap_t *heap, void *elem){
    size_t pos_final = (size_t)heap_cantidad(heap);
    heap->datos[pos_final] = elem;
    upheap(heap->datos, pos_final, heap->cmp);
    heap->cantidad++;

    if (heap->cantidad == heap->capacidad){
        if (!heap_redimensionar(heap, heap->capacidad * 2)) return false;
    }

    return true;
}

void *heap_ver_max(const heap_t *heap){
    if (heap_esta_vacio(heap)) return NULL;
    return heap->datos[0];
}

void *heap_desencolar(heap_t *heap){
    if (heap_esta_vacio(heap)) return NULL;
    void* elemento = heap->datos[0];
    swap(heap->datos, 0, (size_t)heap_cantidad(heap)-1);
    heap->cantidad--;

    downheap(heap->datos, 0, heap->cmp, heap->cantidad);
    if (heap->cantidad * 4 <= heap->capacidad && (heap->cantidad/2) != 0) heap_redimensionar(heap, heap->capacidad/2);
    
    return elemento;
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp) {
    heapify(elementos, cant, cmp);
    while (cant > 1) {
        swap(elementos, 0, cant-1);
        cant--;
        downheap(elementos, 0, cmp, cant);
    }
}

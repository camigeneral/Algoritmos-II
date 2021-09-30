#include "cola.h"
#include <stdlib.h>

//Implementacion de los nodos

typedef struct nodo nodo_t; 

struct nodo {
    void* dato;
    nodo_t* prox;
};


nodo_t *nodo_crear(void* valor) {
    nodo_t *nodo = malloc(sizeof(nodo_t));
    if (nodo == NULL) {
        return NULL;
    }

    nodo->dato = valor;
    nodo->prox = NULL;

    return nodo;
}


void nodo_destruir(nodo_t *nodo){
    free(nodo);
}


//Implementacion de la cola


struct cola {
    nodo_t* prim;
    nodo_t* ult;
};


cola_t *cola_crear() {
    cola_t *cola = malloc(sizeof(cola_t));
    if (cola == NULL) {
        return NULL;
    }

    cola->prim = NULL;
    cola->ult = NULL;

    return cola;
}


bool cola_esta_vacia(const cola_t *cola) {
    return cola->prim == NULL;
}


bool cola_encolar(cola_t *cola, void *valor) {
    nodo_t *nodo = nodo_crear(valor);

    if (nodo == NULL) {
        return false;
    }
   
    if (cola_esta_vacia(cola)) {
        cola->prim = nodo;
        cola->ult = nodo;
    }
 
    else {
        cola->ult->prox = nodo;
        cola->ult = nodo;
    }

    return true;
}

void *cola_desencolar(cola_t *cola) {
    if (cola_esta_vacia(cola)) {
        return NULL;
    }

    nodo_t* nodo = cola->prim;
    void* dato = nodo->dato;

    cola->prim = cola->prim->prox;
    nodo_destruir(nodo);

    return dato;
}


void *cola_ver_primero(const cola_t *cola) {
    if (cola_esta_vacia(cola)) {
        return NULL;
    }

    return cola->prim->dato; 
}


void cola_destruir(cola_t *cola, void (*destruir_dato)(void *)) {
    while (!cola_esta_vacia(cola)) {
        nodo_t* nodo = cola->prim;
        cola->prim = cola->prim->prox;

        if (destruir_dato != NULL) {        
            destruir_dato(nodo->dato);
        }

        nodo_destruir(nodo);

    }

    free(cola);
}













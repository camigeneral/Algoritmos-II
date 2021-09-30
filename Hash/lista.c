#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

//Implementacion de los nodos

typedef struct nodo nodo_t;

struct nodo {
    void* dato;
    nodo_t *prox;
};


nodo_t *nodo_crear(void* valor) {
    nodo_t *nodo = malloc(sizeof(nodo_t));
    if (nodo == NULL) return NULL;

    nodo->dato = valor;
    nodo->prox = NULL;

    return nodo;
}


void nodo_destruir(nodo_t *nodo){
    free(nodo);
}


//Implementacion de la lista

struct lista {
    nodo_t *prim;
    nodo_t *ult;
    size_t largo;
};


lista_t *lista_crear(void) {
    lista_t *lista = malloc(sizeof(lista_t));
    if (lista == NULL) return NULL;

    lista->prim = NULL;
    lista->ult = NULL;
    lista->largo = 0;

    return lista;
}


bool lista_esta_vacia(const lista_t *lista) {
    return lista->prim == NULL;
}


void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)) {
    while (!lista_esta_vacia(lista)) {
        nodo_t *nodo = lista->prim;
        lista->prim = lista->prim->prox;
        if (destruir_dato != NULL) destruir_dato(nodo->dato);
        nodo_destruir(nodo);
    }

    free(lista);
}


bool lista_insertar_primero(lista_t *lista, void *dato) {
    nodo_t *nodo = nodo_crear(dato);
    if (!nodo) return false;

    nodo->prox = lista->prim;
    lista->prim = nodo;
    if (!lista->ult) lista->ult = nodo;
    lista->largo++;
    return true;
}


bool lista_insertar_ultimo(lista_t *lista, void *dato) {
    nodo_t *nodo = nodo_crear(dato);
    if (!nodo) return false;

    if (lista_esta_vacia(lista)) lista->prim = nodo;
    else lista->ult->prox = nodo;
    lista->ult = nodo;
    lista->largo++;
    return true; 
}


size_t lista_largo(const lista_t *lista) {
    return lista->largo;
}


void *lista_borrar_primero(lista_t *lista) {
    if (lista_esta_vacia(lista)) return NULL;

    nodo_t *nodo = lista->prim;
    void *dato = nodo->dato;
    lista->prim = lista->prim->prox;
    if (!lista->prim) lista->ult = NULL;
    lista->largo--;
    free(nodo);
    return dato;
}


void *lista_ver_primero(const lista_t *lista) {
    if (lista_esta_vacia(lista)) return NULL;
    return lista->prim->dato;
}


void *lista_ver_ultimo(const lista_t* lista) {
    if (lista_esta_vacia(lista)) return NULL;
    return lista->ult->dato;
}


void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra) {
    if (lista_esta_vacia(lista)) return;
    nodo_t *actual = lista->prim;
    bool continuar = true;
    while (actual && continuar) {
        continuar = visitar(actual->dato, extra);
        actual = actual->prox;
    }
}


//Iterador externo


struct lista_iter {
    lista_t *lista;
    nodo_t *anterior;
    nodo_t *actual;
};


lista_iter_t *lista_iter_crear(lista_t *lista) {
    lista_iter_t *iter = malloc(sizeof(lista_iter_t));
    if (iter == NULL) return NULL;

    iter->lista = lista;
    iter->anterior = NULL;
    iter->actual = lista->prim;

    return iter;
}


bool lista_iter_al_final(const lista_iter_t *iter) {
    if (!iter->actual) return true;
    return false;
}


bool lista_iter_avanzar(lista_iter_t *iter) {
    if (lista_iter_al_final(iter)) return false;

    iter->anterior = iter->actual;
    iter->actual = iter->actual->prox;
    return true;
}


void *lista_iter_ver_actual(const lista_iter_t *iter) {
    if (lista_iter_al_final(iter)) return NULL;
    return iter->actual->dato;    
}


void lista_iter_destruir(lista_iter_t *iter) {
    free(iter);
}


bool lista_iter_insertar(lista_iter_t *iter, void *dato) {
    nodo_t *nodo = nodo_crear(dato);
    if (nodo == NULL) return false;

    
    if (iter->anterior == NULL) iter->lista->prim = nodo;
    if (iter->actual == NULL) iter->lista->ult = nodo;
    
    nodo->prox = iter->actual;
    if (iter->anterior) {
        iter->anterior->prox = nodo;
    }
    iter->actual = nodo;
    iter->lista->largo++;

    return true;
}


void *lista_iter_borrar(lista_iter_t *iter) {
    if (lista_iter_al_final(iter)) return NULL;

    nodo_t *nodo = iter->actual;
    void *dato = nodo->dato;

    if (iter->anterior == NULL) iter->lista->prim = iter->actual->prox;
    if (iter->actual->prox == NULL) iter->lista->ult = iter->anterior;
    iter->actual = iter->actual->prox;
    if (iter->anterior) iter->anterior->prox = iter->actual;
    iter->lista->largo--;
    free(nodo);
    return dato;
}


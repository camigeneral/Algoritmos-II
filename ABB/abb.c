#include "abb.h"
#include "pila.h"
#include <stdlib.h>
#include <string.h>

// ------------------------------------------------> nodos <-------------------------------------------- //


typedef struct nodo nodo_t;


struct nodo {
    nodo_t* izq;
    nodo_t* der;
    char* clave;
    void* valor;
};
 

nodo_t* nodo_crear(char* clave, void* valor) {
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if (!nodo) return NULL;
    nodo->clave = clave;
    nodo->valor = valor;
    nodo->izq = NULL;
    nodo->der = NULL;
    return nodo;
}


void nodo_destruir(nodo_t* nodo) {
    free(nodo->clave);
    free(nodo);
}


// ----------------------------------------> funciones auxiliares <------------------------------------- //


nodo_t* buscar_nodo(nodo_t* raiz, const char* clave, abb_comparar_clave_t cmp) {
    if (!raiz) return NULL;
    else if (cmp(clave, raiz->clave) == 0) return raiz;
    else if (cmp(clave, raiz->clave) < 0) return buscar_nodo(raiz->izq, clave, cmp);
    else return buscar_nodo(raiz->der, clave, cmp);
}


nodo_t* buscar_predecesor(nodo_t* raiz, nodo_t** padre){
    if (!raiz) return NULL;
    else if (!raiz->der) return raiz;
    else {
        *padre = raiz;
        return buscar_predecesor(raiz->der, padre);
    }
}


void pila_apilar_izq(pila_t* pila, nodo_t* raiz) {
    if (!raiz) return;
    while(raiz->izq){
        pila_apilar(pila, raiz);
        raiz = raiz->izq;
    }
    pila_apilar(pila, raiz);
}


// ------------------------------------------------> arbol <-------------------------------------------- //


struct abb {
    nodo_t* raiz;
    abb_comparar_clave_t cmp;
    abb_destruir_dato_t destruir_dato;
    size_t cantidad;
};


abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato) {
    abb_t* abb = malloc(sizeof(abb_t));
    if (!abb) return NULL;

    abb->raiz = NULL;
    abb->cmp = cmp;
    abb->destruir_dato = destruir_dato;
    abb->cantidad = 0;

    return abb;
}


void* _abb_guardar(nodo_t** raiz, const char* clave, void* valor, abb_comparar_clave_t cmp) { 
    if (!clave) return NULL;
    if (!*raiz) {
        char *copia_clave = malloc(strlen(clave) + 1);
        if (!copia_clave) return NULL;
        strcpy(copia_clave, clave);
        nodo_t* nodo = nodo_crear(copia_clave, valor);
        if (!nodo) return NULL;
        *raiz = nodo;
        return *raiz;
    }

    else if (cmp(clave, (*raiz)->clave) < 0) _abb_guardar(&(*raiz)->izq, clave, valor, cmp);
    else if (cmp(clave, (*raiz)->clave) > 0) _abb_guardar(&(*raiz)->der, clave, valor, cmp);
    else (*raiz)->valor = valor;

    return *raiz;
}


bool abb_guardar(abb_t *arbol, const char *clave, void *dato) {
    if (abb_pertenece(arbol, clave)) {
        void* valor = abb_borrar(arbol, clave);
        if (arbol->destruir_dato) arbol->destruir_dato(valor);
    }
    if (!_abb_guardar(&arbol->raiz, clave, dato, arbol->cmp)) return false;
    arbol->cantidad++;
    return true;
}


void *abb_obtener(const abb_t *arbol, const char *clave){
    nodo_t* nodo = buscar_nodo(arbol->raiz, clave, arbol->cmp);
    if (!nodo) return NULL;
    else return nodo->valor;
}


bool abb_pertenece(const abb_t* arbol, const char *clave) {
    return buscar_nodo(arbol->raiz, clave, arbol->cmp);
}


size_t abb_cantidad(const abb_t *arbol) {
    return arbol->cantidad;
}


void* _abb_borrar(nodo_t** raiz, const char* clave, abb_comparar_clave_t cmp) {
    if (!*raiz) return NULL;
    else if (cmp(clave, (*raiz)->clave) < 0) return _abb_borrar(&(*raiz)->izq, clave, cmp);
    else if (cmp(clave, (*raiz)->clave) > 0) return _abb_borrar(&(*raiz)->der, clave, cmp);
    else {
        void* valor_a_devolver = NULL;

        //si el nodo tiene 2 hijos
        if ((*raiz)->izq && (*raiz)->der) {
            valor_a_devolver = (*raiz)->valor;

            //buscamos un reemplazo para el valor que queremos borrar y guardamos su padre
            nodo_t* padre_reemplazo = *raiz;
            nodo_t* reemplazo = buscar_predecesor((*raiz)->izq, &padre_reemplazo);

            //reemplazamos los datos del nodo a borrar con los del reemplazo
            char* clave_reemplazo = reemplazo->clave;
            char* copia_clave = strdup(clave_reemplazo);
            void* valor_reemplazo = reemplazo->valor;
            free((*raiz)->clave); 
            (*raiz)->clave = copia_clave;
            (*raiz)->valor = valor_reemplazo;

            //borramos el reemplazo
            if (padre_reemplazo->der == reemplazo) {
                if (reemplazo->der) padre_reemplazo->der = reemplazo->der;
                else if (reemplazo->izq) padre_reemplazo->der = reemplazo->izq;
                else padre_reemplazo->der = NULL;
            } else {
                if (reemplazo->der) padre_reemplazo->izq = reemplazo->der;
                else if (reemplazo->izq) padre_reemplazo->izq = reemplazo->izq;
                else padre_reemplazo->izq = NULL;
            }
            nodo_destruir(reemplazo);
        }

        //si tiene 1 o 0 hijos
        else {
            nodo_t* aux = *raiz;
            valor_a_devolver = aux->valor;
            if (!(*raiz)->izq) *raiz = (*raiz)->der;
            else *raiz = (*raiz)->izq;
            nodo_destruir(aux);
        }   
        
        return valor_a_devolver;
    }
}


void *abb_borrar(abb_t *arbol, const char *clave) {
    if (!abb_pertenece(arbol, clave)) return NULL;
    void* elemento = _abb_borrar(&arbol->raiz, clave, arbol->cmp);
    arbol->cantidad--;
    return elemento;
}


void _abb_destruir(nodo_t* raiz, abb_destruir_dato_t destruir_dato) {
    if (!raiz) return;
    _abb_destruir(raiz->izq, destruir_dato);
    _abb_destruir(raiz->der, destruir_dato);
    if (destruir_dato) destruir_dato(raiz->valor);
    nodo_destruir(raiz);
    return;
}


void abb_destruir(abb_t *arbol) {
    _abb_destruir(arbol->raiz, arbol->destruir_dato);
    free(arbol);
    return;
}


bool _abb_in_order(nodo_t* raiz, bool visitar(const char *, void *, void *), void* extra, bool* validacion) {
    if (!raiz) return false;
    _abb_in_order(raiz->izq, visitar, extra, validacion);
    if (!*validacion) return false;
    if (!visitar(raiz->clave,raiz->valor, extra)) {
        *validacion = false;
        return false;
    }
    _abb_in_order(raiz->der, visitar, extra, validacion);
    return true;
}


void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra) {
    bool validacion = true;
    _abb_in_order(arbol->raiz, visitar, extra, &validacion);
    return;
}


// ----------------------------------------> iterador externo <------------------------------------- //


struct abb_iter {
    const abb_t* abb;
    pila_t* pila;
};
 

abb_iter_t *abb_iter_in_crear(const abb_t *arbol) {
    abb_iter_t* iter = malloc(sizeof(abb_iter_t));
    if (!iter) return NULL;
    iter->pila = pila_crear();
    if(!iter->pila) return NULL;
    iter->abb = arbol;
    pila_apilar_izq(iter->pila, arbol->raiz);
    return iter;
}


bool abb_iter_in_al_final(const abb_iter_t* iter) {
    return (pila_esta_vacia(iter->pila));
}


bool abb_iter_in_avanzar(abb_iter_t* iter) {
    if (abb_iter_in_al_final(iter)) return false;
    nodo_t* raiz = pila_desapilar(iter->pila);
    if (raiz->der) pila_apilar_izq(iter->pila, raiz->der);
    return true;
}


const char* abb_iter_in_ver_actual(const abb_iter_t* iter) {
    if (abb_iter_in_al_final(iter)) return NULL;
    nodo_t* tope = pila_ver_tope(iter->pila);
    return tope->clave;
}


void abb_iter_in_destruir(abb_iter_t* iter) {
    pila_destruir(iter->pila);
    free(iter);
}

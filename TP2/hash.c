#include "hash.h"
#include "lista.h"
#include "hashing.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

const size_t CAPACIDAD_INICIAL = 47;

/* Funciones auxiliares */

bool es_primo(int n) {
    for (int i = 2; i < n; i++) if (n % i == 0) return false;
    return 1;
}

int proximo_primo(int n) {
    int encontrado = 1;
    while (!encontrado) encontrado = es_primo(++n);
    return n;
}

/* Implementacion del dato */


typedef struct dato dato_t;


struct dato {
    char *clave;
    void *valor; 
};


dato_t *dato_crear(char *clave, void *valor) {
    dato_t *dato = malloc(sizeof(dato_t));
    if (dato == NULL) return NULL;

    dato->clave = clave;
    dato->valor = valor;

    return dato;
}


void dato_destruir(dato_t *dato){
    free(dato->clave);
    free(dato);
}


/* Implementacion del hash */


struct hash {
    size_t cantidad;
    size_t capacidad;
    void **datos;
    hash_destruir_dato_t parametro_de_destruccion;
};


hash_t *hash_crear(hash_destruir_dato_t destruir_dato) {
    hash_t *hash = malloc(sizeof(hash_t));
    if (!hash) return NULL;

    hash->capacidad = CAPACIDAD_INICIAL;
    hash->cantidad = 0;
    hash->parametro_de_destruccion = destruir_dato;
    hash->datos = calloc(hash->capacidad, sizeof(lista_t*));
    if (!hash->datos) {
        free(hash);
        return NULL;
    }
    
    for (int i = 0; i<hash->capacidad; i++){
        hash->datos[i] = lista_crear();
        if(!hash->datos[i]){
            for (int j=0; j<i;j++){
                free(hash->datos[j]); 
            }
            free(hash->datos);
            free(hash);
            return NULL;
        }
    }

    return hash;
}


bool hash_redimensionar(hash_t **hash, size_t nueva_capacidad) {
    //creamos un arreglo de datos nuevos
    void** datos_nuevos = calloc(nueva_capacidad, sizeof(lista_t*));
    if (!datos_nuevos) return NULL;

    for (int i = 0; i < nueva_capacidad; i++){
        datos_nuevos[i] = lista_crear();
        if(!datos_nuevos[i]){
            for (int j=0; j<i;j++) free(datos_nuevos[j]);
            free(datos_nuevos);
            return NULL;
        }
    }

    //pasamos los datos del hash al arreglo nuevo
    for (int i = 0; i < (*hash)->capacidad; i++) {
        lista_iter_t *iter = lista_iter_crear((*hash)->datos[i]);
        while (!lista_iter_al_final(iter)) {
            dato_t *dato = lista_iter_ver_actual(iter);
            size_t clave_hasheada = jenkins_hash((char*)dato->clave, strlen((dato->clave))) % nueva_capacidad; 
            lista_insertar_ultimo(datos_nuevos[clave_hasheada], dato);
            lista_iter_avanzar(iter);
        }
        lista_iter_destruir(iter);
        lista_destruir((*hash)->datos[i], NULL); //destruimos la lista
    }

    //reemplazamos los datos del hash original con los del auxiliar
    void **datos_a_destruir = (*hash)->datos;
    (*hash)->datos = datos_nuevos;
    (*hash)->capacidad = nueva_capacidad;

    //destruimos el hash auxiliar
    free(datos_a_destruir);

    //listo
    return true;
}


bool hash_guardar(hash_t *hash, const char *clave, void *dato) {
    if (hash_pertenece(hash, clave)) {
        void *valor = hash_borrar(hash, clave);
        if (hash->parametro_de_destruccion) hash->parametro_de_destruccion(valor);
    }

    size_t clave_hasheada = jenkins_hash((char*)clave, strlen(clave)) % hash->capacidad;
    char *copia_clave = malloc(strlen(clave) + 1); 
    strcpy(copia_clave, clave);
    dato_t *par_dato = dato_crear((char*)copia_clave, dato);
    if (!par_dato) return false;

    if (!lista_insertar_primero(hash->datos[clave_hasheada], par_dato)) return false;

    hash->cantidad++;

    if ((double)hash->cantidad/(double)hash->capacidad > 2.5) {
        size_t nueva_capacidad = (size_t)proximo_primo((int)(hash->capacidad*3));
        if (!hash_redimensionar(&hash, nueva_capacidad)) return false;
    }

    return true;
}


void *hash_borrar(hash_t *hash, const char *clave) {
    if (!hash_pertenece(hash, clave)) return NULL;

    size_t clave_hasheada = jenkins_hash((char*)clave, strlen(clave)) % hash->capacidad;

    lista_iter_t *iter = lista_iter_crear(hash->datos[clave_hasheada]);

    dato_t *dato = lista_iter_ver_actual(iter);
    while (strcmp(dato->clave, clave) != 0) {
        lista_iter_avanzar(iter);
        dato = lista_iter_ver_actual(iter);
    }

    lista_iter_borrar(iter);
    void* valor = dato->valor;
    dato_destruir(dato);
    hash->cantidad--;
    lista_iter_destruir(iter);

    if ((double)hash->cantidad/(double)hash->capacidad < 1 && ((int)hash->capacidad/2) > CAPACIDAD_INICIAL/2) {
        size_t nueva_capacidad = (size_t)proximo_primo((int)(hash->capacidad/2));
        if (nueva_capacidad > 0 && !hash_redimensionar(&hash, nueva_capacidad)) return false;
    }

    return valor;
}


void *hash_obtener(const hash_t *hash, const char *clave) {
    if (!hash_pertenece(hash, clave)) return NULL;

    size_t clave_hasheada = jenkins_hash((char*)clave, strlen(clave)) % hash->capacidad;

    lista_iter_t *iter = lista_iter_crear(hash->datos[clave_hasheada]);
    dato_t *dato = lista_iter_ver_actual(iter);
    while (strcmp(dato->clave, clave) != 0) {
        lista_iter_avanzar(iter);
        dato = lista_iter_ver_actual(iter);
    }

    lista_iter_destruir(iter);
    return dato->valor;
}


bool hash_pertenece(const hash_t *hash, const char *clave) {
    size_t clave_hasheada = jenkins_hash((char*)clave, strlen(clave)) % hash->capacidad;

    lista_iter_t *iter = lista_iter_crear(hash->datos[clave_hasheada]);

    while (!lista_iter_al_final(iter)) {
        dato_t *dato = lista_iter_ver_actual(iter);
        if (strcmp(dato->clave, clave) == 0) {
            lista_iter_destruir(iter);
            return true;
        }

        lista_iter_avanzar(iter);
    }

    lista_iter_destruir(iter);
    return false;
}


size_t hash_cantidad(const hash_t *hash) {
    return hash->cantidad;
}


void hash_destruir(hash_t *hash) {
    for (int i = 0; i < hash->capacidad; i++) {
        lista_iter_t *iter = lista_iter_crear(hash->datos[i]);
        while (!lista_iter_al_final(iter)) {
            dato_t *dato = lista_iter_borrar(iter);
            if (hash->parametro_de_destruccion) hash->parametro_de_destruccion(dato->valor);
            dato_destruir(dato);
            hash->cantidad--;
        }
        lista_iter_destruir(iter);
        lista_destruir(hash->datos[i], NULL);
    }
    free(hash->datos);
    free(hash);
}


/* Implementacion del iterador */


struct hash_iter {
    const hash_t *hash;
    size_t pos;
    lista_iter_t *iter_lista;
};


hash_iter_t *hash_iter_crear(const hash_t *hash) {
    hash_iter_t *iter = malloc(sizeof(hash_iter_t));
    if (!iter) return NULL;

    iter->hash = hash;
    iter->pos = 0;

    if (hash->cantidad == 0) iter->iter_lista = NULL;
    else {
        while (lista_esta_vacia(iter->hash->datos[iter->pos]) && iter->pos < iter->hash->capacidad) iter->pos++;
        iter->iter_lista = lista_iter_crear(hash->datos[iter->pos]); 
    }

    return iter;
}


bool hash_iter_al_final(const hash_iter_t *iter) {
    if (iter->hash->cantidad == 0) return true;
    if (!lista_iter_al_final(iter->iter_lista)) {
        return false;
    }

    for (size_t i = iter->pos+1; i < iter->hash->capacidad; i++) {
        if (!lista_esta_vacia(iter->hash->datos[i])) {
            return false;
        }
    }

    return true; 
}


bool hash_iter_avanzar(hash_iter_t *iter) {
    if (hash_iter_al_final(iter)) return false;
    
    if(!lista_iter_al_final(iter->iter_lista)){
        lista_iter_avanzar(iter->iter_lista);
        return true;
    }

    while(lista_iter_al_final(iter->iter_lista)){
        lista_iter_destruir(iter->iter_lista);
        iter->pos++;
        iter->iter_lista = lista_iter_crear(iter->hash->datos[iter->pos]);
    }

    return true;
}


const char *hash_iter_ver_actual(const hash_iter_t *iter) {
    if (hash_iter_al_final(iter)) return NULL;
    else if (lista_iter_al_final(iter->iter_lista)) hash_iter_avanzar((hash_iter_t *)iter);
    dato_t *dato = lista_iter_ver_actual(iter->iter_lista);
    return dato->clave;
}
   

void hash_iter_destruir(hash_iter_t *iter) {
    lista_iter_destruir(iter->iter_lista);
    free(iter);
}

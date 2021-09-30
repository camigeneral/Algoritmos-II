#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* La lista está planteada como un conjunto de punteros genéricos. */

struct lista;
typedef struct lista lista_t;

struct lista_iter;
typedef struct lista_iter lista_iter_t;

/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una lista vacia.
lista_t *lista_crear(void);

// Devuelve verdeadero si la lista esta vacia y falso en caso contarario.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro, para cada uno de los elementos de 
// la lista llama a destruir_dato.
// Pre: la lista fue creada.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));

// Agrega un elemento al principo de la lista, y devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agrego un elemento en el primer lugar de la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un elemento al final de la lista, y devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agrego un elemento en el ultimo lugar de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Devuelve el tamaño de la lista.
// Pre: la lista fue creada.
size_t lista_largo(const lista_t *lista);

// Borra el primer elemento de la lista. Si la lista no esta vacia, devuelve el valor del elemento que estaba 
// en el primer lugar, al contrario devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvio y luego elimino el elemento que estaba en el primer lugar.
void *lista_borrar_primero(lista_t *lista);

// Obtiene el valor del primer elemento de la lista. Si la lista no esta vacia, devuelve el valor del primer elemento, 
// al contrario devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, si es que no estaba vacia.
void *lista_ver_primero(const lista_t *lista);

// Obtiene el valor del ultimo elemento de la lista. Si la lista no esta vacia, devuelve el valor del ultimo elemento, 
// al contrario devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el ultimo elemento de la lista, si es que no estaba vacia.
void *lista_ver_ultimo(const lista_t* lista);

// Itera la lista y le aplica la funcion visitar() a los elementos hasta que esta devuelve falso.
// Pre: la lista fue creada.
// Post: se la aplico la funcion visitar() a los elementos indicados por la misma funcion.
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);


/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea un iterador y se lo asocia a la lista pasada por paramtro.
// Pre: la lista fue creada.
// Post: devuelve un iterador que apunta al primer elemento de la lista si es que existe, si la lista esta vacia
// apunta a NULL.
lista_iter_t *lista_iter_crear(lista_t *lista);

// Devuelve verdeadero si el iterador llego al final de la lista (apunta a NULL) y falso en caso contarario.
// Pre: el iterador fue creado.
bool lista_iter_al_final(const lista_iter_t *iter);

// Avanza un lugar en la lista y devuelve true. Si el iterador ya habia llegado al final de la lista devuelve false.
// Pre: el iterador fue creado.
// Post: se movio un elemento para adelante.
bool lista_iter_avanzar(lista_iter_t *iter);

// Muestra el elemento al que el iterador esta apuntando, o NULL si llego al final de lista.
// Pre: el iterador fue creado.
// Post: se devolvio el elemnto al que apunta el iterador, si es que apunta a algo diferente de NULL.
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Destruye el iterador.
// Pre: el iterador fue creado.
// Post: el iterador fue eliminado.
void lista_iter_destruir(lista_iter_t *iter);

// Inserta un elemento en el lugar donde apunta el iterador. El que estaba en ese lugar anteriormente ahora es el
// elemento que sigue al nuevo.
// Pre: el iterador fue creado. 
// Post: se agrego un elemento en la lista.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Borra el elemento que esta en el lugar donde apunta el iterador.
// Pre: el iterador fue creado. 
// Post: se borro un elemento de la lista.
void *lista_iter_borrar(lista_iter_t *iter);

/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/

// Realiza pruebas sobre la implementacion realizada.
//
// Las pruebas se emplean en el archivo ‘pruebas_lista.c’, y
// solamente emplean la interfaz pública tal y como aparece en lista.h
//
// Las pruebas utilizan la funcion print_test().

void pruebas_lista_estudiante(void);

#endif

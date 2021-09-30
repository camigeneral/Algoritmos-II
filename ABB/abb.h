#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


typedef struct abb abb_t;

typedef int (*abb_comparar_clave_t) (const char *, const char *);
typedef void (*abb_destruir_dato_t) (void *);

// Crea el abb
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

/* Guarda un elemento en el abb, si la clave ya se encuentra en la
* estructura, la reemplaza. De lo contrario devuelve false.
* Pre: la estructura fue inicializada
* Post: Se almacenó el par clave, valor
*/
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

/* Borra un elemento, y devuelve el dato asociado
* Retorna NULL en caso de no hayar el elemento.
* Pre: La estructura fue inicializada
* Post: El elemento fue borrado y se retornó el valor asociado
*/
void *abb_borrar(abb_t *arbol, const char *clave);

/* Obtiene el valor de un elemento del abb, si la clave no se encuentra
 * devuelve NULL.
 * Pre: El abb fue inicializado
 */
void *abb_obtener(const abb_t *arbol, const char *clave);

/* Determina si clave pertenece o no al abb.
 * Pre: El abb fue inicializado
 */
bool abb_pertenece(const abb_t *arbol, const char *clave);

/* Devuelve la cantidad de elementos del abb.
 * Pre: El abb fue inicializado
 */
size_t abb_cantidad(const abb_t *arbol);

/* Destruye la estructura liberando la memoria pedida y llamando a la función
 * destruir para cada par (clave, valor).
 * Pre: El abb fue inicializado
 * Post: El abb fue destruido
 */
void abb_destruir(abb_t *arbol);

/* Itera el abb hasta que se le indique lo contrario por función
* Pre: el abb fue inicializado
* Post: se recorrió un abb con hash
*/
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);   

typedef struct abb_iter abb_iter_t;

/* Crea iterador
* Pre: el abb fue inicializado
* Post: se creó un iterador para dicho árbol
*/
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

/* Se avanza una posición del iterador
* Pre: el iterador fue creado
* Post: el iterador avanzó una posición en el sentido inorder
*/
bool abb_iter_in_avanzar(abb_iter_t *iter);

/* Devuelve la clave de la posición en la que se encuentra el iterador
* Pre: el iterador fue creado
* Post: se retornó la clave del actual
*/
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

/* Comprueba si el iterador está al final del árbol
* Pre: el iterador fue creado
* Post: Retorna true si el iterador está sobre el elemento NULL
*/
bool abb_iter_in_al_final(const abb_iter_t *iter);

/* Destruye el iterador
* Pre: el iterador fue creado
* Post: se destruyó el iterador
*/
void abb_iter_in_destruir(abb_iter_t* iter);

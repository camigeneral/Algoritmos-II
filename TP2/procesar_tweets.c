#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "countminsketch.h"
#include "strutil.h"
#include "hash.h"
#include "heap.h"
#include "lista.h"

// -------------------------------------------------- TAGS --------------------------------------------------

typedef struct tag {
    char* clave;
    size_t* apariciones;
} tag_t;


tag_t* tag_crear(char* clave, size_t* apariciones) {
    tag_t* tag = malloc(sizeof(tag_t));
    if (!tag) return NULL;
    tag->clave = clave;
    tag->apariciones = apariciones;
    return tag;
}


void tag_destruir(void* tag) {
    //free(((tag_t*)tag)->apariciones);
	free(tag);
}

int comparar_tags(const void* a, const void* b) {
	tag_t* tag_a = (tag_t*)a;
	tag_t* tag_b = (tag_t*)b;
	if (*(tag_a->apariciones) == *(tag_b->apariciones)) return strcmp(tag_b->clave, tag_a->clave);
	else return (int)(*(tag_a->apariciones) - *(tag_b->apariciones));
}

// -------------------------------------------------- MAIN --------------------------------------------------

void guardar_tags_en_hash(cms_t* cms, hash_t* hash, char* tweet) {
	char** linea = split(tweet, ',');

	for (int k = 1; linea[k]; k++) {
		char *clave = strtok(linea[k], "\n");
		cms_guardar(cms, clave);
		size_t *apariciones = malloc(sizeof(size_t));
		*apariciones = cms_ver_cantidad(cms, clave);
		hash_guardar(hash, clave, apariciones);
	}

	free_strv(linea);
}


void obtener_trending_topics(cms_t* cms, hash_t* hash, int k) {
     hash_iter_t* iter = hash_iter_crear(hash);
     void** cantidades = malloc(sizeof(tag_t) * hash_cantidad(hash));
     size_t i = 0;

     while (!hash_iter_al_final(iter)) {
        char* clave = (char*)hash_iter_ver_actual(iter);
        size_t* apariciones = (size_t*)hash_obtener(hash, hash_iter_ver_actual(iter));
        cantidades[i] = tag_crear(clave, apariciones);
        i++;
        hash_iter_avanzar(iter);
    }
    
    hash_iter_destruir(iter);

    //heapify O(n)
    heap_t* heap = heap_crear_arr(cantidades, i, comparar_tags);
    free(cantidades);

	//desencolamos k veces O(klogn)
    for (int j = 0; j < k; j++) {
        tag_t* tag = heap_desencolar(heap);
        if (!tag) break;
		//buscamos la frecuencia del tag y actualizamos el hash global 
        size_t cant = cms_ver_cantidad(cms, tag->clave);

		//imprimimos
		printf("%ld %s\n", cant, tag->clave);

		//destruimos el tag
        tag_destruir(tag);
    }
	//free(cantidades);
    heap_destruir(heap, tag_destruir);
	hash_destruir(hash);
}


void procesar_archivo_tweets(int n, int k) {
	size_t tam = 128;
	char* tweet = NULL;

	cms_t* cms = cms_crear(50*n);                  //tda countminsketch
	int i = 1;                                    

	//recorremos el archivo
	while (getline(&tweet, &tam, stdin) != EOF) {
        hash_t* hash = hash_crear(tag_destruir);          //hash de los trending topics de las n lineas
		printf("--- %d\n", i);
		i++;

		//buscamos e imprimimos los trending topics de n lineas
		for (int j = 0; j < n; j++) {
			guardar_tags_en_hash(cms, hash, tweet);
			if (j != n-1) {
				if (getline(&tweet, &tam, stdin) == EOF) break;
			}
			
		}

		obtener_trending_topics(cms, hash, k);
	}
	free(tweet);

	//destruimos las estructuras auxiliares
	cms_destruir(cms);
}



int main(int argc, char* argv[]){
    procesar_archivo_tweets(atoi(argv[1]), atoi(argv[2]));
    return 0;
}


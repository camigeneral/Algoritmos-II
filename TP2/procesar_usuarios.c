#define _POSIX_C_SOURCE 200809L

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hash.h"
#include "hashing.h"
#include "lista.h"
#include "strutil.h"


// -----------------------------------------------------------------------------------------------------------------


void destruir_hash(void* hash) {
    hash_destruir((hash_t*)hash);
}

void imprimir_usuarios(char** usuarios_ordenados, size_t largo, int n) {
    printf("%d: ", n);
    for (int k = 0; k < largo; k++) {
        if (strcmp(usuarios_ordenados[k], "") != 0){
            char* usuario = strtok(usuarios_ordenados[k], "#");
            printf("%s", usuario);
        } 
        if (k+1 != largo) printf(", ");
    }
    printf("\n");
}


void counting_sort(char** arreglo, char** arreglo_ordenado, size_t tam, size_t pos) {
    int contador[256], frecuencia[256];
    memset(contador, 0, sizeof(contador));
    memset(frecuencia, 0, sizeof(frecuencia));

    for(int i = 0; i < tam; i++) contador[(int)arreglo[i][pos]]++;

    for(int i = 1; i < 255; i++) frecuencia[i] = contador[i-1] + frecuencia[i-1];

    for(int i = 0; i < tam; i++) {
        char* palabra = strndup(arreglo[i], strlen(arreglo[i]));
        arreglo_ordenado[frecuencia[(int)arreglo[i][pos]]] = palabra;
        frecuencia[(int)arreglo[i][pos]]++;
    }

	for (int i = 0; i<tam; i++){
		char* dato_a_destruir = arreglo[i];
		arreglo[i] = arreglo_ordenado[i];
		free(dato_a_destruir);
	}

	return;
}


void radix_sort(char** arreglo, char** arreglo_ordenado, size_t tam) {
    for (int j = 14; j >= 0; j--) counting_sort(arreglo, arreglo_ordenado, tam, j);
	return;
}


void igualar_cadenas(char* usuario, char* u2) {
	size_t largo = strlen(usuario);
	char buff = '#';
    strcpy(u2, usuario);
    memset(&u2[largo], buff, 16-largo);
}


void ordenar_arreglo(void** arreglo, size_t tam) {
    for (int i = 1; i < tam+1; i++) {
        //para cada lista en el arreglo armo un subarreglo que contine los usuarios 
        size_t len = lista_largo(arreglo[i]);
        char* usuarios[len];
        memset(usuarios, '\0', len);
        lista_iter_t* iter = lista_iter_crear((lista_t*)arreglo[i]);
        for (int j = 0; j < len; j++) {
            char* usuario = lista_iter_ver_actual(iter);
			char *u2 = calloc(17*sizeof(char), sizeof(char));
            igualar_cadenas(usuario, u2);
            usuarios[j] = u2;
            lista_iter_avanzar(iter);
        }
        lista_iter_destruir(iter);
        
        //ordeno el subarreglo y lo guardo en el arreglo ordenado
		char* usuarios_ordenados[len];
		memset(usuarios_ordenados, 'a', len);

        radix_sort(usuarios, usuarios_ordenados, len);
		
		//imprimo
        if (strcmp(arreglo[i], "") != 0) imprimir_usuarios(usuarios_ordenados, len, i);
    	
		//destruyo los vectores
		for (int k = 0; k < len; k++) free(usuarios[k]);
		lista_destruir(arreglo[i], free);
        
	}
	lista_destruir(arreglo[0], NULL);
    return;
}


void crear_arreglo_usuarios(hash_t* hash_global, void** arreglo_usuarios, size_t tam){
	for (int i = 0; i < tam+1; i++) {
		lista_t* lista = lista_crear();
		arreglo_usuarios[i] = lista;
	}

	hash_iter_t* iter = hash_iter_crear(hash_global);
	while (!hash_iter_al_final(iter)) {
		const char* usuario = hash_iter_ver_actual(iter);
		hash_t* hash_usuario = hash_obtener(hash_global, usuario);
		size_t cant_tags = hash_cantidad(hash_usuario);
		char* copia_usuario = strdup(usuario);
		lista_insertar_ultimo(arreglo_usuarios[cant_tags], copia_usuario);
		hash_iter_avanzar(iter);
	}
	hash_iter_destruir(iter);
	return; 
}


hash_t* crear_hash_usuarios(size_t* rango, char** argv) {
	//creamos un hash para guardar los tags que uso cada usuario: hash_global = {usuario1: {tag1, tag2}, usuario2: ...}
    hash_t* hash_global = hash_crear(destruir_hash);

    const char* archivo = argv[1];
    FILE* arch = fopen(archivo, "r");
    size_t tam = 512;
    char* tweet = malloc(512*sizeof(char));

    while (getline(&tweet, &tam, arch) != EOF) {
        char** linea = split(tweet, ',');
        char* usuario = linea[0];

		//creamos el hash del usuario	
		if (!hash_pertenece(hash_global, usuario)) {
			hash_t* hash_usuario = hash_crear(NULL);
            hash_guardar(hash_global, usuario, hash_usuario);
		}

		//guardamos los tags
		hash_t* hash_usuario = hash_obtener(hash_global, usuario);
		
        for (int i = 1; linea[i]; i++) {
            char* tag = strtok(linea[i], "\n");
            hash_guardar(hash_usuario, tag, 0);
        }
		size_t cant_tags = hash_cantidad(hash_usuario);

		//actualizamos el rango
		if (cant_tags > *rango) *rango = cant_tags;
		free_strv(linea);
	}

	free(tweet);
    fclose(arch);
	return hash_global;
}


int procesar_archivo_usuarios(char** argv) {
    //reccoro el archivo y guardo los usuarios y los tags que uso cada uno en un hash
	size_t* rango = calloc(1, sizeof(size_t*));
    hash_t* hash_global = crear_hash_usuarios(rango, argv);
    
    //paso los usuarios a un arreglo
    void* arreglo_usuarios = calloc(*rango+1, sizeof(char*)); 
    crear_arreglo_usuarios(hash_global, arreglo_usuarios, *rango);	
    
	//ordeno e imprimo el arreglo
    ordenar_arreglo(arreglo_usuarios, *rango);
   
    //destruyo las estructuras auxiliares
	hash_destruir(hash_global);
	free(arreglo_usuarios);
	free(rango);

	return 0;
}


int main(int argc, char* argv[]) {
    return procesar_archivo_usuarios(argv);
}

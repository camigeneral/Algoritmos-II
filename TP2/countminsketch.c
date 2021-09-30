#include <stdio.h>
#include <stdlib.h>
#include "countminsketch.h"
#include "hashing.h"


int calcular_min(int a, int b, int c, int d, int e){
    int minimo_total = a;
    if (b < minimo_total) minimo_total = b;
    if (c < minimo_total) minimo_total = c;
    if (d < minimo_total) minimo_total = d;
    if (e < minimo_total) minimo_total = e;
    return minimo_total;
}


struct countminsketch{
    size_t cantidad;
    int *datos1, *datos2, *datos3, *datos4, *datos5;
};

cms_t* cms_crear(size_t cantidad){
    cms_t* cms = malloc(sizeof(cms_t));
    if (!cms) return NULL;

    cms->cantidad = cantidad;

    int *datos1 = malloc(cantidad*sizeof(int));
    int *datos2 = malloc(cantidad*sizeof(int));
    int *datos3 = malloc(cantidad*sizeof(int));
    int *datos4 = malloc(cantidad*sizeof(int));
    int *datos5 = malloc(cantidad*sizeof(int));

    for (int i = 0; i < cantidad; i++) {
        datos1[i] = 0;
        datos2[i] = 0;
        datos3[i] = 0;
        datos4[i] = 0;
        datos5[i] = 0;
    }

    cms->datos1 = datos1;
    cms->datos2 = datos2;
    cms->datos3 = datos3;
    cms->datos4 = datos4;
    cms->datos5 = datos5;

    return cms;
}

void cms_destruir(cms_t* cms) {
    free(cms->datos1);
    free(cms->datos2);
    free(cms->datos3);
    free(cms->datos4);
    free(cms->datos5);
    free(cms);
}

void cms_guardar(cms_t* cms, char* clave) {
    size_t hash1 = jenkins_hash(clave, strlen(clave)) % cms->cantidad;
    size_t hash2 = murmurOAAT32(clave) % cms->cantidad;
    size_t hash3 = cami_hash(clave) % cms->cantidad;
    size_t hash4 = peti_hash1(clave) % cms->cantidad;
    size_t hash5 = peti_hash2(clave) % cms->cantidad;

    cms->datos1[hash1]++;
    cms->datos2[hash2]++;
    cms->datos3[hash3]++;
    cms->datos4[hash4]++;
    cms->datos5[hash5]++;

    return;
}

size_t cms_ver_cantidad(cms_t* cms, char* clave) {
	size_t hash1 = jenkins_hash(clave, strlen(clave)) % cms->cantidad;
    size_t hash2 = murmurOAAT32(clave) % cms->cantidad;
    size_t hash3 = cami_hash(clave) % cms->cantidad;
    size_t hash4 = peti_hash1(clave) % cms->cantidad;
    size_t hash5 = peti_hash2(clave) % cms->cantidad;

    size_t minimo = (size_t)calcular_min(cms->datos1[hash1], cms->datos2[hash2], cms->datos3[hash3], cms->datos4[hash4],cms->datos5[hash5]);

	return minimo;
}

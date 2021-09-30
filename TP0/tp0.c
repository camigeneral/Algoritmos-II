#include "tp0.h"
#include <stdio.h>

/* *****************************************************************
 *                     FUNCIONES A COMPLETAR                       *
 *         (ver en tp0.h la documentación de cada función)         *
 * *****************************************************************/

void swap(int *x, int *y) {
    /* Intercambia dos valores enteros.*/
    int aux = *x;
    *x = *y;
    *y = aux;
}


int maximo(int vector[], int n) {
    /* Devuelve la posición del mayor elemento del arreglo, o -1 si el
     * el vector es de largo 0.*/
    if (n == 0) {
        return -1;
    }

    else if (n == 1) {
        return 0;
    }

    if (vector[maximo(vector, n-1)] < vector[n-1]) {
        return n-1;
    }   

    return maximo(vector, n-1);
}


int comparar(int vector1[], int n1, int vector2[], int n2) {
    /* Compara dos arreglos de longitud especificada y devuelve -1 si el primer es menor, 1 si el segundo es menor o 0 si son iguales*/
    for (int i = 0; i < n1; i++) {
        if (i >= n2) {
            return 1;
        }
        if (vector1[i] > vector2[i]) {
            return 1;
        }
        else if (vector1[i] < vector2[i]) {
            return -1;
        }
    }

    if (n2 > n1) {
        return -1;
    }

    return 0;
}


void seleccion(int vector[], int n) {
    /* Ordena el arreglo recibido mediante el algoritmo de selección. */
    for (int i = n-1; i > 0; i--) {
        int max_indice = maximo(vector, i);
        if (vector[max_indice] > vector[i]){
            swap(&vector[i], &vector[max_indice]);
        }
    }
}

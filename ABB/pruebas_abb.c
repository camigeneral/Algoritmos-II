#include "abb.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool suman_30(const char* clave, void* valor, void* suma_con_corte){
    if (*(int*)suma_con_corte + *(int*)valor < 30){
        *(int*)suma_con_corte += *(int*)valor;
        return true;
    }
    return false;
}


int comparacion_menores(const char* valor1, const char* valor2){
    size_t largo1 = strlen(valor1);
    size_t largo2 = strlen(valor2);
    if (largo1 > largo2) return 1;
    else if (largo1 < largo2) return 2;
    return 0;
}


void prueba_crear_abb_vacio() {
    abb_t* abb = abb_crear(strcmp, NULL);

    print_test("> Se creó un árbol", abb);
    print_test("> Cantidad de elementos es 0", abb_cantidad(abb) == 0);
    print_test("> Obtener clave en abb vacío es NULL", !abb_obtener(abb, "A"));
    print_test("> Comprobar pertenencia de clave inexistente, retorna false", !abb_pertenece(abb, "A"));
    print_test("> Borra en un abb vacío retorna NULL", !abb_borrar(abb, "A"));

    abb_destruir(abb);
}


void prueba_iterar_abb_vacio() {
    abb_t* abb = abb_crear(strcmp, NULL);
    abb_iter_t* iter = abb_iter_in_crear(abb);

    print_test("> Se creó un árbol", abb);
    print_test("> Se creó un iterador", iter);
    print_test("> Prueba abb iter crear en arbol vacio", iter);
    print_test("> Iter está al final", abb_iter_in_al_final(iter));
    print_test("> Iter avanzar retorna false", !abb_iter_in_avanzar(iter));
    print_test("> Iter ver actual es NULL", !abb_iter_in_ver_actual(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}


void prueba_abb_insertar() {
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "Superman", *valor1 = "Kent";
    char *clave2 = "Batman", *valor2 = "Wayne";
    char *clave3 = "Iron Man", *valor3 = "Stark";

    print_test("> Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("> Prueba abb cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("> Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("> Prueba abb pertenece clave1, es true", abb_pertenece(abb, clave1));

    print_test("> Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("> Prueba abb cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("> Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("> Prueba abb pertenece clave2, es true", abb_pertenece(abb, clave2));

    print_test("> Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("> Prueba abb cantidad de elementos es 3", abb_cantidad(abb) == 3);
    print_test("> Prueba abb obtener clave1 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("> Prueba abb pertenece clave3, es true", abb_pertenece(abb, clave3));
    print_test("> Prueba abb borrar clave3, es valor3", abb_borrar(abb, clave3) == valor3);
    print_test("> Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    abb_destruir(abb);
}


void prueba_abb_borrar() {
    abb_t* abb = abb_crear(strcmp, NULL);

    char *claves[] = {"7", "4", "3", "1", "2", "5", "6", "9", "8", "10"};
    char *valores[] = {"siete", "cuatro", "tres", "uno", "dos", "cinco", "seis", "nueve", "ocho", "diez"};
    bool ok;

    for (int i = 0; i < 10; i++) {
        ok = abb_guardar(abb, claves[i], valores[i]);
    }

    print_test("> Prueba insertar el 10 valores", ok);
    print_test("> Prueba abb cantidad de elementos es 10", abb_cantidad(abb) == 10);

    //borramos un nodo con dos hijos (el 7)
    print_test("> Prueba borrar un nodo con dos hijos", abb_borrar(abb, claves[0]) == valores[0]);
    print_test("> Prueba abb pertenece la clave borrada es false", !abb_pertenece(abb, claves[0]));
    print_test("> Prueba obtener la clave borrada devuelve NULL", abb_obtener(abb, claves[0]) == NULL);
    print_test("> Prueba borrar la clave de nuevo", !abb_borrar(abb, claves[0]));
    print_test("> Prueba abb cantidad de elementos es 9", abb_cantidad(abb) == 9);

    //borramos el que estaba a la izquierda del anterior (el 4)
    print_test("> Prueba borrar el nodo que esta a la izquierda del anterior", abb_borrar(abb, claves[1]) == valores[1]);
    print_test("> Prueba abb pertenece la clave borrada es false", !abb_pertenece(abb, claves[1]));
    print_test("> Prueba obtener la clave borrada devuelve NULL", abb_obtener(abb, claves[1]) == NULL);
    print_test("> Prueba borrar la clave de nuevo", !abb_borrar(abb, claves[1]));
    print_test("> Prueba abb cantidad de elementos es 8", abb_cantidad(abb) == 8);
    
    //borramos el que estaba a la derecha del anterior (el 9)
    print_test("> Prueba borrar el nodo que esta a la izquierda del anterior", abb_borrar(abb, claves[7]) == valores[7]);
    print_test("> Prueba abb pertenece la clave borrada es false", !abb_pertenece(abb, claves[7]));
    print_test("> Prueba obtener la clave borrada devuelve NULL", abb_obtener(abb, claves[7]) == NULL);
    print_test("> Prueba borrar la clave de nuevo", !abb_borrar(abb, claves[7]));
    print_test("> Prueba abb cantidad de elementos es 7", abb_cantidad(abb) == 7);

    //borramos el nodo con el que reemplazamos el que tenia dos hijos (el 6)
    print_test("> Prueba borrar el nodo que reemplazo al nodo con dos hijos", abb_borrar(abb, claves[6]) == valores[6]);
    print_test("> Prueba abb pertenece la clave borrada es false", !abb_pertenece(abb, claves[6]));
    print_test("> Prueba obtener la clave borrada devuelve NULL", abb_obtener(abb, claves[6]) == NULL);
    print_test("> Prueba borrar la clave de nuevo", !abb_borrar(abb, claves[6]));
    print_test("> Prueba abb cantidad de elementos es 6", abb_cantidad(abb) == 6);
    
    //borramos un nodo con 1 hijo (el 1)
    print_test("> Prueba borrar nodo con un hijo", abb_borrar(abb, claves[3]) == valores[3]);
    print_test("> Prueba abb pertenece la clave borrada es false", !abb_pertenece(abb, claves[3]));
    print_test("> Prueba obtener la clave borrada devuelve NULL", abb_obtener(abb, claves[3]) == NULL);
    print_test("> Prueba borrar la clave de nuevo", !abb_borrar(abb, claves[3]));
    print_test("> Prueba abb cantidad de elementos es 5", abb_cantidad(abb) == 5);

    //borramos un nodo sin hijos (el 10)
    print_test("> Prueba borrar nodo sin hijos", abb_borrar(abb, claves[9]) == valores[9]);
    print_test("> Prueba abb pertenece la clave borrada es false", !abb_pertenece(abb, claves[9]));
    print_test("> Prueba obtener la clave borrada devuelve NULL", abb_obtener(abb, claves[9]) == NULL);
    print_test("> Prueba borrar la clave de nuevo", !abb_borrar(abb, claves[9]));
    print_test("> Prueba abb cantidad de elementos es 4", abb_cantidad(abb) == 4);
    
    //borramos los nodos que quedan
    abb_borrar(abb, claves[2]);
    abb_borrar(abb, claves[5]);
    abb_borrar(abb, claves[4]);
    print_test("> Prueba borrar los nodos que quedan", abb_borrar(abb, claves[8]) == valores[8]);
    print_test("> Prueba abb cantidad de elementos es 0", abb_cantidad(abb) == 0);   
    
    abb_destruir(abb);
}


void prueba_insertar_clave_vacia() {
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave = "", *valor = "";

    print_test("> Prueba abb insertar clave vacia", abb_guardar(abb, clave, valor));
    print_test("> Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("> Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("> Prueba abb obtener clave vacia es valor", abb_obtener(abb, clave) == valor);
    print_test("> Prueba abb borrar clave vacia, es valor", abb_borrar(abb, clave) == valor);
    print_test("> Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}


void prueba_insertar_null() {
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave = "", *valor = NULL;

    print_test("> Prueba abb insertar NULL", abb_guardar(abb, clave, valor));
    print_test("> Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("> Prueba abb pertenece clave, es true", abb_pertenece(abb, clave));
    print_test("> Prueba abb obtener clave es NULL", abb_obtener(abb, clave) == valor);
    print_test("> Prueba abb borrar clave, es NULL", abb_borrar(abb, clave) == valor);
    print_test("> Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);

}


void prueba_abb_reemplazar() {
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "Charly", *valor1a = "Fanky", *valor1b = "Rezo por vos";
    char *clave2 = "Cerati", *valor2a = "Crimen", *valor2b = "Cactus";

    print_test("> Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("> Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("> Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("> Prueba abb obtener clave1 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("> Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("> Prueba reemplazar el valor de clave1 con otro", abb_guardar(abb, clave1, valor1b));
    print_test("> Prueba reemplazar el valor de clave2 con otro", abb_guardar(abb, clave2, valor2b));
    print_test("> Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("> Prueba abb obtener clave1 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("> Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    abb_destruir(abb);
}


void prueba_abb_reemplazar_destruir() {
    abb_t* abb = abb_crear(strcmp, free);

    char* clave1 = "uno";
    char* clave2 = "dos";
    char* valor1a = malloc(10 * sizeof(char));
    char* valor1b = malloc(10 * sizeof(char));
    char* valor2a = malloc(10 * sizeof(char));
    char* valor2b = malloc(10 * sizeof(char));

    print_test("> Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("> Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("> Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("> Prueba abb obtener clave1 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("> Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("> Prueba reemplazar el valor de clave1 con otro", abb_guardar(abb, clave1, valor1b));
    print_test("> Prueba reemplazar el valor de clave2 con otro", abb_guardar(abb, clave2, valor2b));
    print_test("> Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("> Prueba abb obtener clave1 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("> Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    abb_destruir(abb);
}


bool sumar(const char* clave, void* valor, void* extra) {
    *(int*) extra += *(int*) valor;
    return true;
}


void prueba_abb_iterador_interno() {
    abb_t* abb = abb_crear(strcmp, NULL);

    unsigned largo = 20;
    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);

    int* valores[largo];

    bool ok = true;
    for (int i = 0; i < largo; i++) {
        valores[i] = malloc(sizeof(int));
        sprintf(claves[i], "%08d", i);
        *valores[i] = i;
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    print_test("> Prueba abb guardar 19 elementos", ok);
    int suma = 0;
    abb_in_order(abb, sumar, &suma);
    print_test("> Prueba sumar todos los elementos del arbol", suma == 190);

    for (size_t i = 0; i < largo; i++) free(valores[i]);
    free(claves); 

    abb_destruir(abb);

    abb_t* abb2 = abb_crear(strcmp, NULL);

    char* claves2[] = {"20", "18", "10", "0", "1", "19", "24", "22", "30", "28", "29"};
    int valores2[] = {20, 18, 10, 6, 8, 19, 24, 22, 30, 28, 29};
    for (int i = 0; i < 11; i++) {
        abb_guardar(abb2, claves2[i], &valores2[i]);
    }
    
    suma = 0;
    abb_in_order(abb2, suman_30, &suma);
    print_test("> Prueba sumar todos los elementos del arbol", suma == 24);

    abb_destruir(abb2);    
}


void prueba_abb_volumen() {
    abb_t* abb = abb_crear(strcmp, NULL);

    unsigned largo = 5000;
    const size_t largo_clave = 1000;
    char **claves = malloc(largo * largo_clave);
    int* valores[largo];
    bool ok = true;

    for (int i = 0; i < largo; i++) {
        int num_clave = rand();
        char* clave = malloc(largo_clave*sizeof(char));
        sprintf(clave, "%08d", num_clave);
        claves[i] = clave;
        valores[i] = malloc(sizeof(int));
        *valores[i] = i;
        
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }
    
    print_test("> Prueba abb guardar 5000 elementos", ok);
    print_test("> Prueba abb la cantidad de elementos guardados es 5000", abb_cantidad(abb) == largo);
    
    for (size_t i = 0; i < largo; i++) {
        ok = abb_pertenece(abb, claves[i]);
        if (!ok) break;
        ok = abb_obtener(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    print_test("> Prueba abb pertenece y obtener los 5000 elementos", ok);

    for (size_t i = 0; i < largo; i++) {
        ok = abb_borrar(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    print_test("> Prueba abb borrar 5000 elementos", ok);
    print_test("> Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    for (size_t i = 0; i < largo; i++) free(valores[i]);
    for (size_t i = 0; i < largo; i++) free(claves[i]);
    free(claves);
    abb_destruir(abb);
}


void prubea_abb_iterar() {
    abb_t* abb = abb_crear(strcmp, NULL);

    char *claves[] = {"Iron Man", "Superman", "Batman"};
    char *valores[] = {"Stark", "Kent", "Wayne"};

    print_test("> Prueba abb insertar clave1", abb_guardar(abb, claves[0], valores[0]));
    print_test("> Prueba abb insertar clave2", abb_guardar(abb, claves[1], valores[1]));
    print_test("> Prueba abb insertar clave3", abb_guardar(abb, claves[2], valores[2]));

    abb_iter_t* iter = abb_iter_in_crear(abb);
    const char *clave;

    print_test("> Prueba abb iterador no esta al final", !abb_iter_in_al_final(iter));

    clave = abb_iter_in_ver_actual(iter);
    print_test("> Prueba abb iterador ver actual devuelve la clave correcta", strcmp(clave,claves[2]) == 0);
    print_test("> Prueba abb iterador ver actual no es el mismo puntero", clave != claves[2]);
    print_test("> Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("> Prueba abb iterador esta al final es false", !abb_iter_in_al_final(iter));

    clave = abb_iter_in_ver_actual(iter);
    print_test("> Prueba abb iterador ver actual devuelve la clave correcta", strcmp(clave, claves[0]) == 0);
    print_test("> Prueba abb iterador ver actual no es el mismo puntero", clave != claves[0]);
    print_test("> Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("> Prueba abb iterador esta al final es false", !abb_iter_in_al_final(iter)); 

    clave = abb_iter_in_ver_actual(iter);
    print_test("> Prueba abb iterador ver actual devuelve la clave correcta", strcmp(clave,claves[1]) == 0);
    print_test("> Prueba abb iterador ver actual no es el mismo puntero", clave != claves[1]);
    print_test("> Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("> Prueba abb iterador esta al final", abb_iter_in_al_final(iter));
    print_test("> Prueba abb iterador ver actual es NULL", !abb_iter_in_ver_actual(iter));
    print_test("> Prueba abb iterador avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("> Prueba abb iterador esta al final", abb_iter_in_al_final(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}


void pruebas_comparacion_alternativas(){

    abb_t* abb = abb_crear(comparacion_menores, NULL);

    char *clave1 = "diez", *valor1 = "10"; 
    char *clave2 = "catorce", *valor2 = "14";
    char *clave3 = "siete", *valor3 = "7";

    print_test("> Prueba abb insertar primer clave", abb_guardar(abb, clave1, valor1));
    print_test("> Prueba abb cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("> Prueba abb obtener primer clave es primer valor", abb_obtener(abb, clave1) == valor1);
    print_test("> Prueba abb pertenece primer clave, es true", abb_pertenece(abb, clave1));

    print_test("> Prueba abb insertar segunda clave", abb_guardar(abb, clave2, valor2));
    print_test("> Prueba abb cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("> Prueba abb obtener segunda clave es segundo valor", abb_obtener(abb, clave2) == valor2);
    print_test("> Prueba abb pertenece segunda clave, es true", abb_pertenece(abb, clave2));

    print_test("> Prueba abb insertar tercer clave", abb_guardar(abb, clave3, valor3));
    print_test("> Prueba abb cantidad de elementos es 3", abb_cantidad(abb) == 3);
    print_test("> Prueba abb obtener tercer clave es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("> Prueba abb pertenece tercer clave, es true", abb_pertenece(abb, clave3));
    print_test("> Prueba abb borrar tercer clave, es valor3", abb_borrar(abb, clave3) == valor3);
    print_test("> Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    abb_destruir(abb);
} 


void prueba_abb_iterar_volumen() {
    abb_t* abb = abb_crear(strcmp, NULL);

    unsigned largo = 1000;
    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);
    int* valores[largo];
    bool ok = true;

    for (int i = 0; i < largo; i++) {
        valores[i] = malloc(sizeof(int));
        sprintf(claves[i], "%08d", i);
        *valores[i] = i;
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("> Prueba crear el iterador", iter);
    print_test("> Prueba abb iterador no esta al final", !abb_iter_in_al_final(iter));

    ok = true;
    unsigned i;
    const char *clave;
    size_t *valor;

    for (i = 0; i < largo; i++) {
        if (abb_iter_in_al_final(iter)) {
            ok = false;
            break;
        }
        clave = abb_iter_in_ver_actual(iter);
        if (!clave) {
            ok = false;
            break;
        }
        valor = abb_obtener(abb, clave);
        if (!valor) {
            ok = false;
            break;
        }
        abb_iter_in_avanzar(iter);
    }

    print_test("> Prueba iterar por 1000 elementos", ok);
    print_test("> Prueba iterador esta al final", abb_iter_in_al_final(iter));

    for (size_t j = 0; j < largo; j++) free(valores[j]);
    free(claves);
    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}


void pruebas_abb_estudiante() {
    printf("PRUEBAS ABB VACIO\n");
    prueba_crear_abb_vacio(); 
    printf("\n\n");
    printf("PRUEBAS ABB ITERAR VACIO\n");
    prueba_iterar_abb_vacio();
    printf("\n\n");
    printf("PRUEBAS ABB INSERTAR\n");
    prueba_abb_insertar();
    printf("\n\n");
    printf("PRUEBAS ABB BORRAR\n");
    prueba_abb_borrar();
    printf("\n\n");
    printf("PRUEBAS CLAVE VACIA\n");
    prueba_insertar_clave_vacia();
    printf("\n\n");
    printf("PRUEBAS VALOR NULL\n");
    prueba_insertar_null();
    printf("\n\n");
    printf("PRUEBAS REEMPLAZAR\n");
    prueba_abb_reemplazar();
    printf("\n\n");
    printf("PRUEBAS REEMPLAZAR CON DESTRUIR\n");
    prueba_abb_reemplazar_destruir();
    printf("\n\n"); 
    printf("PRUEBAS ITERADOR INTERNO\n");
    prueba_abb_iterador_interno();
    printf("\n\n");
    printf("PRUEBAS DE VOLUMEN\n");
    prueba_abb_volumen();
    printf("\n\n");
    printf("PRUEBAS ITERADOR\n");
    prubea_abb_iterar();
    printf("\n\n");
    printf ("PRUEBAS COMPARACION ALTERNATIVAS\n");
    pruebas_comparacion_alternativas(); 
    printf("\n\n");
    printf("PRUEBAS ITERADOR DE VOLUMEN\n"); 
    prueba_abb_iterar_volumen(); 
}


#ifndef CORRECTOR

int main() {
    pruebas_abb_estudiante();
    return 0;
}

#endif 

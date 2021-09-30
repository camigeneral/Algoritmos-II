#include <stdio.h>
#include "strutil.h"
#include <string.h>
#include <stdlib.h>
#define _POSIX_C_SOURCE 200809L


char *substr(const char *str, size_t n) {
    char *substr = malloc(sizeof(char)*(n+1));
    if (!substr) return NULL;
    strncpy(substr, str, n);
    substr[n] = '\0';
    return substr;
}


char **split(const char *str, char sep) {
    size_t separadores = 0;
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] == sep) separadores++; 
    }

    char **splitstr = malloc(sizeof(char*)*(separadores + 2));
    if (!splitstr) return NULL;

    size_t pos = 0; //posicion en el arreglo de cada subcadena
    size_t inicio = 0; //donde empieza cada subcadena con respecto a la cadena inicial
    size_t len = strlen(str); //largo de la cadena inicial
    int chars = 0; //caracteres en cada subcadena

    for (size_t i = 0; i < len; i++) {
        if (str[i] == sep) {
            splitstr[pos] = substr(str+inicio, chars);
            inicio = i+1;
            pos++;
            chars = -1;
        }
        chars++;
    }

    splitstr[separadores] = substr(str+inicio, chars);
    splitstr[separadores+1] = NULL;

    return splitstr;
}
     

char *join(char **strv, char sep) {
    size_t largo = 0;
    size_t separadores = 0;
    size_t len_sep = 1;
    int separador_nulo = strcmp(&sep, "\0"); //0 si el separador es \0

   for (int i = 0; strv[i]; i++) {
        largo += strlen(strv[i]);
        separadores += 1; //separadores va a terminar siendo uno mas de la cant de separadores que necesito
    } 

    if (separador_nulo == 0) {
        len_sep = 0; //si el separador es \0 junto las subcadenas sin separador
        separadores = 1; //uno para tener espacio para el \0
    }

    if (largo == 0 && separadores <= 1) {
        char *str = malloc(sizeof(char));
        str[0] = '\0';
        return str;
    }

    char *str = malloc(sizeof(char)*(largo+separadores)); //el +1 del '\0' ya esta incluido en separadores
    if (!str) return NULL;

    size_t inicio = 0;

    for (int i = 0; strv[i]; i++) {
        size_t len = strlen(strv[i]);
        strcpy(str+inicio, strv[i]);
        inicio += len + len_sep;
        if (separador_nulo != 0) *(str+inicio-1) = sep;
    }

    str[inicio-len_sep] = '\0';
    return str;
}


void free_strv(char *strv[]) {
    for (int i = 0; strv[i]; i++) free(strv[i]);
    free(strv);
}


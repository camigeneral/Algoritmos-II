#include "calc_helper.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct calc_token *token_crear() {
    struct calc_token *token = malloc(sizeof(struct calc_token));
    if (!token) return NULL;
    token->type = 0;
    return token;
}


bool chequar_operacion_valida(int op, int a, int b, int c) {
    if ((op == 3 && a == 0) || (op == 4 && a < 0) || (op == 5 && a < 2) || (op == 6 && a < 0)) return false;
    return true;
}


int aplicar_operacion(int op, int a, int b, int c) {
    if (op == OP_ADD) return b+a;
    else if (op == OP_SUB) return b-a;
    else if (op == OP_MUL) return b*a;
    else if (op == OP_DIV) return b/a;
    else if (op == OP_POW) return floor(pow(b,a));
    else if (op == OP_LOG) return floor(log(b)/log(a));
    else if (op == OP_RAIZ) return floor(sqrt(a));
    else return c?b:a; 
}


int operar(char **operacion, calc_num *num_resultado) {
    pilanum_t *pila = pilanum_crear(); //solo contiene numeros (no el token entero)

    for (int i = 0; operacion[i] != NULL; i++) {
        //creo el token a liberar
        struct calc_token *token = token_crear();

        //si el token no se creo o si no es un token valido return
        if (!token || !calc_parse(operacion[i], token) || token->type == 2 || token->type == 3) {
            free(token);
            pilanum_destruir(pila);
            return 0;
        }

        //si el token es un numero apilo el valor 
        else if (token->type == 0) {
            apilar_num(pila, token->value);
            free(token);
        }

        //si el token es un operador desapilo la cantidad de operandos necesaria, opero, y apilo el resultado
         else if (token->type == 1) {
            calc_num resultado;
 
            if (token->oper.num_operandos == 3) {
                calc_num a, b, c;
                bool v1 = desapilar_num(pila, &a);
                bool v2 = desapilar_num(pila, &b);
                bool v3 = desapilar_num(pila, &c);
            }

            else if (token->oper.num_operandos == 2) {
                calc_num a, b, c = 0;
                bool v1 = desapilar_num(pila, &a);
                bool v2 = desapilar_num(pila, &b);
                bool v3 = true;
            }

            else {
                calc_num a; b = 0, c = 0;
                bool v1 = desapilar_num(pila, &a);
                bool v2 = true;
                bool v3 = true;
            }

            if (!v1 || !v2 || !v3 || !chequar_operacion_valida(token->oper.op, (int)a, (int)b, (int)c)) {
                free(token);
                pilanum_destruir(pila);
                return 0;
            }

            resultado = (calc_num)aplicar_operacion(token->oper.op, (int)a, (int)b, (int)c);
            apilar_num(pila, resultado);
            free(token);
        }
    }

    //desapilo el resultado final
    desapilar_num(pila, num_resultado);

    //chequeo que la pila haya quedado vacia
    if (!pilanum_esta_vacia(pila)) {
        pilanum_destruir(pila);   
        return 0;
    }

    //destuyo la pila
    pilanum_destruir(pila);
    
    return 1;
}


int leer_op() {
    size_t tam = 32;
    char *op = malloc(tam*sizeof(char));
    if (!op) return 1;

    while (getline(&op, &tam, stdin) != EOF) {
        char **operacion = dc_split(op);
        calc_num resultado = 0;
        int valido = operar(operacion, &resultado);

        if (valido == 0) printf("ERROR\n");
        else printf("%ld\n", resultado);

        for (int i = 0; operacion[i] != NULL; i++) {
            free(operacion[i]);
        }

        free(operacion);
    }

    free(op);
    return 0;    
}


int main() {
    return leer_op();
}

#include "calc_helper.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct calc_token *token_crear() {
    struct calc_token *token = malloc(sizeof(struct calc_token));
    if (!token) return NULL;
    token->type = 0;
    return token;
}


void imprimir_operador(struct calc_token *operador) {
    if (operador->oper.op == OP_ADD) printf ("+ ");
    else if (operador->oper.op == OP_SUB) printf ("- ");
    else if (operador->oper.op == OP_MUL) printf ("* ");
    else if (operador->oper.op == OP_DIV) printf ("/ ");
    else if (operador->oper.op == OP_POW) printf ("^ ");
}


void convertir(char **infix) {
    pila_t *pila = pila_crear();

    for (int i = 0; infix[i] != NULL; i++) {
        struct calc_token *token = token_crear();

        if (!calc_parse(infix[i], token)) {
            free(token);
            printf("ERROR\n");
            return;
        }

        //si token es un numero print numero, free token
        if (token->type == TOK_NUM) {
            printf("%ld ", token->value);
            free(token);
        }

        //si token es un operador:
        else if (token->type == TOK_OPER) {
            //si no es un operador valido return
            if (token->oper.op == OP_LOG || token->oper.op == OP_RAIZ || token->oper.op == OP_TERN) {
                free(token);
                printf("ERROR\n");
                return;
            }

            //si hay operadores en la pila
            struct calc_token *operador = pila_ver_tope(pila);

            if (operador && operador->type == TOK_OPER) {
                //si el operador es una potencia mientras que el tope sea de menor precedencia lo desapilo y lo imprimo
                //despues apilo el token

                if (token->oper.op == OP_POW && token->oper.prioridad < operador->oper.prioridad) {
                    while (!pila_esta_vacia(pila) && operador->type == TOK_OPER && token->oper.prioridad < operador->oper.prioridad) {
                        struct calc_token *op = pila_desapilar(pila);
                        imprimir_operador(operador);
                        free(op);
                        operador = pila_ver_tope(pila);
                    }
                    pila_apilar(pila, token);
                }

                //si no es una potencia hago lo mismo mientras que el tope sea de menor o igual precedencia 
                else if (token->oper.op != OP_POW && token->oper.prioridad <= operador->oper.prioridad) {
                    while (!pila_esta_vacia(pila) && operador->type == TOK_OPER && token->oper.prioridad <= operador->oper.prioridad) {
                        struct calc_token *op = pila_desapilar(pila);
                        imprimir_operador(operador);
                        free(op);
                        operador = pila_ver_tope(pila);
                    }
                    pila_apilar(pila, token);
                }
            
                else pila_apilar(pila, token);

            }
 
            //else apilar
            else pila_apilar(pila, token);
        }
        
        //si token es L parentesis apilar
        else if (token->type == TOK_LPAREN) pila_apilar(pila, token);

        //si token es R parantesis desapilar y print hasta llegar al L parentesis
        else {
            struct calc_token *operador = pila_ver_tope(pila);
            while (operador->type != TOK_LPAREN) {
                struct calc_token *op = pila_desapilar(pila);
                imprimir_operador(op);
                free(op);
                operador = pila_ver_tope(pila);
            }
            operador = pila_desapilar(pila); //desapilo L parentesis
            free(operador);
            free(token);  //free R parentesis
        }
        
        free(infix[i]);
    }

    //desapilar y print hasta que la pila este vacia
    while (!pila_esta_vacia(pila)) {
        struct calc_token *operador = pila_desapilar(pila);
        if (operador->type != TOK_LPAREN) imprimir_operador(operador);
        free(operador);
    }

    //destruir pila
    pila_destruir(pila);
    printf("\n");
}


int leer_infix() {
    size_t tam = 32;
    char *op = malloc(tam*sizeof(char));
    if (!op) return 1;

    while (getline(&op, &tam, stdin) != EOF) {
        char **infix = infix_split(op);
        if (infix) convertir(infix);
        free(infix);
    }

    free(op);
    return 0;
}


int main() {
    return leer_infix();
}

#!/usr/bin/python3
from grafo import Grafo
import biblioteca_grafos
import sys

def crear_grafo(ruta_archivo):
	grafo = Grafo()
	with open(ruta_archivo, "r") as archivo:
		for linea in archivo:
			vertice, adyacente = linea.split()
			grafo.agregar_vertice(vertice)
			grafo.agregar_vertice(adyacente)
			grafo.agregar_arista(vertice, adyacente)
	return grafo


def imprimir_lista(lista, separador):
    for i in range(len(lista)-1):
        print(lista[i], end=separador+" ")
    print(lista[-1])


def min_seguimientos(grafo, origen, destino):
    lista_destino = set()
    lista_destino.add(destino)
    _, padres = biblioteca_grafos.dijkstra(grafo, origen, lista_destino)
    camino_minimo = []
    padre = ""
    if destino not in padres:
        print("Seguimiento imposible")
    else: 
        while (padre != None):
            camino_minimo.append(destino)
            padre = padres[destino]
            destino = padre
        imprimir_lista(camino_minimo[::-1], " ->")
    return


def mas_importantes(grafo, cantidad, imprimir):
    importantes = biblioteca_grafos.pagerank(grafo)
    lista = sorted(importantes, key=lambda i:importantes[i], reverse=True)
    if imprimir == "si":
        imprimir_lista(lista[:cantidad], ",")
    return lista[:int(cantidad)]  


def comunidades(grafo, n):
    dict_comunidades =  biblioteca_grafos.label_propagation(grafo, n)
    lista_comunidades = []
    comunidad = []
    k = None
    for vertice, n_comunidad in dict_comunidades.items():
        if n_comunidad != k:
            lista_comunidades.append(comunidad)
            comunidad = []
            k = n_comunidad
        comunidad.append(vertice)
    lista_comunidades.append(comunidad)
    
    for i in range(1, len(lista_comunidades)):
        print(f"Comunidad {i}: ", end="")
        imprimir_lista(lista_comunidades[i], ",")


def divulgar(grafo, delincuente, n):
    visitados = biblioteca_grafos.buscar_vertices_distancia_n(grafo, delincuente, n)
    imprimir_lista(visitados, ",")


def divulgar_ciclo(grafo, delincuente, n):
	ciclo = biblioteca_grafos.buscar_ciclo_largo_n(grafo, delincuente, n)
	if len(ciclo) == 0:
		print("No se encontro recorrido")
	else:
		imprimir_lista(ciclo, " ->")
	return


def cfc(grafo):
    lista_cfc = biblioteca_grafos.obtener_cfc(grafo)
    for i in range(len(lista_cfc)):
        print(f"CFC {i+1}: ", end="")
        imprimir_lista(lista_cfc[i], ",")


def obtener_mejor_camino(diccionario, criminal):
    lista = [criminal]
    while diccionario[criminal] != None:
        lista.append(diccionario[criminal])
        criminal = diccionario[criminal]
    return lista


def persecucion(grafo, lista_delincuentes, k):
    lista_k_importantes = mas_importantes(grafo, k, "no")
    distancia_min = float("inf")
    camino_minimo = []
    for origen in lista_delincuentes:
        diccionario_distancias, diccionario_padres = biblioteca_grafos.dijkstra(grafo, origen, set(lista_k_importantes))
        for elemento in lista_k_importantes[::-1]:
            if elemento in diccionario_distancias and elemento in diccionario_padres:
                if float(diccionario_distancias[elemento]) <= float(distancia_min):
                    distancia_min = diccionario_distancias[elemento]
                    camino_minimo = obtener_mejor_camino(diccionario_padres, elemento)

    imprimir_lista(camino_minimo[::-1], " ->")
    return


def main():
    ruta_archivo = sys.argv[1]
    grafo = crear_grafo(ruta_archivo)
    
    for entrada in sys.stdin:
        entrada_procesada = entrada.split()
        comando = entrada_procesada[0]    

        if comando == "min_seguimientos":
            min_seguimientos(grafo, entrada_procesada[1], entrada_procesada[2])
        elif comando == "mas_imp":
            mas_importantes(grafo, int(entrada_procesada[1]), "si")
        elif comando == "comunidades":
            comunidades(grafo, entrada_procesada[1])
        elif comando == "divulgar":
            divulgar(grafo, entrada_procesada[1], int(entrada_procesada[2]))
        elif comando == "divulgar_ciclo":
            divulgar_ciclo(grafo, entrada_procesada[1], int(entrada_procesada[2]))
        elif comando == "cfc":
            cfc(grafo)
        elif comando == "persecucion":
            lista_delincuentes = []
            for delincuente in entrada_procesada[1].split(','):
                lista_delincuentes.append(delincuente)
            persecucion(grafo, lista_delincuentes, entrada_procesada[2])
    return

main()

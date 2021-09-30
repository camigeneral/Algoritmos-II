from grafo import Grafo
from pila import Pila
from cola import Cola
import heapq
import random


def dijkstra(grafo, origen, destinos):
    '''devuelve una tupla con los diccionario de distancias y de padres obtenidos con dijkstra'''
    distancias = {}
    padres = {}
    for vertice in grafo.obtener_vertices():
        distancias[vertice] = float("inf")
    distancias[origen] = 0
    padres[origen] = None
    heap = []
    heapq.heappush(heap, (0, origen))
    while len(heap) != 0 and len(destinos) != 0:
        distancia, v = heapq.heappop(heap)
        if v in destinos:
            destinos.remove(v)
        for w in grafo.obtener_adyacentes(v):
            if distancias[v]+1 < distancias[w]:
                distancias[w] = distancias[v]+1
                padres[w] = v
                heapq.heappush(heap, (distancias[w], w))
    return distancias, padres


def vertices_a_distancia_n(grafo, origen, n):
    '''busca todos los vertices a n saltos del origen y los devuelve en una lista'''
    visitados = []
    distancia = {}
    distancia[origen] = 0
    visitados.append(origen)
    cola_valores = Cola()
    while not cola_valores.esta_vacia():
        v = cola_valores.desencolar()
        if distancia[v] < n:
            for w in grafo.obtener_adyacentes(v):
                if w not in visitados:
                    distancia[w] = distancia[v]+1
                    visitados.append(w)
                    cola_valores.encolar(w)
    return visitados


def dfs(grafo, v, visitados):
    '''dfs, devuelve una lista'''
    visitados.append(v)
    for w in grafo.obtener_adyacentes(v):
        if w not in visitados:
            visitados = dfs(grafo, w, visitados)
    return visitados


def dfs_pila(grafo, v, visitados, pila):
    '''dfs, devuelve una pila'''
    visitados.append(v)
    for w in grafo.obtener_adyacentes(v):
        if w not in visitados:
            pila = dfs_pila(grafo, w, visitados, pila)
    pila.pila_apilar(v)
    return pila


def obtener_grafo_traspuesto(grafo):
    '''devuelve el grafo traspuesto, es decir el grafo con las aristas invertidas'''
    grafo_traspuesto = Grafo()
    for v in grafo.obtener_vertices():
        grafo_traspuesto.agregar_vertice(v)
        for w in grafo.obtener_adyacentes(v):
            grafo_traspuesto.agregar_vertice(w)
            grafo_traspuesto.agregar_arista(w, v)
    return grafo_traspuesto


def obtener_cfc(grafo):
    '''busca todas las componentes fuertemente conexas del grafo y las devuelve en una lista de listas'''
    pila = Pila()
    visitados = []
    for v in grafo.obtener_vertices():
        if v not in visitados:
            pila = dfs_pila(grafo, v, visitados, pila)
    grafo_traspuesto = obtener_grafo_traspuesto(grafo)
    lista_cfc = []
    visitados = []
    while not pila.pila_esta_vacia():
        vertice = pila.pila_desapilar()
        if vertice not in visitados:
            recorrido_dfs = dfs(grafo_traspuesto, vertice, [])
            cfc = []
            for vertice in recorrido_dfs:
                if vertice not in visitados:
                    cfc.append(vertice)
            if len(cfc) != 0:
                lista_cfc.append(cfc)
            visitados = dfs(grafo_traspuesto, vertice, visitados)
    return lista_cfc


def _buscar_ciclo_largo_n(grafo, origen, v, n, visitados, ciclo):
	'''busca todos los caminos de largo n y los devuelve en una lista de listas'''
	if n == 0:
		if v == origen:
			return True 
		return False
	if v not in visitados:
		visitados.add(v)
		ciclo.append(v)
		for w in grafo.obtener_adyacentes(v):
			if _buscar_ciclo_largo_n(grafo, origen, w, n-1, visitados, ciclo):
				return True
		visitados.remove(v)
		ciclo.pop()
	return False


def buscar_ciclo_largo_n(grafo, origen, n):
	'''busca un ciclo de largo n y lo devuelve en una lista'''
	ciclo = []
	if origen in grafo.obtener_vertices():
		_buscar_ciclo_largo_n(grafo, origen, origen, n, set(), ciclo)
	if ciclo:
		ciclo.append(origen)
	return ciclo


def buscar_vertices_distancia_n(grafo, origen, n):
	'''busca todos los vertices a maximo n saltos del pedido y los devuelve en una lista'''
	visitados = set()
	orden = {}
	heap = []
	orden[origen] = 0
	heapq.heappush(heap, (orden[origen],origen))
	while len(heap) > 0:
		_, v = heapq.heappop(heap)
		if orden[v] < n:
			for w in grafo.obtener_adyacentes(v):
				if w not in visitados and w != origen:
					if orden[v] < orden.get(w,n+1):
						orden[w] = orden[v] + 1
					visitados.add(w)
					heapq.heappush(heap, (orden[w], w))
	return list(visitados)


def pagerank(grafo):
	'''devuelve un diccionario con la importancia de cada vertice'''
	pagerank = {}
	grafo_traspuesto = obtener_grafo_traspuesto(grafo)
	pr_inicial = 1/grafo.obtener_cantidad()
	for v in grafo.obtener_vertices():
		pagerank[v] = pr_inicial
	
	for i in range(10):
		pagerank_aux = {}
		for v in grafo.obtener_vertices():
			for w in grafo_traspuesto.obtener_adyacentes(v):
				if w in pagerank:
					pagerank_aux[v] = pagerank_aux.get(v, 0) + pagerank[w]/len(grafo.obtener_adyacentes(w))
		pagerank = dict(pagerank_aux)
	return pagerank


def obtener_frec_max(comunidades, lista_adyacentes):
	comunidades_presentes = {}
	for adyacente in lista_adyacentes:
		comunidades_presentes[comunidades[adyacente]] = comunidades_presentes.get(comunidades[adyacente], 0) + 1
	if len(comunidades_presentes) > 0:
		return max(comunidades_presentes, key=comunidades_presentes.get)
	else:
		return None

def label_propagation(grafo, n):
    '''devuelve un diccionario con todas las counidades de al menos n integrantes'''
    comunidades = {}
    vertices = grafo.obtener_vertices()
    grafo_traspuesto = obtener_grafo_traspuesto(grafo)

    for i in range(len(vertices)):
        comunidades[vertices[i]] = i

    for i in range(10):
        for i in range(len(vertices)):
            v = vertices[i]
            comunidades[v] = obtener_frec_max(comunidades, grafo_traspuesto.obtener_adyacentes(v))

    return comunidades

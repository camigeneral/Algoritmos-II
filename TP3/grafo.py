import random

def obtener_claves(diccionario):
    lista_claves = []
    for clave in diccionario.keys():
        lista_claves.append(clave)
    return lista_claves

class Grafo():
    #lista de adyacencia: {vertice1: [ady1, ady2, ...], ...}
    #grafo dirigido y no pesado

    def __init__(self):
        self.grafo = {}

    def agregar_vertice(self, v):
        if v in self.grafo:
            return False
        self.grafo[v] = []

    def borrar_vertice(self, v):
        if v not in self.grafo:
            return False
        self.grafo.__delitem__(v)
        for vertice,adyacentes in self.grafo.items():
            for ady in adyacentes:
                if ady == v:
                    self.grafo[vertice].remove(ady)
    def agregar_arista(self, v, w):
        if v not in self.grafo or w not in self.grafo:
            return False
        if w in self.grafo[v]:
            return False
        self.grafo[v].append(w)

    def borrar_arista(self, v, w):
        if v not in self.grafo or w not in self.grafo[v]:
            return False
        self.grafo[v].remove(w)

    def buscar_vertice(self, v):
        if v in self.grafo:
            return True
        return False

    def buscar_arista(self, v, w):
        if w in self.grafo[v]:
            return True
        return False

    def obtener_vertice_aleatorio(self):
        return random.choice(list(self.grafo.keys()))

    def obtener_vertices(self):
        return obtener_claves(self.grafo)

    def obtener_adyacentes(self, v):
        if not v:
            return False
        return self.grafo[v]

    def obtener_cantidad(self):
        return len(self.grafo)

class Grafo_iterador():
    def __init__(self, grafo):
        self.grafo = grafo
        self.pos = 0

    def iter_al_final(self):
        if self.pos >= len(self.grafo):
            return True
        return False

    def iter_avanzar(self):
        if not self.iter_al_final(self):
            self.pos += 1

    def iter_ver_actual(self):
        if self.iter_al_final(self):
            return False
        vertices = Grafo.obtener_vertices(self.grafo)
        return vertices[self.pos]
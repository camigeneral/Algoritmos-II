class Pila:
    def __init__(self):
        '''Crea una pila vacia'''
        self.items = []

    def pila_apilar(self, dato):
        '''Apila un elemento'''
        self.items.append(dato)

    def pila_ver_tope(self):
        '''Devuelve el elemento que está en el tope de la pila.'''
        if self.pila_esta_vacia():
            raise ValueError("pila vacía")
        return self.items[-1]

    def pila_desapilar(self):
        '''Desapila el elemnto que esta en el tope de la pila y lo devuelve'''
        if self.pila_esta_vacia():
            raise IndexError("La pila está vacía")
        return self.items.pop()

    def pila_esta_vacia(self):
        '''Devuelve True si la pila esta vacia, False al contrario'''
        return len(self.items) == 0
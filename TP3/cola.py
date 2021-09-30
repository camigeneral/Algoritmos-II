class Cola:
    def __init__(self):
        '''Crea una cola vacia'''
        self.items = []

    def encolar(self, x):
        '''Encola un elemento'''
        self.items.append(x)

    def desencolar(self):
        '''Elimina el primer elemento de la cola y devuelve su valor'''
        if self.esta_vacia():
            raise ValueError("La cola está vacía")
        return self.items.pop(0)

    def esta_vacia(self):
        '''Devuelve True si la cola esta vacia, False al contrario'''
        return len(self.items) == 0
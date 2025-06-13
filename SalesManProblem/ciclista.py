import dijkstra as dij
#ciclista.py
    # Contiene un objeto de ciclista que tiene:
    #     Una lista de paquetes que tiene que entregar
    #     Una prioridad de cada paquete (en el mismo orden que la lista de paquetes)
    #     Un trail de las casillas que ha visitado
    #     Una posición actual
    #     Una lista de paquetes ordenada de mayor a menor prioridad (función de facilidad de entrega e importancia del paquete)
    #     Una copia actual del tablero
    #     Una función de calcular la ruta óptima hacia un paquete
    #     Tmax
    #     Un id único
    #     Un número de orden (para saber en qué orden se mueve)


class ciclista:
    id = 0
    
    def passTablero(self, tablero):
        tablero = tablero

    def __init__(self, paquetes, Tmax, prioridades, tablero):
        #paquetes es una lista de coordenadas [x,y] que deben ser entregadas
        #prioridades es la prioridad (1-10) de cada paquete
        self.paquetes = paquetes
        self.prioridades = prioridades
        self.tablero= tablero
        self.trail = [0,0]
        self.Tmx = Tmax
        self.id = ciclista.id
        ciclista.id += 1
        #self.current=0
        self.orden = 0
        self.posicion = [0,0]
        #self.tablero = [[]]
        self.paquetes_ordenados = self.ordena_paquetes(self.paquetes, self.prioridades)
        self.theorical= self.hacer_ruta_teorica()
    
    def define_prio_de_entregas(self, paquetes, prioridades):
        facilidad_de_entrega = []
        for i in range(len(paquetes)):
            ruta = dij.dijkstra(self.tablero, self.posicion, paquetes[i])
            if ruta is None:
                continue
            facilidad_de_entrega.append([paquetes[i], len(ruta)* prioridades[i]])
        return facilidad_de_entrega
        
    def ordena_paquetes(self, paquetes, prioridades):
        #ordena los paquetes de mayor a menor prioridad
        facilidad_de_entrega = self.define_prio_de_entregas(paquetes, prioridades)
        #print(facilidad_de_entrega)
        #paquetes_ordenados = []
        #facilidad de entrega se puede ver así:
        #[[[1, 2], 27], [[7, 2], 6], [[8, 7], 16], [[6, 3], 40], [[4, 5], 54], [[5, 8], 9], [[2, 1], 16], [[2, 7], 24], [[3, 7], 8], [[6, 4], 35]]
        #entonces ordenamos según el segundo elemento de cada lista
        facilidad_de_entrega.sort(key=lambda x: x[1]) #, reverse=True
        #print(facilidad_de_entrega)
        return facilidad_de_entrega
    
    def define_ruta(self, paquete):
        #calcula la ruta óptima hacia un paquete
        return dij.dijkstra(self.tablero, self.posicion, paquete)


    #calculamos la ruta óptima teórica, sin contar a otros ciclistas
    #es decir, la ruta más corta posible para entregar todos los paquetes.
    #Esto es para decidir quién de los repartidores se moverá primero.
    def hacer_ruta_teorica(self):
        trail = []
        self.posicion = [0, 0]
        n = self.tablero.len()
        paquetes_ordenados = self.ordena_paquetes(self.paquetes, self.prioridades)

        for paquete in paquetes_ordenados:
            paqueteCoords = paquete[0]
            ruta = self.define_ruta(paqueteCoords)
            if ruta is None:
                continue
            trail.extend(ruta)
            self.posicion = trail[-1]
            if self.posicion in paquetes_ordenados:
                self.paquetes.remove(self.posicion)
                paquetes_ordenados.remove(self.posicion)

        trail += self.define_ruta([n - 1, n - 1])
        self.posicion = [n - 1, n - 1]
        trail.append(self.posicion)

        i = 1
        while i < len(trail):
            if trail[i] == trail[i - 1]:
                del trail[i]
            else:
                i += 1

        self.trail = trail
        self.theorical = trail
        return trail


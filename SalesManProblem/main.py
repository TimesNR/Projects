from ciclista import ciclista
from tablero import tablero
import random as rd
import numpy as np
import matplotlib.pyplot as plt





#Parámetros
paquetesMáximos=4
n=150
grid = tablero(n)
q=3 #número de ciclistas
Tmax=n**2 #tiempo máximo de simulación (pasos máximos que puede dar un ciclista)
prioridadConstante= True #si es True, todos los paquetes tienen la misma prioridad, si no, se genera al azar









ciclistas=[]
for i in range(q):
    paquetesAsignados= rd.randint(1, paquetesMáximos) #máximo 10 paquetes
    paquetes=[]
    prioridades=[]
    for j in range(paquetesAsignados):
        paquetes.append([rd.randint(1, n-1), rd.randint(1, n-1)])
        if prioridadConstante:    
            prioridades.append(1)
        else:
            prioridades.append(rd.randint(1, 10))
        #paquetes.append([rd.randint(1, n-2), rd.randint(1, n-2)]) 
        #prioridades.append(rd.randint(1, 10))
        #prueba: todos los paquetes tienen la misma prioridad
        #prioridades.append(1)
    ciclistas.append(ciclista(paquetes, Tmax, prioridades,grid))
    

#finalmente, la simulación
#calculamos la prioridad de cada ciclista
prioridadCiclista=[]
#para esto vamos a invocar la ruta teórica de cada ciclista
for i in range(q):
    prioridadCiclista.append([len(ciclistas[i].theorical), ciclistas[i]]) #distancia, ciclista

#ordenamos la lista de prioridades basadas en el primer valor del conjunto
prioridadCiclista.sort(key=lambda x: x[0], reverse=True) #esta linea está un poco cargada, lo que hace es:
#1. toma la lista prioridadCiclista
#2. toma el primer elemento de cada conjunto (x[0])
#3. ordena la lista de acuerdo a ese primer elemento
#lambda se usa para definir funciones rápidamente, en este caso, la función toma x, y regresa x[0]
#print("PrioCiclTest")
#print(prioridadCiclista)

#Sanity check
def sanityCheck():
    ids=[ciclista[1].id for ciclista in prioridadCiclista]
    print("Rutas")
    for cicl in ciclistas:
        #print theorical
        print("Ciclista "+str(cicl.id)+" tiene ruta teórica:")
        print(cicl.theorical)
        print("Con paquetes: ")
        print(cicl.paquetes)
    print("Orden de ciclistas")
    print(ids)
ids=[ciclista[1].id for ciclista in prioridadCiclista]
print("Orden de ciclistas: ")
print(ids)
#sanityCheck()

#prioridadCiclista se ve como:
#[[5, ciclista2], [4, ciclista4], [3, ciclista5], [2, ciclista1], [1, ciclista2]]


#Ahora ya sabemos qué ciclista va primero, y podemos empezar la simulación

rutaAnterior=[[0,0]]
#primero, movemos al primer ciclista de la lista
#vamos a usar la ruta teórica de cada ciclista para simular su movimiento por el tablero, y después recalculamos con .hacer_ruta_teorica()
#guardamos el trail del ciclista y modificamos el tablero conforme haya pasado, a t le agregamos 1 en cada casilla, y a f le restamos 1

#tiempo=0 #tiempo de simulación, que es diferente al t de las casillas
#mientras haya ciclista en la lista

for ciclistaActual in prioridadCiclista:
    #modificamos el tablero según la ruta anterior
    for i in range(len(rutaAnterior)):
        grid.getCasillas()[rutaAnterior[i][0]][rutaAnterior[i][1]].t+=1
        grid.getCasillas()[rutaAnterior[i][0]][rutaAnterior[i][1]].f-=1
        #sanity check: si f es negativo, imprimir error
        if grid.getCasillas()[rutaAnterior[i][0]][rutaAnterior[i][1]].f<0:
           #print("Error: f es negativo")
           #lo ponemos =0
            grid.getCasillas()[rutaAnterior[i][0]][rutaAnterior[i][1]].f=1
    #calculamos la ruta teórica del ciclista actual
    #checamos si para el ciclista actual, tiene algún paquete que caiga en una casilla con f=0
    #si es así, ponemos que la casilla tiene f=1, independiente de t. Esto es para que el ciclista pueda pasar por ahí
    for paquete in ciclistaActual[1].paquetes:
        if grid.getCasillas()[paquete[0]][paquete[1]].f<=0:
            grid.getCasillas()[paquete[0]][paquete[1]].f=1
    ciclistaActual[1].hacer_ruta_teorica()
    rutaAnterior=ciclistaActual[1].theorical
    # print("Ciclista "+str(ciclistaActual[1].id)+" tiene ruta teórica:")
    # print(ciclistaActual[1].theorical)


#sanityCheck()




def generar_datos(camino, paquetes):
    return [{"camino": camino, "paquetes": paquetes}]

def graficar_camino_y_paquetes(caminos, paquetes):
    import matplotlib.colors as mcolors
    colores_camino = list(mcolors.TABLEAU_COLORS.values())
    colores_paquetes = list(mcolors.TABLEAU_COLORS.values())

    fig, ax = plt.subplots()
    #ax.set_xticks([x for x in range(n)])
    #ax.set_yticks([y for y in range(n)])
    ax.set_xlim(0, n)
    ax.set_ylim(0, n)
    ax.grid(which='both')

    facilidad_cruzar = np.zeros((n, n))
    #manualmente modificamos las casillas 0,0 y n-1,n-1 para que t=1 y f=9
    tablero = grid.getCasillas()
    tablero[0][0].t=1
    tablero[0][0].f=9
    tablero[n-1][n-1].t=1
    tablero[n-1][n-1].f=9
    for x in range(n):
        for y in range(n):
            facilidad_cruzar[x, y] = grid.getCasillas()[x][y].t / (grid.getCasillas()[x][y].f + 1) 
            #facilidad_cruzar[x, y] = grid.getCasillas()[x][y].f
            #facilidad_cruzar[x, y] = grid.getCasillas()[x][y].t

    heatmap = ax.imshow(facilidad_cruzar, cmap='Greens', interpolation='nearest', aspect='auto', origin='upper')
    cbar = plt.colorbar(heatmap)
    #cbar.set_label('Facilidad de Cruzar (t+1)/(d+1)')

    for i, (camino, paquete) in enumerate(zip(caminos, paquetes)):
        
        desplazamiento_horizontal = 0.1 * i
        desplazamiento_vertical = 0.1 * i

        
        camino_x, camino_y = zip(*[(x + 0.5 + desplazamiento_horizontal, y + 0.5 + desplazamiento_vertical) for x, y in camino])
        ax.plot(camino_x, camino_y, color=colores_camino[i], linewidth=2)

        
        paquetes_x, paquetes_y = zip(*[(x + 0.5 + desplazamiento_horizontal, y + 0.5 + desplazamiento_vertical) for x, y in paquete])
        ax.scatter(paquetes_x, paquetes_y, color=colores_paquetes[i], s=100, zorder=2)

   # plt.legend(bbox_to_anchor=(1.05, 1), loc='upper right')
    #ajustamos los xticks y yticks para que vayan cada 0.5
    #ax.set_xticks([x for x in range(n)])
    #ax.set_yticks([y for y in range(n)])
    plt.show()

caminos = []
paquetes = []

for cicl in ciclistas:
    #print(cicl.theorical)
    caminos.append(cicl.theorical)
    paquetes.append(cicl.paquetes)

graficar_camino_y_paquetes(caminos, paquetes)

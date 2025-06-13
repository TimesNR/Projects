Planteamiento del problema: 
Considere un servicio de entregas conformado por un equipo de ciclistas y patinadores que van
repartiendo artículos, desplazándose ágilmente a través de la ciudad. En un día, cada repartidor
tiene la asignación de entregar 𝑁 artículos en diversos sitios de la ciudad. La ciudad se organizado
como una cuadrícula comprendida por 𝑀𝑥𝑀 sectores. Al inicio del día se le entrega a cada
repartidor una lista de los N artículos {𝑧0, 𝑧1, … , 𝑧𝑘, … , 𝑧𝑁−1}, su ubicación en el mapa de donde
entregarlos: {(𝑥0, 𝑦0), (𝑥1, 𝑦1), … , (𝑥𝑘, 𝑦𝑘), … , (𝑥𝑁−1, 𝑦𝑁−1)} y sus prioridades de entrega
{𝑣0, 𝑣1, … , 𝑣𝑘, … , 𝑣𝑁−1}. Los repartidores cuentan con una aplicación, que le indica el tiempo para
avanzar en una celda y que tan fácil es atravesarla (𝑥, 𝑦). Su objetivo será diseñar y programar un
algoritmo bioinspirado para optimizar el servicio de entregas en 3 escenarios:

En el primer escenario, considere 1 sólo repartidor que realiza sus entregas por la ciudad iniciando
en la celda (0,0) y concluyendo en la celda (𝑁 − 1, 𝑁 − 1). Cada celda tiene asignado un tiempo
de avance 𝑡 (con un valor de 0 a 9) y una facilidad para atravesarla (de 0 a 9). Determine la ruta
que debería seguir el repartidor para maximizar la prioridad total de los artículos entregados, en
el menor tiempo posible y por las rutas más fáciles. En un día, el repartidor tiene a lo más un
tiempo 𝑇𝑚𝑎𝑥 para realizar las entregas.

En el segundo escenario, cuenta con un número 𝑄 de ciclistas y patinadores, cada uno con su
asignación de entregas (como lo indican los puntos anteriores 0 y 1). La entrega conjunta de
artículos por los repartidores actualiza los tiempos de avance por celda y su facilidad para
atravesarla, generando escenarios colaborativos y competitivos. Cada vez que un repartidor se
encuentra en una celda, el tiempo de avance en esa celda aumenta 𝑡 → 𝑡 + 1 (por aumento el
tráfico) y la facilidad disminuye 𝑓 → 𝑓 − 1 (indica que tan viable es avanzar por la ruta). Al salir,
el tiempo disminuye 𝑡 → 𝑡 − 1 y la facilidad aumenta 𝑓 → 𝑓 + 1. Diseñe y programe un algoritmo
de logística coordinada de entregas para determinar las rutas de entregas simultáneas de tal
forma que maximice la prioridad de las entregas entre todos los repartidores, en el menor tiempo
posible y con la mayor facilidad.









Notas mías:
- El tiempo de avance 𝑡 (con un valor de 0 a 9) y una facilidad para atravesarla (de 0 a 9) se refiere a la dificultad de la celda, no al tiempo que se tarda en atravesarla.
- Asumamos ahorita Tmax infinito, es decir, que no hay límite de tiempo para entregar los paquetes
    Sin embargo, si hay límite de tiempo para entregar, solo dejaremos sin entregar los paquetes con menor prioridad


La estrategia va a ser:
- Encontrar la ruta óptima para cada repartidor
    Esto implica calcular la ruta cuya resolución de Dijkstra o A* sea la menor hacia cada paquete, y luego recalcular la ruta hacia el siguiente paquete, y así sucesivamente hasta terminar con todos los paquetes O, hasta que Tmax no alcance para llegar al final. 
    (Posiblemente hacer alguna función para darle más peso a la prioridad)
        Ordenar de mayor a menor la cantidad de pasos total de cada repartidor, y hacer que los que tengan más pasos vayan primero
            Esto permite que en caso de que una casilla se vuelva inpasable, la acción más óptima sea esperar ese paso de tiempo (le dejamos la pena de esperar a los que tengan menos pasos, ya que son los que les sobra)
                Después de decidir eso para cada repartidor, recalcular las rutas de cada uno, y volver a ordenarlos de mayor a menor, y así hasta el último repartidor.
                    En caso de que alguien tenga que entregar a una casilla ocupada, se espera hasta que pueda moverse.
                        *probablemente recalcular Dijkstra o A* cada vez que se mueva un repartidor, para que no se quede atorado en un loop infinito
    Es decir, los ciclistas se simulan secuencialmente, no en paralelo. 


El layout del código consiste en:
ciclista.py
    Contiene un objeto de ciclista que tiene:
        Una lista de paquetes que tiene que entregar
        Una prioridad de cada paquete (en el mismo orden que la lista de paquetes)
        Un trail de las casillas que ha visitado
        Una posición actual
        Una lista de paquetes ordenada de mayor a menor prioridad (función de facilidad de entrega e importancia del paquete)
        Una copia actual del tablero
        Una función de calcular la ruta óptima hacia un paquete
        Tmax
        Un id único
        Un número de orden (para saber en qué orden se mueve)

casilla.py
    Contiene un objeto de casilla que tiene:
        Una posición
        Un tiempo de avance
        Una facilidad para atravesarla
        Una lista de ciclistas que están en esa casilla

tablero.py
    Contiene un objeto de tablero que tiene:
        Una lista de casillas
        Una función para actualizar el tablero
        Una función para imprimir el tablero


dijkstra.py 
    Es una función que calcula la ruta óptima entre dos puntos, y regresa una lista de casillas que hay que visitar para llegar al destino
    Debe recibir un tablero, una posición inicial y una posición final
    Debe regresar una lista de casillas que hay que visitar para llegar al destino

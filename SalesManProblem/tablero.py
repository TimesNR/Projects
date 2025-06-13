import casilla
import random as rd

class tablero:
    def __init__(self,n) -> None:
        self.casillas = [[casilla.Casilla(i, j, rd.choice(range(1, 9)), rd.choice(range(1, 9))) for j in range(n)] for i in range(n)]
        self.n=n
        self.casillas[0][0].t=0
        self.casillas[n-1][n-1].t=0
        self.casillas[0][0].f=20
        self.casillas[n-1][n-1].f=20

    def len(self):
        return self.n
    
    def getCasillas(self):
        return self.casillas
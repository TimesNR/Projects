You are given the two integers, n and m and two integer arrays, hBars and vBars. The grid has n + 2 horizontal and m + 2 vertical bars, creating 1 x 1 unit cells. The bars are indexed starting from 1.

You can remove some of the bars in hBars from horizontal bars and some of the bars in vBars from vertical bars. Note that other bars are fixed and cannot be removed.

Return an integer denoting the maximum area of a square-shaped hole in the grid, after removing some bars (possibly none).
**IDEA**
Como sabes que cualquiera dos lineas se intersectan, 
- Primero  ordenar los arrays con las lineas quitables.
- Ves si las lineas quitables son seguidas en cada dimension, y te quedas con la longitud resultante
- Te quedas con el de maxima longitud
- ya que tiene la max longitud horizontal y vertical. Pues como se intersectan sabes que se va a formar un cuadrado no importa dónde.
- Como es cuadrado, te quedas con el lado mas bajo y lo elevas al cuadrado

**MI SOLUCION**
```python
class Solution(object):
    def maximizeSquareHoleArea(self, n, m, hBars, vBars):
        """
        :type n: int
        :type m: int
        :type hBars: List[int]
        :type vBars: List[int]
        :rtype: int
        """
        hBars =  sorted(hBars)
        vBars = sorted(vBars)
        # Primer tema es que puedes quitar mas de 1, chance recursivo
        # Todas las lineas se intersectan en algun lado 
        #Tengo que saber si los Hbars son seguidos
        # Y la maxima cantidad seguidas que son
        lonHBars = len(hBars)
        lonVBars = len(vBars)
        hsquare = 2
        vsquare = 2
        maxhsquare = 1
        maxvsquare = 1
        # Ocupo que sea al menos dos
        if lonHBars == 0 or lonVBars == 0:
            return 1
        for i in range(lonHBars):
            i0 = hBars[i-1]
            i1 = hBars[i]
            if i0 == i1 -1:
                hsquare += 1
            else:
                hsquare = 2
            maxhsquare = max([hsquare,maxhsquare])
        for j in range(lonVBars):
            j0 = vBars[j-1]
            j1 = vBars[j]
            if j0 == j1 -1:
                vsquare +=1
            else:
                vsquare = 2
            maxvsquare = max([vsquare,maxvsquare])
        return min([maxhsquare,maxvsquare])**2
```

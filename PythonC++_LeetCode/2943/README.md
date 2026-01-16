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


**SOLUCION EN C+++**

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
class Solution {
public:
    int maximizeSquareHoleArea(int n, int m, vector<int>& hBars, vector<int>& vBars) {
        int lonHBars = hBars.size();
        int lonVBars = vBars.size();
       //  cannot bind to a temporary of type 'void'
        // no sé por que recomendaban usar esto int n = sizeof(arr) / sizeof(arr[0]);
        // asumo mas rapido para arreglos estaticos, pero te dise los bites del objeto como esta en una funcion el objeto es un puntero por tanto no funciona
        // Aqui funciona eso por el tipo de objeto raro que tiene, el otro es para un array estatico
        // como es INPLACE modifica directamente al objeto, no a la copia o al pointe
        // ergo no es necesario guardarlo en nada aparte no devuelve ningun valor da void
        std::sort(vBars.begin(), vBars.end());
        std::sort(hBars.begin(), hBars.end());
        int hsquare = 2;
        int vsquare = 2;
        int maxhsquare = 1;
        int maxvsquare = 1;
        if (lonHBars == 0 || lonVBars == 0 ){ return 1;}
        if (lonHBars ==1){maxhsquare = 2;}
        if(lonVBars ==1){maxvsquare =2;}
        // aqui el for es diferente al de python con los bordes.
        // en python
        for (int i = 0; i+1 < lonHBars; i++) 
            {
                std::cout << i;
                std::cout << endl;
                int i0 = hBars[i];
                int i1 = hBars[i+1];
                if (i0 == i1 -1)
                    {
                        hsquare = hsquare+1;
                    }
                else 
                    { hsquare = 2;}
                maxhsquare = std::max({hsquare,maxhsquare});
            }
        for (int j = 0; j+1 < lonVBars; j++)
            {
                std::cout << j;
                std::cout << endl;
                int j0 = vBars[j];
                int j1 = vBars[j+1];
                if (j0 == j1 -1) 
                    {
                        vsquare = vsquare +1;
                    }
                else
                    {
                        vsquare = 2;
                    }
                maxvsquare = std::max({maxvsquare,vsquare});
            }
        // std:: cout << std::min({maxvsquare,maxhsquare});
        return pow(std::min({maxvsquare,maxhsquare}),2) ;
       // std :: sort(hBars)
    }
};
```

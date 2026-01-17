There is a large (m - 1) x (n - 1) rectangular field with corners at (1, 1) and (m, n) containing some horizontal and vertical fences given in arrays hFences and vFences respectively.

Horizontal fences are from the coordinates (hFences[i], 1) to (hFences[i], n) and vertical fences are from the coordinates (1, vFences[i]) to (m, vFences[i]).

Return the maximum area of a square field that can be formed by removing some fences (possibly none) or -1 if it is impossible to make a square field.

Since the answer may be large, return it modulo 109 + 7.

Note: The field is surrounded by two horizontal fences from the coordinates (1, 1) to (1, n) and (m, 1) to (m, n) and two vertical fences from the coordinates (1, 1) to (m, 1) and (1, n) to (m, n). These fences cannot be removed.

 

Example 1:



Input: m = 4, n = 3, hFences = [2,3], vFences = [2]
Output: 4
Explanation: Removing the horizontal fence at 2 and the vertical fence at 2 will give a square field of area 4.


**SOLUCION**

Notas 
-Casi todas las funciones de lista son **built in**
-Extend para agregar **mas de 1 elemento**
-Pop quita el **ultimo elemento**
-Poner [::-1] **invierte la lista**
-El max es malisimo en la version orignal depython, usar python 3.0
-**Quitar elementos de la lista disminuye la complejidad** de n**2 a algo mayor a n

```python
class Solution:
    def maximizeSquareArea(self, m: int, n: int, hFences: List[int], vFences: List[int]) -> int:

    # Aui a diferencia del anterior, no siempre hay lineas que es el pedo principal
    # Osea el m y n dan como la indicacion de bordes
    # Y la hfences y v fences son las lineas
        lonHFences = len(hFences)
        lonVFences = len(vFences)
        # Son funciones in place
        hFences.extend([1,m])
        vFences.extend([1,n])
        hFences.sort()
        vFences.sort()
        # for i in hFences:
        #     for j in hFences:
        l_h_square = []
        l_v_square = []
        aux_hFences = hFences[:]
        aux_vFences = vFences[:]
        for i in hFences:
            aux_hFences.remove(i)
            for j in aux_hFences:
                l_h_square.append(j-i)

        for i in vFences:
            aux_vFences.remove(i)
            for j in aux_vFences:
                l_v_square.append(j-i)
        aux = set(l_h_square) & set(l_v_square)
        if len(aux) == 0:
            return -1
        else: 
            return max(aux) **2 % (10**9+7)
```

```cpp
class Solution {
public:
    int maximizeSquareArea(int m, int n, vector<int>& hFences, vector<int>& vFences) {
        int lonHFences = size(hFences);
        int lonVFences = size(vFences);
        //Copia el vector
        hFences.insert(std::end(hFences),1,m);
        vFences.insert(std::end(vFences),1,n);
        std::sort(hFences.begin(),hFences.end());
        std::sort(vFences.begin(),vFences.end());
        std::vector<int> l_h_square;
        std::vector<int> l_v_square;
        std::vector<int> aux_hFences(hFences.begin(),hFences.end());
        std::vector<int> aux_vFences(vFences.begin(),vFences.end());
        for (const auto& elemento : hFences)
            {
                
            }
        return -1;
    }
};
```

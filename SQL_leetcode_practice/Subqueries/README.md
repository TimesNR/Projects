## 1321. Restaurant Growth
You are the restaurant owner and you want to analyze a possible expansion (there will be at least one customer every day).

Compute the moving average of how much the customer paid in a seven days window (i.e., current day + 6 days before). average_amount should be rounded to two decimal places.

Return the result table ordered by visited_on in ascending order.

The result format is in the following example.

 

Example 1:

Input: 
Customer table:
+-------------+--------------+--------------+-------------+
| customer_id | name         | visited_on   | amount      |
+-------------+--------------+--------------+-------------+
| 1           | Jhon         | 2019-01-01   | 100         |
| 2           | Daniel       | 2019-01-02   | 110         |
| 3           | Jade         | 2019-01-03   | 120         |
| 4           | Khaled       | 2019-01-04   | 130         |
| 5           | Winston      | 2019-01-05   | 110         | 
| 6           | Elvis        | 2019-01-06   | 140         | 
| 7           | Anna         | 2019-01-07   | 150         |
| 8           | Maria        | 2019-01-08   | 80          |
| 9           | Jaze         | 2019-01-09   | 110         | 
| 1           | Jhon         | 2019-01-10   | 130         | 
| 3           | Jade         | 2019-01-10   | 150         | 
+-------------+--------------+--------------+-------------+
Output: 
+--------------+--------------+----------------+
| visited_on   | amount       | average_amount |
+--------------+--------------+----------------+
| 2019-01-07   | 860          | 122.86         |
| 2019-01-08   | 840          | 120            |
| 2019-01-09   | 840          | 120            |
| 2019-01-10   | 1000         | 142.86         |
+--------------+--------------+----------------+

**NOTAS** 
Pues de los ejercicios disponibles pa este. Este me destaco por que no había usado las window function mucho la verdad
```sql
SELECT visited_on,amount,average_amount
FROM
(SELECT visited_on,
SUM(amount) OVER (ORDER BY visited_on ASC ROWS BETWEEN 6 PRECEDING AND CURRENT ROW) AS amount, 
DATE_SUB(visited_on, INTERVAL 6 DAY) as dmenos7,
ROUND(AVG(amount)
OVER (ORDER BY visited_on ASC
ROWS BETWEEN 6 PRECEDING AND CURRENT ROW),2) AS average_amount
FROM
(SELECT visited_on, SUM(amount) as amount
FROM Customer
GROUP BY visited_on) Suma) Aux
WHERE dmenos7
IN
(SELECT visited_on FROM Customer)
```
Aquí basicamente es medio desmadroso asegurarte que solo muestra datos que tomen en cuenta el promedio de 7 dias, creo que igual puedes hacerlo mas facil con un last. Pero pues yo vi que datos había 7 dias previos y ver si esos datos estaban en visited_on. Ya luego un medio desmadre de subqueries para que puede filtrar por eso sin que me afecte el resultado del average. Reitero seguramente son con un last menos 7 sea más sencillo
En todo caso, lo que destaco es bueno 

```sql
SUM(amount) OVER (ORDER BY visited_on ASC ROWS BETWEEN 6 PRECEDING AND CURRENT ROW)
```
***ROWS BETWEEN** Establece una forma manual sin agrupar con el partition by de dividir los grupos. En este caso para que funcionará primero tuve que agrupar por sumas

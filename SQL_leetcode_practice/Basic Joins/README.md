# 197 Rising Temperature
Write a solution to find all dates' id with higher temperatures compared to its previous dates (yesterday).

Return the result table in any order.

The result format is in the following example.

 

Example 1:

Input: 
Weather table:
+----+------------+-------------+
| id | recordDate | temperature |
+----+------------+-------------+
| 1  | 2015-01-01 | 10          |
| 2  | 2015-01-02 | 25          |
| 3  | 2015-01-03 | 20          |
| 4  | 2015-01-04 | 30          |
+----+------------+-------------+
Output: 
+----+
| id |
+----+
| 2  |
| 4  |
+----+


```sql
SELECT id
FROM
(SELECT id, temperature,LAG(temperature) 
OVER(ORDER BY recordDate) as retraso
FROM Weather) tarantino
WHERE temperature > retraso
```

Aquí pues no puedo editar la tabla tipo
```sql
ALTER TABLE Weather ADD COLUMN retraso int;
```
ni mi combiene editarlo para eso pues un **subquerry**

```sql
(SELECT id, temperature,LAG(temperature) 
OVER(ORDER BY recordDate) as retraso
FROM Weather) tarantino
```
Hace una tabla temporal que llamé tarantino con la temperature y el retraso
Donde el retraso se hace con la siguiente sintaxis

```sql
LAG(columna, offset, valor_por_defecto) OVER (PARTITION BY ... ORDER BY ...)
```


# 1581 CUSTOMERS WHO VISITED BUT DID NOT MAKE ANY TRANSACTIONS.

Write a solution to find the IDs of the users who visited without making any transactions and the number of times they made these types of visits.

Return the result table sorted in any order.

The result format is in the following example.

 

Example 1:

Input: 
Visits
+----------+-------------+
| visit_id | customer_id |
+----------+-------------+
| 1        | 23          |
| 2        | 9           |
| 4        | 30          |
| 5        | 54          |
| 6        | 96          |
| 7        | 54          |
| 8        | 54          |
+----------+-------------+
Transactions
+----------------+----------+--------+
| transaction_id | visit_id | amount |
+----------------+----------+--------+
| 2              | 5        | 310    |
| 3              | 5        | 300    |
| 9              | 5        | 200    |
| 12             | 1        | 910    |
| 13             | 2        | 970    |
+----------------+----------+--------+
Output: 
+-------------+----------------+
| customer_id | count_no_trans |
+-------------+----------------+
| 54          | 2              |
| 30          | 1              |
| 96          | 1              |
+-------------+----------------+

```sql
SELECT Visits.customer_id,count(Visits.customer_id) AS count_no_trans #count_no_trans 
FROM
(Visits LEFT JOIN Transactions ON  (Visits.visit_id  = Transactions.visit_id))
WHERE Transactions.transaction_id  IS NULL 
GROUP BY Visits.customer_id
```

**Explanation**
Hacemos el left join de visita y eso pues solo pueda darme más valores que los de la tabla izquierda. 
Los **JOIN NO SON OPERACIONES EN CONJUNTO**, funcionan similar pero no son. Tipo es como decidir desde donde inicia y se pega una combinatoria.
Tipo aquí si solo haces el join da:


+-------------+
| customer_id |
+-------------+
| 23          |
| 9           |
| 30          |
| 54 
| 54
| 54
| 96          |
| 54          |
| 54          |
+-------------+
Se agregar por que como estoy pegando por id de visita, y el cliente 54 hizo tres transacciones esa visita pues se pone tres veces.
Por ejemplo el cliente 30 no visito ni una vez pero como estoy pegando por ese id se queda.

Ahora por que esto(osea donde no haya transacciones)
```sql
WHERE Transactions.transaction_id  IS NULL 
```
Y no esto 

```sql
WHERE Transactions.visit_id  NOT IN  (Transactions.visit_id)
```

**Por que el select digamos que solo hace un filtro visual, la tabla es la generador por el JOIN y esta tiene NULLS y cuando le pregunta a sql algo tipo¿Esta 1 dentro de (Null)?
pues es decir que hay algo dentro de nada y vale madres**
# 1068 Product Sales Analysis 1

Write a solution to report the product_name, year, and price for each sale_id in the Sales table.

Return the resulting table in any order.

The result format is in the following example.

 

Example 1:

Input: 
Sales table:
+---------+------------+------+----------+-------+
| sale_id | product_id | year | quantity | price |
+---------+------------+------+----------+-------+ 
| 1       | 100        | 2008 | 10       | 5000  |
| 2       | 100        | 2009 | 12       | 5000  |
| 7       | 200        | 2011 | 15       | 9000  |
+---------+------------+------+----------+-------+
Product table:
+------------+--------------+
| product_id | product_name |
+------------+--------------+
| 100        | Nokia        |
| 200        | Apple        |
| 300        | Samsung      |
+------------+--------------+
Output: 
+--------------+-------+-------+
| product_name | year  | price |
+--------------+-------+-------+
| Nokia        | 2008  | 5000  |
| Nokia        | 2009  | 5000  |
| Apple        | 2011  | 9000  |
+--------------+-------+-------+
Explanation: 
From sale_id = 1, we can conclude that Nokia was sold for 5000 in the year 2008.
From sale_id = 2, we can conclude that Nokia was sold for 5000 in the year 2009.
From sale_id = 7, we can conclude that Apple was sold for 9000 in the year 2011.


```sql
# Write your MySQL query statement below
SELECT Product.product_name,Sales.year,Sales.price 
FROM 
(Sales LEFT JOIN Product ON Sales.product_id = Product.product_id)
```

# Replace employee ID with the unique identifier

Write a solution to show the unique ID of each user, If a user does not have a unique ID replace just show null.

Return the result table in any order.

The result format is in the following example.

 

Example 1:

Input: 
Employees table:
+----+----------+
| id | name     |
+----+----------+
| 1  | Alice    |
| 7  | Bob      |
| 11 | Meir     |
| 90 | Winston  |
| 3  | Jonathan |
+----+----------+
EmployeeUNI table:
+----+-----------+
| id | unique_id |
+----+-----------+
| 3  | 1         |
| 11 | 2         |
| 90 | 3         |
+----+-----------+
Output: 
+-----------+----------+
| unique_id | name     |
+-----------+----------+
| null      | Alice    |
| null      | Bob      |
| 2         | Meir     |
| 3         | Winston  |
| 1         | Jonathan |
+-----------+----------+

```sql

SELECT EmployeeUNI.unique_id,Employees.name 
FROM 
(Employees LEFT JOIN EmployeeUNI ON Employees.id = EmployeeUNI.id)
```



# 596 Class with at least 5 students
Write a solution to find all the classes that have at least five students.

Return the result table in any order.

The result format is in the following example.

 

Example 1:

Input: 
Courses table:
+---------+----------+
| student | class    |
+---------+----------+
| A       | Math     |
| B       | English  |
| C       | Math     |
| D       | Biology  |
| E       | Math     |
| F       | Computer |
| G       | Math     |
| H       | Math     |
| I       | Math     |
+---------+----------+
Output: 
+---------+
| class   |
+---------+
| Math    |
+---------+
Explanation: 
- Math has 6 students, so we include it.
- English has 1 student, so we do not include it.
- Biology has 1 student, so we do not include it.
- Computer has 1 student, so we do not include it.
*Solucion*
```sql
# Write your MySQL query statement below
SELECT class
FROM
(SELECT class,COUNT(DISTINCT student) as conteo
FROM Courses
GROUP BY class) tabla
WHERE conteo >= 5
```
Pero en la web esta está solución tan bonita:

```sql
select class 
from Courses
group by class
having count(*)>=5;
```
Me falta usar de merjo manera el having

# Product sales analysis III
Write a solution to find all sales that occurred in the first year each product was sold.

For each product_id, identify the earliest year it appears in the Sales table.

Return all sales entries for that product in that year.

Return a table with the following columns: product_id, first_year, quantity, and price.
Return the result in any order.

 

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


*Mi solucion*
Pues bueno, auiq tuve problemas pero no se excatmente por que. Creo mi primera solución, tenía elementos repetidos o algo. La verdad me parecía correcta. Pero salió con esta de aquí
```sql
SELECT product_id,first_year,quantity,price
FROM
SALES
RIGHT JOIN
(SELECT min(year) as first_year, product_id as p
FROM Sales
GROUP BY product_id) Tabla
ON 
product_id = p AND year = first_year
```
Mi otra solución que igual veía bien era la siguiente
```sql
SELECT Sales.product_id,first_year, quantity,price
FROM
Sales
LEFT JOIN
(SELECT product_id,min(year) as first_year FROM Sales GROUP BY product_id) First_year
ON First_year.product_id = Sales.product_id
WHERE Sales.year in
(SELECT min(year) as first_year FROM Sales GROUP BY product_id) 
```
Basicamente la segunda, devuelve todas las ventas correspondientes de los primeros años, la segunda devuelve todas las ventas en los primeros años relacionadas a ese producto. Segun yo la descripción quedaba más con la segunda pero bueno.

Output: 
+------------+------------+----------+-------+
| product_id | first_year | quantity | price |
+------------+------------+----------+-------+ 
| 100        | 2008       | 10       | 5000  |
| 200        | 2011       | 15       | 9000  |
+------------+------------+----------+-------+


# 550. Game Play Analysis IV
Write a solution to report the fraction of players that logged in again on the day after the day they first logged in, rounded to 2 decimal places. In other words, you need to determine the number of players who logged in on the day immediately following their initial login, and divide it by the number of total players.

The result format is in the following example.

 

Example 1:

Input: 
Activity table:
+-----------+-----------+------------+--------------+
| player_id | device_id | event_date | games_played |
+-----------+-----------+------------+--------------+
| 1         | 2         | 2016-03-01 | 5            |
| 1         | 2         | 2016-03-02 | 6            |
| 2         | 3         | 2017-06-25 | 1            |
| 3         | 1         | 2016-03-02 | 0            |
| 3         | 4         | 2018-07-03 | 5            |
+-----------+-----------+------------+--------------+
Output: 
+-----------+
| fraction  |
+-----------+
| 0.33      |
+-----------+

*Psuedo-algoritomo*
Basicamente sigo lo siguiente
- Encontrar el primer logged-in
- Ver si se loggeo dos dias seguidos pero solo del primer logged in, y contar la cantidad de jugadores que cumplen eso
- Contar el total, para sacar el porcentaje de jugadadores que se logearon dos dias seguidos en su primer logged in
Mi primer aproach fue con la funcion de ventaja LAG(), pero como no puedes usarla en la where clause ocupas muchas subquerries, es posible pero no lo recomiendo.
Luego hice lo siguiente:
```sql
SELECT ROUND(IFNULL(Streak.day_after/COUNT(DISTINCT Activity.player_id),0),2) AS fraction
FROM 
Activity
LEFT JOIN

(SELECT A1.player_id,A1.event_date,COUNT(A2.player_id) as day_after
FROM
Activity A1
LEFT JOIN
(SELECT player_id, MIN(event_date) as first_logged_in
FROM Activity
GROUP BY player_id) A2
ON A1.player_id = A2.player_id
AND A1.event_date = DATE_ADD(first_logged_in, INTERVAL 1 DAY)) Streak

ON Activity.player_id = Streak.player_id
AND Activity.event_date = Streak.event_date
```
Que pues basicamente es una jerarquia de tres subquerries
Esta parte obtiene el primer logged in de cada jugadores
```sql
SELECT player_id, MIN(event_date) as first_logged_in
FROM Activity
GROUP BY player_id
```
Luego pego la tabla anterior con mi tabal original de tal forma que solo se peguen cuando se cumple A1.event_date = DATE_ADD(first_logged_in, INTERVAL 1 DAY), que pues bueno es que se conecto al dia siguiente del first_logged_in
```sql

SELECT A1.player_id,A1.event_date,COUNT(A2.player_id) as day_after
FROM
Activity A1
LEFT JOIN
(SELECT player_id, MIN(event_date) as first_logged_in
FROM Activity
GROUP BY player_id) A2
ON A1.player_id = A2.player_id
AND A1.event_date = DATE_ADD(first_logged_in, INTERVAL 1 DAY)
```
Ya pues nada mas cuentas el total de jugadores y sacas el fraction.
*LEETCODE SOLUTION*
Ahora en comparacion la funcion de leetcode recoemndada es muy bonita, en complejidad es similar pero es mil veces más entendible:
```sql
SELECT
  ROUND(COUNT(DISTINCT player_id) / (SELECT COUNT(DISTINCT player_id) FROM Activity), 2) AS fraction
FROM
  Activity
WHERE
  (player_id, DATE_SUB(event_date, INTERVAL 1 DAY))
  IN (
    SELECT player_id, MIN(event_date) AS first_login FROM Activity GROUP BY player_id
  )
```
Aqui lo interesante es el WHERE. De inicio no sabia que podias usar subquerries en el where jajaja
Con lo siguiente, igual saca el primer logged in por jugador
```sql
SELECT player_id, MIN(event_date) AS first_login FROM Activity GROUP BY player_id
```
Aqui usan muy bien el operador IN, primero saca cual es el día anterior de todos los datos.
Pero solo se queda los que su dia anterior esten dentro de la lista de primeros dias(que bueno chance da problemas cuando dos jugadores comparten el primer dia o algo asi)

```sql
  (player_id, DATE_SUB(event_date, INTERVAL 1 DAY))
  IN (
    SELECT player_id, MIN(event_date) AS first_login FROM Activity GROUP BY player_id
  )
```
Igual usa una subquerry dentro del select, que pues da el total y simplifica miucho el codigo. IGUAL no sabia que podias usarlas dentro de SELECT


# ME FALTA UNO

# 1193. Monthly Transactions I
Table: Transactions

+---------------+---------+
| Column Name   | Type    |
+---------------+---------+
| id            | int     |
| country       | varchar |
| state         | enum    |
| amount        | int     |
| trans_date    | date    |
+---------------+---------+
id is the primary key of this table.
The table has information about incoming transactions.
The state column is an enum of type ["approved", "declined"].
 

Write an SQL query to find for each month and country, the number of transactions and their total amount, the number of approved transactions and their total amount.

Return the result table in any order.

The query result format is in the following example.

 

Example 1:

Input: 
Transactions table:
+------+---------+----------+--------+------------+
| id   | country | state    | amount | trans_date |
+------+---------+----------+--------+------------+
| 121  | US      | approved | 1000   | 2018-12-18 |
| 122  | US      | declined | 2000   | 2018-12-19 |
| 123  | US      | approved | 2000   | 2019-01-01 |
| 124  | DE      | approved | 2000   | 2019-01-07 |
+------+---------+----------+--------+------------+
Output: 
+----------+---------+-------------+----------------+--------------------+-----------------------+
| month    | country | trans_count | approved_count | trans_total_amount | approved_total_amount |
+----------+---------+-------------+----------------+--------------------+-----------------------+
| 2018-12  | US      | 2           | 1              | 3000               | 1000                  |
| 2019-01  | US      | 1           | 1              | 2000               | 2000                  |
| 2019-01  | DE      | 1           | 1              | 2000               | 2000                  |
+----------+---------+-------------+----------------+--------------------+-----------------------+
 
*Notas*
Pues bueno este es algo mas largo el codiog es: 
```sql
SELECT 
DATE_FORMAT(trans_date,"%Y-%m")  AS month,
country,
COUNT(id) as trans_count,
COUNT(CASE WHEN state = "approved" THEN id ELSE NULL END) AS approved_count,
SUM(amount) as trans_total_amount,
SUM(CASE WHEN state = "approved" THEN amount ELSE 0 END) AS approved_total_amount
FROM Transactions
GROUP BY month,country
```
Basicamente para cambiar el formato de fecha se usa *DATE_FORMAT*, igual existe *FORMAT* pero eso es para otros formatos. Te permite cambiar todo la parte del mes aqui hay varias variaciones y se pone con % antecedido. Tipo %c es mes pero de 1-12, %m es de 01-12 y %M es el mes pero en string. Para este caso por que igual depende de la version de sql que tengas, pa ver más info de eso esta este link: https://www.w3schools.com/sql/func_mysql_date_format.asp
Luego un comando muy util que no conocia es
```sql
CASE WHEN state = "approved" THEN id ELSE NULL END
```
QUE ES BUENO SIMILAR A UN NP.WHERE(),pero con ocupas las funciones de agregaciones por que si no las columnas no van a concordar en caso de que tengas diferentes filtros.

# 1633 Percentage of users acepted.
+-------------+---------+
| Column Name | Type    |
+-------------+---------+
| user_id     | int     |
| user_name   | varchar |
+-------------+---------+
user_id is the primary key (column with unique values) for this table.
Each row of this table contains the name and the id of a user.
 

Table: Register

+-------------+---------+
| Column Name | Type    |
+-------------+---------+
| contest_id  | int     |
| user_id     | int     |
+-------------+---------+
(contest_id, user_id) is the primary key (combination of columns with unique values) for this table.
Each row of this table contains the id of a user and the contest they registered into.
 

Write a solution to find the percentage of the users registered in each contest rounded to two decimals.

Return the result table ordered by percentage in descending order. In case of a tie, order it by contest_id in ascending order.

The result format is in the following example.

 

Example 1:

Input: 
Users table:
+---------+-----------+
| user_id | user_name |
+---------+-----------+
| 6       | Alice     |
| 2       | Bob       |
| 7       | Alex      |
+---------+-----------+
Register table:
+------------+---------+
| contest_id | user_id |
+------------+---------+
| 215        | 6       |
| 209        | 2       |
| 208        | 2       |
| 210        | 6       |
| 208        | 6       |
| 209        | 7       |
| 209        | 6       |
| 215        | 7       |
| 208        | 7       |
| 210        | 2       |
| 207        | 2       |
| 210        | 7       |
+------------+---------+
Output: 
+------------+------------+
| contest_id | percentage |
+------------+------------+
| 208        | 100.0      |
| 209        | 100.0      |
| 210        | 100.0      |
| 215        | 66.67      |
| 207        | 33.33      |
+------------+------------+

```sql
SELECT Register.contest_id,
IFNULL(ROUND(COUNT(Register.contest_id)/total_usuarios,4),0)*100 AS percentage
FROM 
Register
JOIN
(SELECT Users.user_id, Count(DISTINCT user_id) as total_usuarios
FROM Users
) Tabla
GROUP BY
Register.contest_id
ORDER BY
percentage  DESC, Register.contest_id ASC
```
*NOTAS*
Aqui para usar el total lo saque y luego hice u full outer join para agregarlo a todo, ocmo es un solo dato el total al hacer el aouter join es como si agregaras una columna
Igual puedes agregarla, pero eso modificaria la base de datos
# 1075 Project Employees I
+-------------+---------+
| Column Name | Type    |
+-------------+---------+
| project_id  | int     |
| employee_id | int     |
+-------------+---------+
(project_id, employee_id) is the primary key of this table.
employee_id is a foreign key to Employee table.
Each row of this table indicates that the employee with employee_id is working on the project with project_id.
 

Table: Employee

+------------------+---------+
| Column Name      | Type    |
+------------------+---------+
| employee_id      | int     |
| name             | varchar |
| experience_years | int     |
+------------------+---------+
employee_id is the primary key of this table. It's guaranteed that experience_years is not NULL.
Each row of this table contains information about one employee.
 

Write an SQL query that reports the average experience years of all the employees for each project, rounded to 2 digits.

Return the result table in any order.

The query result format is in the following example.

 

Example 1:

Input: 
Project table:
+-------------+-------------+
| project_id  | employee_id |
+-------------+-------------+
| 1           | 1           |
| 1           | 2           |
| 1           | 3           |
| 2           | 1           |
| 2           | 4           |
+-------------+-------------+
Employee table:
+-------------+--------+------------------+
| employee_id | name   | experience_years |
+-------------+--------+------------------+
| 1           | Khaled | 3                |
| 2           | Ali    | 2                |
| 3           | John   | 1                |
| 4           | Doe    | 2                |
+-------------+--------+------------------+
Output: 
+-------------+---------------+
| project_id  | average_years |
+-------------+---------------+
| 1           | 2.00          |
| 2           | 2.50          |
+-------------+---------------+
Explanation: The average experience years for the first project is (3 + 2 + 1) / 3 = 2.00 and for the second project is (3 + 2) / 2 = 2.50

```sql
SELECT Project.project_id, 
IFNULL(ROUND(AVG(Employee.experience_years),2),0) AS average_years
FROM
Project
LEFT JOIN
Employee
ON Project.employee_id = Employee.employee_id
GROUP BY Project.project_id
```

# 1251 Average Selling prices 

Table: Prices

+---------------+---------+
| Column Name   | Type    |
+---------------+---------+
| product_id    | int     |
| start_date    | date    |
| end_date      | date    |
| price         | int     |
+---------------+---------+
(product_id, start_date, end_date) is the primary key (combination of columns with unique values) for this table.
Each row of this table indicates the price of the product_id in the period from start_date to end_date.
For each product_id there will be no two overlapping periods. That means there will be no two intersecting periods for the same product_id.
 

Table: UnitsSold

+---------------+---------+
| Column Name   | Type    |
+---------------+---------+
| product_id    | int     |
| purchase_date | date    |
| units         | int     |
+---------------+---------+
This table may contain duplicate rows.
Each row of this table indicates the date, units, and product_id of each product sold. 
 

Write a solution to find the average selling price for each product. average_price should be rounded to 2 decimal places. If a product does not have any sold units, its average selling price is assumed to be 0.

Return the result table in any order.

The result format is in the following example.

 

Example 1:

Input: 
Prices table:
+------------+------------+------------+--------+
| product_id | start_date | end_date   | price  |
+------------+------------+------------+--------+
| 1          | 2019-02-17 | 2019-02-28 | 5      |
| 1          | 2019-03-01 | 2019-03-22 | 20     |
| 2          | 2019-02-01 | 2019-02-20 | 15     |
| 2          | 2019-02-21 | 2019-03-31 | 30     |
+------------+------------+------------+--------+
UnitsSold table:
+------------+---------------+-------+
| product_id | purchase_date | units |
+------------+---------------+-------+
| 1          | 2019-02-25    | 100   |
| 1          | 2019-03-01    | 15    |
| 2          | 2019-02-10    | 200   |
| 2          | 2019-03-22    | 30    |
+------------+---------------+-------+
Output: 
+------------+---------------+
| product_id | average_price |
+------------+---------------+
| 1          | 6.96          |
| 2          | 16.96         |
+------------+---------------+


```sql
SELECT Prices.product_id, 
IFNULL(ROUND(
SUM(Prices.price*UnitsSold.units)
/
SUM(UnitsSold.units)
,2),0)
AS average_price #(Prices.price*UnitsSold.units)/
FROM
Prices
LEFT JOIN 
UnitsSold
ON
Prices.product_id = UnitsSold.product_id 
AND UnitsSold.purchase_date BETWEEN Prices.start_date AND Prices.end_date 
GROUP BY Prices.product_id
```

*Notas*
Aquí bues basicamente hay dos puntos importantes a mencionar:
 -Basicamente depende la fecha el precio, y por tanto el promedio que te sale es diferente para asegurarte que el JOIN no te de demas por una fecha diferente usas lo siguiente:

```sql
UnitsSold.purchase_date BETWEEN Prices.start_date AND Prices.end_date 
```
 - Luego por asunto de sustituir NULL de una columna sin tener que hacer un JOIN con la tabla updateado con valors substituidos pues hay como 3 comandos que a veces funcionan y aveces no dependiendo de donde trabajes: ISNULL(),IFNULL(), COALESCE(). Basicamente el COALESCE() da el primver valor no null de una columna o de un set de columnas


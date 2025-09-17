# 1907. Count Salary Categories
Write a solution to calculate the number of bank accounts for each salary category. The salary categories are:

"Low Salary": All the salaries strictly less than $20000.
"Average Salary": All the salaries in the inclusive range [$20000, $50000].
"High Salary": All the salaries strictly greater than $50000.
The result table must contain all three categories. If there are no accounts in a category, return 0.

Return the result table in any order.

The result format is in the following example.

 

Example 1:

Input: 
Accounts table:
+------------+--------+
| account_id | income |
+------------+--------+
| 3          | 108939 |
| 2          | 12747  |
| 8          | 87709  |
| 6          | 91796  |
+------------+--------+
Output: 
+----------------+----------------+
| category       | accounts_count |
+----------------+----------------+
| Low Salary     | 1              |
| Average Salary | 0              |
| High Salary    | 3              |
+----------------+----------------+
Explanation: 
Low Salary: Account 2.
Average Salary: No accounts.
High Salary: Accounts 3, 6, and 8.


**NOTAS**

Pues aquí, lo complicado es que no te dan la tabla de categorias, entonces si hay null pues no puedes aplicar el clásico de hacer un join a la tabla en donde se especifica eso. Yo lo hice asi:
```sql
Select Table2.category, IFNULL(Table1.accounts_count,0) as accounts_count
FROM
(SELECT 
(CASE 
WHEN income < 20000 THEN "Low Salary"
WHEN income <= 50000 AND income >= 20000 THEN "Average Salary"
ELSE "High Salary" END) AS category,
COUNT(account_id) as accounts_count
FROM Accounts 
GROUP BY category) Table1
RIGHT JOIN
(SELECT 'Low Salary' AS category FROM DUAL
UNION ALL
SELECT 'Average Salary' FROM DUAL
UNION ALL
SELECT 'High Salary' FROM DUAL) Table2
ON Table2.category = Table1.category
```
Lo importante es **las union**:
``` sql
SELECT 'Low Salary' AS category FROM DUAL
UNION ALL
SELECT 'Average Salary' FROM DUAL
UNION ALL
SELECT 'High Salary' FROM DUAL
```
**DUAL** pues es para decir que vas a llamar una constante, es como una tabla que no tiene que estar delcarada.

# 1204. Last Person to Fit in the Bus
There is a queue of people waiting to board a bus. However, the bus has a weight limit of 1000 kilograms, so there may be some people who cannot board.

Write a solution to find the person_name of the last person that can fit on the bus without exceeding the weight limit. The test cases are generated such that the first person does not exceed the weight limit.

Note that only one person can board the bus at any given turn.

The result format is in the following example.

 

Example 1:

Input: 
Queue table:
+-----------+-------------+--------+------+
| person_id | person_name | weight | turn |
+-----------+-------------+--------+------+
| 5         | Alice       | 250    | 1    |
| 4         | Bob         | 175    | 5    |
| 3         | Alex        | 350    | 2    |
| 6         | John Cena   | 400    | 3    |
| 1         | Winston     | 500    | 6    |
| 2         | Marie       | 200    | 4    |
+-----------+-------------+--------+------+
Output: 
+-------------+
| person_name |
+-------------+
| John Cena   |
+-------------+
Explanation: The folowing table is ordered by the turn for simplicity.
+------+----+-----------+--------+--------------+
| Turn | ID | Name      | Weight | Total Weight |
+------+----+-----------+--------+--------------+
| 1    | 5  | Alice     | 250    | 250          |
| 2    | 3  | Alex      | 350    | 600          |
| 3    | 6  | John Cena | 400    | 1000         | (last person to board)
| 4    | 2  | Marie     | 200    | 1200         | (cannot board)
| 5    | 4  | Bob       | 175    | ___          |
| 6    | 1  | Winston   | 500    | ___          |
+------+----+-----------+--------+--------------+



*NOTAS *
Pues tiempo = 35 min. Mi objetivoe era menos de 30min. Me tarde viendo como traer el ultimo miembro de la query intente con having pero por algun motivo no funciono
Igual la solucion la tenia medio bien desde la 15. Aqui use una fabulosa WINDOW FUNCTION y mi eficiencia estuvo bien
```sql
# Write your MySQL query statement below
# limite de 1000kg
# ultima persona antes del limite
#pseudo.
# acomodar por turno
# hacer la cumulativa hasta ahi
# y ver la ultima persona cuya sumatoria es menor al turno
-- SELECT person_name 
-- FROM

-- (SELECT person_name,cumulative_weight
-- FROM
SELECT person_name
FROM
(SELECT person_name,cumulative_weight
FROM
(SELECT person_name,turn,weight,
SUM(weight) OVER (order by turn,person_id) as cumulative_weight 
FROM Queue
ORDER BY turn,person_id) Tabla
WHERE cumulative_weight <=1000
ORDER BY cumulative_weight DESC) Tabla2
LIMIT 1

```
Lo importante es la window function que va acumulando el peso y el limit que solo muestra un dato y lo ordeno para que muestre el más alto

# 180 Consecutive Numbers
Find all numbers that appear at least three times consecutively.

Return the result table in any order.

The result format is in the following example.

 

Example 1:

Input: 
Logs table:
+----+-----+
| id | num |
+----+-----+
| 1  | 1   |
| 2  | 1   |
| 3  | 1   |
| 4  | 2   |
| 5  | 1   |
| 6  | 2   |
| 7  | 2   |
+----+-----+
Output: 
+-----------------+
| ConsecutiveNums |
+-----------------+
| 1               |
+-----------------+
Explanation: 1 is the only number that appears consecutively for at least three times.

*Solución*

```sql
SELECT Tabla.num as ConsecutiveNums
FROM
(SELECT num, id,
LAG(num,1) OVER (ORDER BY id) as lag_1,
LAG(num,2) OVER (ORDER BY id) as lag_2
FROM Logs) Tabla
WHERE 
num = lag_1 and lag_1 = lag_2
GROUP BY num
```

# 610 Triangle Judgement
Report for every three line segments whether they can form a triangle.

Return the result table in any order.

The result format is in the following example.

 

Example 1:

Input: 
Triangle table:
+----+----+----+
| x  | y  | z  |
+----+----+----+
| 13 | 15 | 30 |
| 10 | 20 | 15 |
+----+----+----+
Output: 
+----+----+----+----------+
| x  | y  | z  | triangle |
+----+----+----+----------+
| 13 | 15 | 30 | No       |
| 10 | 20 | 15 | Yes      |
+----+----+----+----------+


*Solution*
```sql
SELECT
x,y,z,
(CASE WHEN (x < y+z AND y <x+z AND z<x+y) THEN "Yes" Else "No" END) AS triangle
#podria lit probar los tres casos, pero quiero hacerlo mas elegante
FROM Triangle
```
Aqui lo complicado es ver que es un triangulo, que pues bueno dicen: cuando el lado mas largo es menor que la suma de los otros dos. Que es cierto para
la hipotenusa, pero no pasa en todos los espacios y la definición me parece muy mala. Pero bueno es la solución pese a que sea matematicamente incorrecta.

# 1789 Primary department for each employee

(employee_id, department_id) is the primary key (combination of columns with unique values) for this table.
employee_id is the id of the employee.
department_id is the id of the department to which the employee belongs.
primary_flag is an ENUM (category) of type ('Y', 'N'). If the flag is 'Y', the department is the primary department for the employee. If the flag is 'N', the department is not the primary.
 

Employees can belong to multiple departments. When the employee joins other departments, they need to decide which department is their primary department. Note that when an employee belongs to only one department, their primary column is 'N'.

Write a solution to report all the employees with their primary department. For employees who belong to one department, report their only department.

Return the result table in any order.

The result format is in the following example.

 

Example 1:

Input: 
Employee table:
+-------------+---------------+--------------+
| employee_id | department_id | primary_flag |
+-------------+---------------+--------------+
| 1           | 1             | N            |
| 2           | 1             | Y            |
| 2           | 2             | N            |
| 3           | 3             | N            |
| 4           | 2             | N            |
| 4           | 3             | Y            |
| 4           | 4             | N            |
+-------------+---------------+--------------+
Output: 
+-------------+---------------+
| employee_id | department_id |
+-------------+---------------+
| 1           | 1             |
| 2           | 1             |
| 3           | 3             |
| 4           | 3             |
+-------------+---------------+

*Solucion*

Pues, bueno como no lo pide ordenado lo que se me hice mas sencillo fue juntar dos querys:
```sql
SELECT employee_id,department_id
FROM Employee
WHERE primary_flag = "Y"
UNION
SELECT employee_id,department_id
FROM Employee
GROUP BY employee_id
HAVING count(DISTINCT department_id) = 1
```
Una con los primary department explicitamente marcados union la otra en la que no estan marcados.

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

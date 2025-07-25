# 580 Manager with at least 5 Direct Reports
Write a solution to find managers with at least five direct reports.

Return the result table in any order.

The result format is in the following example.

 

Example 1:

Input: 
Employee table:
+-----+-------+------------+-----------+
| id  | name  | department | managerId |
+-----+-------+------------+-----------+
| 101 | John  | A          | null      |
| 102 | Dan   | A          | 101       |
| 103 | James | A          | 101       |
| 104 | Amy   | A          | 101       |
| 105 | Anne  | A          | 101       |
| 106 | Ron   | B          | 101       |
+-----+-------+------------+-----------+
Output: 
+------+
| name |
+------+
| John |
+------+


``` sql
SELECT Employee.name
FROM

(SELECT managerID,name,COUNT(managerID) as Conteo
FROM employee
WHERE managerID IS NOT null
GROUP BY managerID) Conteo
RIGHT JOIN
Employee
ON Conteo.managerID = Employee.id
Where Conteo IS NOT NULL
AND Conteo>=5
```

# 1280 Student and Examinations

Write a solution to find the number of times each student attended each exam.

Return the result table ordered by student_id and subject_name.

The result format is in the following example.

 

Example 1:

Input: 
Students table:
+------------+--------------+
| student_id | student_name |
+------------+--------------+
| 1          | Alice        |
| 2          | Bob          |
| 13         | John         |
| 6          | Alex         |
+------------+--------------+
Subjects table:
+--------------+
| subject_name |
+--------------+
| Math         |
| Physics      |
| Programming  |
+--------------+
Examinations table:
+------------+--------------+
| student_id | subject_name |
+------------+--------------+
| 1          | Math         |
| 1          | Physics      |
| 1          | Programming  |
| 2          | Programming  |
| 1          | Physics      |
| 1          | Math         |
| 13         | Math         |
| 13         | Programming  |
| 13         | Physics      |
| 2          | Math         |
| 1          | Math         |
+------------+--------------+
Output: 
+------------+--------------+--------------+----------------+
| student_id | student_name | subject_name | attended_exams |
+------------+--------------+--------------+----------------+
| 1          | Alice        | Math         | 3              |
| 1          | Alice        | Physics      | 2              |
| 1          | Alice        | Programming  | 1              |
| 2          | Bob          | Math         | 1              |
| 2          | Bob          | Physics      | 0              |
| 2          | Bob          | Programming  | 1              |
| 6          | Alex         | Math         | 0              |
| 6          | Alex         | Physics      | 0              |
| 6          | Alex         | Programming  | 0              |
| 13         | John         | Math         | 1              |
| 13         | John         | Physics      | 1              |
| 13         | John         | Programming  | 1              |
+------------+--------------+--------------+----------------+

My solución es: 
```sql
SELECT ExamenesTotales.student_id, ExamenesTotales.student_name, ExamenesTotales.subject_name,COUNT(Tabla.subject_name) as attended_exams 
FROM

(SELECT Examinations.student_id, Students.student_name, Examinations.subject_name FROM
Examinations LEFT JOIN Students ON
Students.student_id = Examinations.student_id) Tabla

RIGHT JOIN

(SELECT Students.student_id, Subjects.subject_name, Students.student_name
FROM Students JOIN Subjects) ExamenesTotales

ON 
ExamenesTotales.student_id = Tabla.student_id AND 
ExamenesTotales.subject_name  = Tabla.subject_name

GROUP BY
ExamenesTotales.student_id,ExamenesTotales.subject_name
ORDER BY
ExamenesTotales.student_id, ExamenesTotales.subject_name
```
Al inicio pense que se podía en un solo join, chance sí. Pero no encontre la forma
Aqui a destacar tres puntos. De inicio el problema da que chance un alumno no hizo todos los examenes o que de plano no hizo ninguno.
Entonces tienes que hacer una tablas de los examenes que debió haber hecho. Para eso haces un **cross join entre las materias y estudiantes**.
Ya de ahí por los datos que te pide tienes que hacer un join entre examinations y students.
Aquí otro tema, que fue uno de los motivos por los que me tarde **COUNT(tabla1) != COUNT(TABLA2)**. Osea que si requieres hacer un count mientras haces un join. El conteo
resultante va a ser de la respectiva tabla puesta y luego unido al join.
Para evitar que el count me da muchos resultados uso:
```sql
ExamenesTotales.student_id = Tabla.student_id AND 
ExamenesTotales.subject_name  = Tabla.subject_name
```
Pues si solo lo hago con la id pues en examinations se repite la id por cada examen.Ahora le agrego el subject para que no se repita.
En el caso de que no este una materia, pues se queda por el tipo de join.


# 577 Employee Bonus


Write a solution to report the name and bonus amount of each employee with a bonus less than 1000.

Return the result table in any order.

The result format is in the following example.

 

Example 1:

Input: 
Employee table:
+-------+--------+------------+--------+
| empId | name   | supervisor | salary |
+-------+--------+------------+--------+
| 3     | Brad   | null       | 4000   |
| 1     | John   | 3          | 1000   |
| 2     | Dan    | 3          | 2000   |
| 4     | Thomas | 3          | 4000   |
+-------+--------+------------+--------+
Bonus table:
+-------+-------+
| empId | bonus |
+-------+-------+
| 2     | 500   |
| 4     | 2000  |
+-------+-------+
Output: 
+------+-------+
| name | bonus |
+------+-------+
| Brad | null  |
| John | null  |
| Dan  | 500   |
+------+-------+


```sql
# Write your MySQL query statement below
SELECT Employee.name, Bonus.bonus
FROM (Employee LEFT JOIN Bonus ON Employee.empID = Bonus.EmpId)
Where Bonus.bonus is NULL OR Bonus.bonus < 1000
```

# 1661 Average time process per machine


There is a factory website that has several machines each running the same number of processes. Write a solution to find the average time each machine takes to complete a process.

The time to complete a process is the 'end' timestamp minus the 'start' timestamp. The average time is calculated by the total time to complete every process on the machine divided by the number of processes that were run.

The resulting table should have the machine_id along with the average time as processing_time, which should be rounded to 3 decimal places.

Return the result table in any order.

The result format is in the following example.

 

Example 1:

Input: 
Activity table:
+------------+------------+---------------+-----------+
| machine_id | process_id | activity_type | timestamp |
+------------+------------+---------------+-----------+
| 0          | 0          | start         | 0.712     |
| 0          | 0          | end           | 1.520     |
| 0          | 1          | start         | 3.140     |
| 0          | 1          | end           | 4.120     |
| 1          | 0          | start         | 0.550     |
| 1          | 0          | end           | 1.550     |
| 1          | 1          | start         | 0.430     |
| 1          | 1          | end           | 1.420     |
| 2          | 0          | start         | 4.100     |
| 2          | 0          | end           | 4.512     |
| 2          | 1          | start         | 2.500     |
| 2          | 1          | end           | 5.000     |
+------------+------------+---------------+-----------+
Output: 
+------------+-----------------+
| machine_id | processing_time |
+------------+-----------------+
| 0          | 0.894           |
| 1          | 0.995           |
| 2          | 1.456           |
+------------+-----------------+


```sql

# Todas las maquinas corren la misma cantidad de procesos. Es decir si la maquina 0 corre el proceso 0,1,2. El resto igual corre el mismo
# Tiempo promedio en completar un proceso.
# voy a hacerlo con un self JOin
SELECT A1.machine_id #
,ROUND(AVG(A2.timestamp - A1.timestamp),3) as processing_time
FROM 
(Activity A1 JOIN Activity A2
ON
A1.process_id = A2.process_id AND
A1.machine_id = A2.machine_id AND
A1.activity_type = 'start' AND A2.activity_type = 'END')
GROUP BY A1.machine_id
```
Pues aqui redonde coun ROUND(col/val,no de decimales) y el promedio con AVG. Agrupo por el identificador único que es (machine id, process id, activity type)
Hago el join en los mismos procesos de las mismas maquinas pero con el inicio y el final. Así solo me da start y end en una misma fila
Pero **es inefciente**

**Sol de LEETCODE**

```sql
SELECT a.machine_id, 
       ROUND(AVG(b.timestamp - a.timestamp), 3) AS processing_time
FROM Activity a, 
     Activity b
WHERE 
    a.machine_id = b.machine_id
AND 
    a.process_id = b.process_id
AND 
    a.activity_type = 'start'
AND 
    b.activity_type = 'end'
GROUP BY machine_id
```

Osea la lógica esta bien, lo que hace más efcieinte so solución es que no ahce la combinatoria, solo se queda con los anteriores.

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
(SELECT id, temperature,
LAG(temperature) OVER(ORDER BY recordDate) as retraso,
DATEDIFF(recordDate,LAG(recordDate) OVER(ORDER BY recordDate)) AS deltaDias
FROM Weather) tarantino
WHERE temperature > retraso AND deltaDias =1
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
Aqui datediff se hace para asegurar que sea **solo respecto al valor anterior**

**CON JOINS**
Basicamente haces un self join, para hacer un producto cartesiano.
Recordemos que el producto cartesiano entre de conjuntos es el conjunto de todas las posibles combinaciones entre elementos.
Osea seria producto cartesiano por fecha, entonces es como digamos tengo 1 junio,2 junio, 3 junio.
Tipo para combino con si mismo (1 junio, 1 junio), (1 junio, 2 junio), (1 junio, 3 junio)
Pero solo pones un condicional para que te quedes solo con el par que tenga una diferencia de 1 día
Es decir:
```sql

SELECT 
    w1.id
FROM 
    Weather w1
JOIN 
    Weather w2
ON 
    DATEDIFF(w1.recordDate, w2.recordDate) = 1
WHERE 
    w1.temperature > w2.temperature;
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



# 1757 LOW FATS AND RECYCLABLE
Write a solution to find the ids of products that are both low fat and recyclable.

Return the result table in any order.

The result format is in the following example.

 

Example 1:

Input: 
Products table:

| product\_id | low\_fats | recyclable |
| ----------- | --------- | ---------- |
| 0           | Y         | N          |
| 1           | Y         | Y          |
| 2           | N         | Y          |
| 3           | Y         | Y          |
| 4           | N         | N          |

Output: 
| product\_id |
| ----------- |
| 1           |
| 3           |


```sql
select product_id from Products where low_fats = 'Y' and recyclable  = 'Y'
```
Explanation: Only products 1 and 3 are both low fat and recyclable.

# 584 FIND CUSTOMER REFEREE

Find the names of the customer that are not referred by the customer with id = 2.

Return the result table in any order.

The result format is in the following example.

 

Example 1:

Input: 
Customer table:
+----+------+------------+
| id | name | referee_id |
+----+------+------------+
| 1  | Will | null       |
| 2  | Jane | null       |
| 3  | Alex | 2          |
| 4  | Bill | null       |
| 5  | Zack | 1          |
| 6  | Mark | 2          |
+----+------+------------+
Output: 
+------+
| name |
+------+
| Will |
| Jane |
| Bill |
| Zack |
+------+




```sql
SELECT name FROM CUSTOMER WHERE NOT (referee_id  = 2) OR referee_id IS NULL
```
**EL FILTRO QUITA POR DEFECTO LOS NULL** por tanto le quieres poner is null
# 595 BIG COUNTRIES 


A country is big if:

it has an area of at least three million (i.e., 3000000 km2), or
it has a population of at least twenty-five million (i.e., 25000000).
Write a solution to find the name, population, and area of the big countries.

Return the result table in any order.

The result format is in the following example.

 

Example 1:

Input: 
World table:
+-------------+-----------+---------+------------+--------------+
| name        | continent | area    | population | gdp          |
+-------------+-----------+---------+------------+--------------+
| Afghanistan | Asia      | 652230  | 25500100   | 20343000000  |
| Albania     | Europe    | 28748   | 2831741    | 12960000000  |
| Algeria     | Africa    | 2381741 | 37100000   | 188681000000 |
| Andorra     | Europe    | 468     | 78115      | 3712000000   |
| Angola      | Africa    | 1246700 | 20609294   | 100990000000 |
+-------------+-----------+---------+------------+--------------+
Output: 
+-------------+------------+---------+
| name        | population | area    |
+-------------+------------+---------+
| Afghanistan | 25500100   | 652230  |
| Algeria     | 37100000   | 2381741 |
+-------------+------------+---------+


```sql
SELECT name,population,area FROM World WHERE  population >= 25000000 OR area  >= 3000000
```

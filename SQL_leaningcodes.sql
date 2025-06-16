
SELECT orders.OrderID, customers.CustomerName, shippers.ShipperName 
from (orders INNER JOIN customers on orders.customerID = customers.customerID) INNER JOIN shippers ON orders.ShipperID = shippers.ShipperID;


SELECT customers.CustomerName, orders.OrderID
from customers
INNER JOIN orders ON customers.customerID = orders.customerID
ORDER BY customers.CustomerName DESC;


SELECT c.customerID,c.CustomerName,o.OrderID,o.OrderDate
from customers as c
LEFT JOIN orders as o
ON c.customerID = o.CustomerID

UNION

SELECT c.customerID,c.CustomerName,o.OrderID,o.OrderDate
from customers as c
RIGHT JOIN orders as o
ON c.customerID = o.CustomerID;



SELECT 
A.CustomerName as CustomerName1,
B.CustomerName as CustomerName2, A.City
from customers A, customers B
WHERE A.CustomerID <> B.CustomerID
AND A.City = B.City
ORDER BY A.City;


SELECT COUNT(CustomerID) as a, Country
from customers
GROUP BY Country
ORDER BY a;


SELECT COUNT(ShipperID)
from 
GROUP BY



SELECT COUNT(dwa.OrderID),dwa.ShipperName
from
(SELECT o.ShipperID, o.OrderID,s.ShipperName
from orders as o
LEFT JOIN shippers as s 
ON o.ShipperID = s.ShipperID) as dwa
GROUP BY dwa.ShipperName;



SELECT COUNT(CustomerID),Country
from customers
GROUP BY Country
HAVING COUNT(CustomerID )>6
ORDER BY COUNT(CustomerID) DESC;

SELECT employees.LastName, COUNT(orders.OrderID) AS NumeroDeOrdenes
from(
    orders
    INNER JOIN
    employees
    ON employees.EmployeeID = orders.EmployeeID
    -- WHERE LastName = "Davolio" OR LastName= "Fuller"
)
GROUP BY LastName
HAVING COUNT(orders.OrderID) >10
ORDER   BY LastName DESC;

SELECT SupplierName
from suppliers
WHERE EXISTS(
    SELECT ProductName
    from products
    WHERE products.SupplierID = suppliers.SupplierID
    AND Price <20
);

SELECT SupplierName,
EXISTS(
    SELECT 1 from products
    WHERE products.SupplierID = suppliers.SupplierID
    AND Price = 22
) AS ProductoA22
from suppliers;


SELECT OrderID, Quantity,
    CASE 
        WHEN Quantity >30 THEN 'La cantidad es mayor a 30'
        WHEN Quantity =30 THEN 'La cantidad  30'
        ELSE 'La cantidad es menor a 30' 
    END AS TextoCantidades
from order_details;

SELECT CustomerName,City,Country
from customers
ORDER BY
    CASE
        WHEN City is NULL THEN Country
        ELSE City
    END;


CREATE TABLE departments(
    id INT AUTO_INCREMENT PRIMARY KEY,
    name varchar(100) NOT NULL
);

CREATE TABLE employees(
    id  INT AUTO_INCREMENT PRIMARY KEY,
    first_name varchar(27) NOT NULL,
    last_name varchar(40) NOT NULL,
    email varchar(100) UNIQUE,
    hire_date DATE,
    salary DECIMAL(10,2),
    department_id INT,
    FOREIGN KEY (department_id) REFERENCES departments(id)
);





-- CREATE TABLE departments(
--     id INT AUTO_INCREMENT PRIMARY KEY,
--     name varchar(100) NOT NULL
-- );

-- CREATE TABLE emoloyees(
--     id INT AUTO_INCREMENT PRIMARY KEY,
--     name varchar 100,
--     department_id int,
--     FOREIGN KEY (department_id) REFERENCES department_id
-- )


CREATE TABLE nueva_Tabla AS 
SELECT * FROM tabla_existente;
-- este comando copia la estructura de la tabla
-- pero no copia ningun constrint(primary key, not null, aut increment,etc.)

CREATE TABLE nueva_Tabla AS
SELECT * FROM tabla_existente WHERE 1=0;


SHOW CREATE TABLE nombr_tabla;
-- 

INSERT INTO tabla_existente2 SELECT * FROM tabla_existente1;


CREATE TABLE products2 SELECT ProductID, ProductName, Unit, Price FROM products WHERE 1=0;

INSERT INTO products2
SELECT ProductID, ProductName, Unit, Price
FROM products;

ALTER TABLE nombre_tabla ACTION

ALTER TABLE products2 RENAME to ProductsTwo;



ALTER TABLE ProductsTwo ADD PRIMARY KEY (id);

ALTER TABLE ProductsTwo ADD COLUMN brand varchar (id);


ALTER TABLE ProductsTwo ADD COLUMN ExpiringDate DATE;



ALTER TABLE ProductsTwo CHANGE COLUMN ExpiringDate Caducidad DATE;

ALTER TABLE ProductsTwo ADD COLUMN CategoryID int;



ALTER TABLE ProductsTwo
ADD constraint CategoryID
FOREIGN KEY (CategoryID) REFERENCES categories(CategoryID);


ALTER TABLE ProductsTwo MODIFY COLUMN Price DECIMAL(5,2) NOT NULL;



SELECT 
employee_id,employee_name,salary,hire_date,
COALESCE(department, "Desconocido") as department
from employees;

CREATE TABLE limpia AS
SELECT 
employee_id,employee_name,salary,hire_date,
COALESCE(department, "Desconocido") as department
from employees;


SELECT 
employee_id,employee_name,salary,hire_date,department
from limpia WHERE salary >0 or salary < 100000;


CONCAT(
    UPPER(SUBSTRING(employee_name,1,1)) -- Primera letra de la primera cadena
    LOWER(SUBSTRING(employee_name,2,LOCATE(" ", employee_name-2))) -- Halla el espacio y se regresa dos caracteries
    -- tipo Alan(1) (2) Merlan(3), Por tanto selecciones  le *2
    UPPER(SUBSTRING(employee_name, LOCATE(" ",employee_name+1),1)),
    LOWER(SUBSTRING(employee_name,LOCATE(" ".employee_name+2)))
    )
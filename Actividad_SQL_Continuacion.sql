--PARTE 01

PRAGMA foreign_keys = ON;

-- Tabla: Productos
CREATE TABLE IF NOT EXISTS Productos (
    id_producto INTEGER NOT NULL,
    nombre      TEXT    NOT NULL,
    precio      REAL    NOT NULL,
    CONSTRAINT PK_Productos PRIMARY KEY (id_producto),
    CONSTRAINT CHK_precio   CHECK (precio > 0)
);

-- Tabla: Ventas
CREATE TABLE IF NOT EXISTS Ventas (
    id_venta    INTEGER NOT NULL,
    id_producto INTEGER NOT NULL,
    cantidad    INTEGER NOT NULL,
    fecha       TEXT    NOT NULL DEFAULT (DATE('now')),
    CONSTRAINT PK_Ventas PRIMARY KEY (id_venta),
    CONSTRAINT FK_Ventas_Productos
        FOREIGN KEY (id_producto) REFERENCES Productos(id_producto),
    CONSTRAINT CHK_cantidad CHECK (cantidad > 0)
);

-- PARTE 02
PRAGMA foreign_keys = ON;

-- Insertar datos en Productos
INSERT INTO Productos (id_producto, nombre, precio) VALUES
(1, 'Laptop',    1200.5),
(2, 'Mouse',       25.75),
(3, 'Teclado',     45.0),
(4, 'Monitor',    300.0),
(5, 'Impresora',  150.0);

-- Insertar datos en Ventas
INSERT INTO Ventas (id_venta, id_producto, cantidad, fecha) VALUES
(1,  5, 1, '2025-02-01'),
(2,  2, 3, '2025-01-28'),
(3,  3, 4, '2025-02-06'),
(4,  4, 3, '2025-01-24'),
(5,  4, 4, '2025-02-11'),
(6,  2, 5, '2025-02-11'),
(7,  3, 4, '2025-02-15'),
(8,  3, 4, '2025-01-25'),
(9,  2, 2, '2025-02-03'),
(10, 1, 3, '2025-02-03');

--PARTE 03
PRAGMA foreign_keys = ON;
-- 1 Obtener el total de todas las ventas q se registraron
SELECT COUNT(*) AS total_ventas
FROM Ventas;
-- 2 Calcular el total de productos vendidos
SELECT SUM(cantidad) AS cantidad_total_vendida
FROM Ventas;
-- 3 Determina el precio maximo, minimo y el promedio de los productos
SELECT
    MAX(precio) AS precio_maximo,
    MIN(precio) AS precio_minimo,
    AVG(precio) AS precio_promedio
FROM Productos;
-- 4 Cantidad total de productos vendidos por cada "clase" o "vendedor" por asi decirlo
--    (agrupado por id_producto)
SELECT
    id_producto,
    SUM(cantidad) AS total_vendido
FROM Ventas
GROUP BY id_producto
ORDER BY id_producto;

PRAGMA foreign_keys = ON;
-- 1 sacar el total de ventas registradas
SELECT COUNT(*) AS total_ventas
FROM Ventas;
-- 2 calcular  cantidad total de productos vendidos
SELECT SUM(cantidad) AS cantidad_total_vendida
FROM Ventas;
-- 3 determina el precio máximo  mínimo y promedio de los productos denuevo
SELECT
    MAX(precio) AS precio_maximo,
    MIN(precio) AS precio_minimo,
    AVG(precio) AS precio_promedio
FROM Productos;
-- 4 Obtener la cantidad total de productos vendidos para cada categoria denuevo
--    (agrupado por id_producto)
SELECT
    id_producto,
    SUM(cantidad) AS total_vendido
FROM Ventas
GROUP BY id_producto
ORDER BY id_producto;

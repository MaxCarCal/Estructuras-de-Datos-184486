
--  ACTIVIDAD SQL — Sistema de Renta de Autos
--  Archivo: ACT_SQL_CarmonaMaximiliano.sql
--  BASE DE DATOS: SQLite


-- SQLite no tiene CREATE DATABASE ni USE.
-- Todo se trabaja dentro de un único archivo .db
-- Activar integridad referencial (obligatorio en SQLite):
PRAGMA foreign_keys = ON;



-- PARTE A — DDL: Crear tablas


-- Limpiar tablas si ya existen (para poder re-ejecutar el script)
DROP TABLE IF EXISTS ReservaAuto;
DROP TABLE IF EXISTS Reserva;
DROP TABLE IF EXISTS Auto;
DROP TABLE IF EXISTS Cliente;

-- 
-- Tabla: Cliente
-- 
CREATE TABLE Cliente (
    id_cliente   INTEGER     PRIMARY KEY AUTOINCREMENT,
    nombre       TEXT        NOT NULL,
    direccion    TEXT        NOT NULL,
    telefono     TEXT        NOT NULL
);

-- 
-- Tabla: Auto
-- 
CREATE TABLE Auto (
    matricula    TEXT        PRIMARY KEY,
    marca        TEXT        NOT NULL,
    modelo       TEXT        NOT NULL,
    color        TEXT        NOT NULL,
    disponible   INTEGER     NOT NULL DEFAULT 1  -- 1=Sí, 0=No
);

-- 
-- Tabla: Reserva
-- 
CREATE TABLE Reserva (
    id_reserva   INTEGER     PRIMARY KEY AUTOINCREMENT,
    id_cliente   INTEGER     NOT NULL,
    fecha_inicio TEXT        NOT NULL,  -- formato 'YYYY-MM-DD'
    fecha_fin    TEXT        NOT NULL,
    precio       REAL        NOT NULL,
    combustible  REAL        NOT NULL,
    devuelto     INTEGER     NOT NULL DEFAULT 0,  -- 0=No, 1=Sí
    CONSTRAINT fk_reserva_cliente
        FOREIGN KEY (id_cliente) REFERENCES Cliente(id_cliente)
        ON UPDATE CASCADE
        ON DELETE RESTRICT,
    CONSTRAINT chk_fechas CHECK (fecha_fin >= fecha_inicio),
    CONSTRAINT chk_precio  CHECK (precio >= 0)
);

-- 
-- Tabla puente: ReservaAuto (PK compuesta)
-- 
CREATE TABLE ReservaAuto (
    id_reserva   INTEGER     NOT NULL,
    matricula    TEXT        NOT NULL,
    PRIMARY KEY (id_reserva, matricula),
    CONSTRAINT fk_ra_reserva
        FOREIGN KEY (id_reserva) REFERENCES Reserva(id_reserva)
        ON UPDATE CASCADE
        ON DELETE RESTRICT,
    CONSTRAINT fk_ra_auto
        FOREIGN KEY (matricula)  REFERENCES Auto(matricula)
        ON UPDATE CASCADE
        ON DELETE RESTRICT
);

-- 
-- Verificación DDL
-- (equivalente a SHOW TABLES pero es DESCRIBE en SQLite)

SELECT name FROM sqlite_master WHERE type='table' ORDER BY name;

PRAGMA table_info(Cliente);
PRAGMA table_info(Auto);
PRAGMA table_info(Reserva);
PRAGMA table_info(ReservaAuto);


-- 
-- DML: Insertar datos
-- 

-- Clientes
INSERT INTO Cliente (nombre, direccion, telefono) VALUES
    ('Ana García López',      'Calle Hidalgo 12, Puebla',    '2221001001'),
    ('Carlos Ramírez Vega',   'Av. Juárez 45, Cholula',      '2221002002'),
    ('María Torres Solis',    'Blvd. Norte 88, San Andrés',  '2221003003'),
    ('Luis Pérez Mendoza',    'Calle 5 de Mayo 3, Puebla',   '2221004004'),
    ('Elena Castillo Ruiz',   'Priv. Las Flores 9, Atlixco', '2221005005');

-- Autos
INSERT INTO Auto (matricula, marca, modelo, color, disponible) VALUES
    ('PUE-001', 'Toyota',     'Corolla', 'Blanco', 1),
    ('PUE-002', 'Nissan',     'Versa',   'Gris',   1),
    ('PUE-003', 'Volkswagen', 'Jetta',   'Negro',  1),
    ('PUE-004', 'Chevrolet',  'Aveo',    'Rojo',   1),
    ('PUE-005', 'Honda',      'Civic',   'Azul',   0);

-- Reservas
INSERT INTO Reserva (id_cliente, fecha_inicio, fecha_fin, precio, combustible, devuelto) VALUES
    (1, '2025-06-01', '2025-06-05', 2000.00, 40.00, 1),
    (2, '2025-06-03', '2025-06-07', 2400.00, 35.50, 0),
    (3, '2025-06-10', '2025-06-12', 1200.00, 50.00, 1),
    (4, '2025-06-15', '2025-06-20', 3000.00, 20.00, 0),
    (1, '2025-07-01', '2025-07-03', 1400.00, 45.00, 0);

-- Tabla puente
INSERT INTO ReservaAuto (id_reserva, matricula) VALUES
    (1, 'PUE-001'),
    (2, 'PUE-002'),
    (3, 'PUE-003'),
    (4, 'PUE-004'),
    (5, 'PUE-001');

-- -----------------------------------------------
-- Verificación DML
-- -----------------------------------------------
SELECT * FROM Cliente;
SELECT * FROM Auto;
SELECT * FROM Reserva;
SELECT * FROM ReservaAuto;



--  DQL: Consultas Q1–Q5


-- Q1: Clientes con al menos una reserva pendiente de devolución
-- Resultado esperado: 3 filas (Carlos, Luis, Ana)
SELECT DISTINCT
    c.id_cliente,
    c.nombre,
    c.telefono
FROM Cliente c
JOIN Reserva r ON c.id_cliente = r.id_cliente
WHERE r.devuelto = 0;

-- Q2: Total facturado por cliente
-- Resultado esperado: 4 filas ordenadas por total_pagado DESC
SELECT
    c.nombre,
    COUNT(r.id_reserva)  AS num_reservas,
    SUM(r.precio)        AS total_pagado
FROM Cliente c
JOIN Reserva r ON c.id_cliente = r.id_cliente
GROUP BY c.id_cliente, c.nombre
ORDER BY total_pagado DESC;

-- Q3: Autos reservados con su fecha de reserva más reciente
-- Resultado esperado: 4 filas
SELECT
    a.matricula,
    a.marca,
    a.modelo,
    MAX(r.fecha_inicio) AS ultima_reserva
FROM Auto a
JOIN ReservaAuto ra ON a.matricula  = ra.matricula
JOIN Reserva     r  ON ra.id_reserva = r.id_reserva
GROUP BY a.matricula, a.marca, a.modelo;

-- Q4: Reservas sin devolver con duración mayor a 3 días
-- SQLite usa julianday() en lugar de DATEDIFF()
-- Resultado esperado: 2 filas (Carlos 4 días, Luis 5 días)
SELECT
    r.id_reserva,
    c.nombre        AS cliente,
    r.fecha_inicio,
    r.fecha_fin,
    CAST(julianday(r.fecha_fin) - julianday(r.fecha_inicio) AS INTEGER) AS dias,
    r.precio
FROM Reserva r
JOIN Cliente c ON r.id_cliente = c.id_cliente
WHERE r.devuelto = 0
  AND (julianday(r.fecha_fin) - julianday(r.fecha_inicio)) > 3;

-- Q5: Autos que nunca han sido reservados
-- Resultado esperado: 1 fila (PUE-005 Honda Civic)
SELECT
    a.matricula,
    a.marca,
    a.modelo,
    a.color,
    a.disponible
FROM Auto a
LEFT JOIN ReservaAuto ra ON a.matricula = ra.matricula
WHERE ra.matricula IS NULL;



-- PARTE D — UPDATE / DELETE / TRANSACCIONES (DML + TCL)



-- UPDATE: Marcar como devuelta la reserva 2

-- ANTES:
SELECT id_reserva, devuelto FROM Reserva WHERE id_reserva = 2;

UPDATE Reserva SET devuelto = 1 WHERE id_reserva = 2;

-- DESPUÉS:
SELECT id_reserva, devuelto FROM Reserva WHERE id_reserva = 2;



-- DELETE: orden correcto respetando FK
-- (borrar directo en Cliente fallaría pq Reserva)

DELETE FROM ReservaAuto WHERE id_reserva = 2;
DELETE FROM Reserva     WHERE id_reserva = 2;
DELETE FROM Cliente     WHERE id_cliente = 2;

-- Verificar eliminación:
SELECT * FROM Cliente     WHERE id_cliente = 2;   -- 0 filas
SELECT * FROM Reserva     WHERE id_cliente = 2;   -- 0 filas
SELECT * FROM ReservaAuto WHERE id_reserva = 2;   -- 0 filas



-- TRANSACCIÓN 1: ROLLBACK (revertir e cambio)
-- 
-- ANTES:
SELECT id_reserva, precio FROM Reserva WHERE id_reserva = 3;

BEGIN TRANSACTION;
    UPDATE Reserva SET precio = 9999.99 WHERE id_reserva = 3;
    -- Cambio temporal visible dentro de la transacción:
    SELECT id_reserva, precio FROM Reserva WHERE id_reserva = 3;
ROLLBACK;

-- DESPUÉS del ROLLBACK (precio vuelve a 1200.00):
SELECT id_reserva, precio FROM Reserva WHERE id_reserva = 3;


-- TRANSACCIÓN 2: COMMIT (guardar el cambio)

-- ANTES:
SELECT matricula, disponible FROM Auto WHERE matricula = 'PUE-005';

BEGIN TRANSACTION;
    UPDATE Auto SET disponible = 1 WHERE matricula = 'PUE-005';
    SELECT matricula, disponible FROM Auto WHERE matricula = 'PUE-005';
COMMIT;

-- DESPUÉS del COMMIT (disponible = 1 permanece):
SELECT matricula, disponible FROM Auto WHERE matricula = 'PUE-005';



-- FIN DEL ARCHIVO

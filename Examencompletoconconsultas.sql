--184486 MAXIMILIANO CAMRMONA

PRAGMA foreign_keys = ON;

DROP TABLE IF EXISTS Pago;
DROP TABLE IF EXISTS Detalle_Cita_Tratamiento;
DROP TABLE IF EXISTS Cita;
DROP TABLE IF EXISTS Tratamiento;
DROP TABLE IF EXISTS Consultorio;
DROP TABLE IF EXISTS Odontologo;
DROP TABLE IF EXISTS Paciente;

CREATE TABLE Paciente (
    id_paciente      TEXT PRIMARY KEY,
    nombre_completo  TEXT NOT NULL,
    fecha_nacimiento TEXT NOT NULL,
    telefono         TEXT,
    correo           TEXT,
    direccion        TEXT
);

CREATE TABLE Odontologo (
    id_odontologo TEXT PRIMARY KEY,
    nombre        TEXT NOT NULL,
    especialidad  TEXT NOT NULL,
    telefono      TEXT,
    correo        TEXT
);

CREATE TABLE Consultorio (
    id_consultorio TEXT PRIMARY KEY,
    numero         TEXT NOT NULL,
    piso           INTEGER NOT NULL
);

CREATE TABLE Tratamiento (
    id_tratamiento TEXT PRIMARY KEY,
    nombre         TEXT NOT NULL,
    descripcion    TEXT,
    costo_base     REAL NOT NULL CHECK (costo_base >= 0)
);

CREATE TABLE Cita (
    id_cita        TEXT PRIMARY KEY,
    fecha          TEXT NOT NULL,
    hora           TEXT NOT NULL,
    motivo         TEXT,
    estado         TEXT NOT NULL CHECK (estado IN ('Completada','Programada','Cancelada','Pendiente')),
    id_paciente    TEXT NOT NULL,
    id_odontologo  TEXT NOT NULL,
    id_consultorio TEXT NOT NULL,
    FOREIGN KEY (id_paciente)    REFERENCES Paciente(id_paciente),
    FOREIGN KEY (id_odontologo)  REFERENCES Odontologo(id_odontologo),
    FOREIGN KEY (id_consultorio) REFERENCES Consultorio(id_consultorio)
);

CREATE TABLE Detalle_Cita_Tratamiento (
    id_cita        TEXT NOT NULL,
    id_tratamiento TEXT NOT NULL,
    observaciones  TEXT,
    costo_aplicado REAL NOT NULL CHECK (costo_aplicado >= 0),
    PRIMARY KEY (id_cita, id_tratamiento),
    FOREIGN KEY (id_cita)        REFERENCES Cita(id_cita),
    FOREIGN KEY (id_tratamiento) REFERENCES Tratamiento(id_tratamiento)
);

CREATE TABLE Pago (
    id_pago     TEXT PRIMARY KEY,
    fecha_pago  TEXT NOT NULL,
    monto       REAL NOT NULL CHECK (monto > 0),
    metodo_pago TEXT NOT NULL CHECK (metodo_pago IN ('Tarjeta','Efectivo','Transferencia','Pendiente')),
    estado      TEXT NOT NULL CHECK (estado IN ('Pagado','Pendiente','Anulado')),
    id_cita     TEXT NOT NULL UNIQUE,
    FOREIGN KEY (id_cita) REFERENCES Cita(id_cita)
);

CREATE INDEX idx_cita_paciente   ON Cita(id_paciente);
CREATE INDEX idx_cita_odontologo ON Cita(id_odontologo);
CREATE INDEX idx_cita_fecha      ON Cita(fecha);

INSERT INTO Paciente VALUES
    ('P001','Ana López García',       '2002-03-14','2223456789','ana.lopez@correo.com',       'Cholula, Puebla'),
    ('P002','Carlos Martínez Ruiz',   '2001-08-22','2224567890','carlos.martinez@correo.com',  'Puebla, Puebla'),
    ('P003','Diana Hernández Soto',   '2003-01-10','2225678901','diana.hernandez@correo.com',  'San Andrés Cholula, Puebla'),
    ('P004','José Ramírez Torres',    '2000-11-05','2226789012','jose.ramirez@correo.com',     'Atlixco, Puebla'),
    ('P005','Mariana Pérez Castillo', '2002-06-30','2227890123','mariana.perez@correo.com',    'San Pedro Cholula, Puebla');

INSERT INTO Odontologo VALUES
    ('O001','Dra. Laura Sánchez',  'Ortodoncia',          '2221112233','laura.sanchez@clinica.com'),
    ('O002','Dr. Miguel Torres',   'Endodoncia',          '2221113344','miguel.torres@clinica.com'),
    ('O003','Dra. Fernanda Gómez', 'Odontología general', '2221114455','fernanda.gomez@clinica.com');

INSERT INTO Consultorio VALUES
    ('C001','101',1),
    ('C002','102',1),
    ('C003','201',2);

INSERT INTO Tratamiento VALUES
    ('T001','Limpieza dental',       'Eliminación de sarro y placa',             500.00),
    ('T002','Resina',                'Restauración dental con material resina',  850.00),
    ('T003','Extracción',            'Remoción de una pieza dental',            1200.00),
    ('T004','Endodoncia',            'Tratamiento de conducto',                 2500.00),
    ('T005','Ortodoncia evaluación', 'Revisión y diagnóstico de ortodoncia',     700.00);

INSERT INTO Cita VALUES
    ('CT001','2026-04-02','09:00','Dolor molar',         'Completada','P001','O002','C001'),
    ('CT002','2026-04-02','10:00','Limpieza general',    'Completada','P002','O003','C002'),
    ('CT003','2026-04-03','11:30','Revisión de brackets','Completada','P003','O001','C003'),
    ('CT004','2026-04-03','13:00','Caries en premolar',  'Completada','P004','O003','C001'),
    ('CT005','2026-04-04','09:30','Extracción dental',   'Completada','P005','O002','C002'),
    ('CT006','2026-04-04','12:00','Dolor e infección',   'Completada','P002','O002','C001'),
    ('CT007','2026-04-05','10:30','Valoración general',  'Programada','P001','O003','C003'),
    ('CT008','2026-04-05','12:30','Ajuste de ortodoncia','Programada','P003','O001','C003');

INSERT INTO Detalle_Cita_Tratamiento VALUES
    ('CT001','T004','Se realizó tratamiento de conducto', 2500.00),
    ('CT002','T001','Limpieza completa sin complicaciones', 500.00),
    ('CT003','T005','Evaluación y ajuste inicial',          700.00),
    ('CT004','T002','Aplicación de resina en premolar',     850.00),
    ('CT005','T003','Extracción de tercer molar',          1200.00),
    ('CT006','T004','Endodoncia por infección avanzada',   2500.00),
    ('CT007','T001','Limpieza sugerida en valoración',      500.00),
    ('CT008','T005','Revisión y ajuste de ortodoncia',      700.00);

INSERT INTO Pago VALUES
    ('PG001','2026-04-02',2500.00,'Tarjeta',      'Pagado',   'CT001'),
    ('PG002','2026-04-02', 500.00,'Efectivo',     'Pagado',   'CT002'),
    ('PG003','2026-04-03', 700.00,'Tarjeta',      'Pagado',   'CT003'),
    ('PG004','2026-04-03', 850.00,'Transferencia','Pagado',   'CT004'),
    ('PG005','2026-04-04',1200.00,'Efectivo',     'Pagado',   'CT005'),
    ('PG006','2026-04-04',2500.00,'Tarjeta',      'Pagado',   'CT006'),
    ('PG007','2026-04-05', 500.00,'Pendiente',    'Pendiente','CT007'),
    ('PG008','2026-04-05', 700.00,'Pendiente',    'Pendiente','CT008');
	
--1 consultorios por piso	
SELECT piso, COUNT (*) AS num_consultorios 
FROM Consultorio
GROUP BY piso;

--2 costo mas alto y bajo de tratamiento 
SELECT MAX (costo_base) AS costo_mas_alto, MIN (costo_base) AS costo_mas_bajo
FROM Tratamiento	

--3 cuantas citas hay en cada estado
SELECT estado, COUNT(*) AS total_citas
FROM Cita
GROUP BY estado;

--4 cuantas citas tiene cada paciente
SELECT id_paciente, COUNT (*) AS total_citas
FROM Cita
GROUP BY id_paciente;

--5 cuantas citas atiende cada Odontologo
SELECT id_odontologo, COUNT (*) AS total_citas
FROM Cita
GROUP BY id_odontologo;

--6 cuantas citas hay x motivo
SELECT motivo, COUNT (*) AS total_citas	
FROM Cita
GROUP BY motivo;

--7 + total de todos los pagos 
SELECT SUM(monto) AS total_general_pagos
FROM Pago;

--8 total acumulado x metodo de Pago
SELECT metodo_pago, SUM(monto) AS total_acumulado
FROM Pago
GROUP BY metodo_pago;

--9 grupos de pagos x estado con suma mayor a 1000
SELECT estado, SUM(monto) AS total_por_estad0
FROM Pago
GROUP BY estado
HAVING SUM(monto) > 1000;

--10 costo promedio x tratamietno
SELECT id_tratamiento, AVG(costo_aplicado) AS costo_promedio_aplicado
FROM Detalle_Cita_Tratamiento
GROUP BY id_tratamiento;

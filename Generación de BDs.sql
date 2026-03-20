-- Tabla: Departamento
CREATE TABLE Departamento (
    Dep_Numero        INT           PRIMARY KEY,
    Dep_Nombre        VARCHAR(100)  NOT NULL,
    Dep_Localizacion  VARCHAR(100)
);
 
-- Tabla: Facultad
CREATE TABLE Facultad (
    Fac_Numero           INT            PRIMARY KEY,
    Fac_Nombre           VARCHAR(100)   NOT NULL,
    Fac_Direccion        VARCHAR(150),
    Fac_Salario          DECIMAL(12, 2),
    Fac_SalarioAcumulado DECIMAL(12, 2),
    Dep_Numero           INT,
    Fac_Grado            VARCHAR(10),
    Fac_Especialidad     VARCHAR(100),
    Fac_Rango            VARCHAR(10),
    Fac_Dependientes     BOOLEAN        DEFAULT FALSE,
    CONSTRAINT fk_facultad_departamento
        FOREIGN KEY (Dep_Numero) REFERENCES Departamento(Dep_Numero)
);
 
-- Tabla: Historial
CREATE TABLE Historial (
    Fac_Numero      INT          NOT NULL,
    Hist_id         INT          NOT NULL,
    Hist_Rango      VARCHAR(10)  NOT NULL,
    Hist_fechaRango DATE         NOT NULL,
    PRIMARY KEY (Fac_Numero, Hist_id),
    CONSTRAINT fk_historial_facultad
        FOREIGN KEY (Fac_Numero) REFERENCES Facultad(Fac_Numero)
);
 
-- Tabla: Conferencias
CREATE TABLE Conferencias (
    Fac_Numero        INT           NOT NULL,
    Conf_id           INT           NOT NULL,
    Conf_Titulo       VARCHAR(200)  NOT NULL,
    Conf_NumeroVeces  INT           DEFAULT 0,
    Conf_UltimaVez    DATE,
    PRIMARY KEY (Fac_Numero, Conf_id),
    CONSTRAINT fk_conferencias_facultad
        FOREIGN KEY (Fac_Numero) REFERENCES Facultad(Fac_Numero)
);
 
-- Datos de prueba
 
-- Departamento
INSERT INTO Departamento (Dep_Numero, Dep_Nombre, Dep_Localizacion) VALUES
(2, 'Física',                  'Edificio 100'),
(5, 'Ciencias Computacionales','Edificio 100'),
(7, 'Geología',                'Edificio 200');
 
-- Facultad
INSERT INTO Facultad (Fac_Numero, Fac_Nombre, Fac_Direccion, Fac_Salario, Fac_SalarioAcumulado,
                      Dep_Numero, Fac_Grado, Fac_Especialidad, Fac_Rango, Fac_Dependientes) VALUES
(119, 'Torres',    'La Paz',      700100.00,  8900800.00, 5, 'MS',  'Matemáticas', 'Asst', FALSE),
(120, 'José Díaz', 'Col. Centro', 690000.00,  7890000.00, 5, 'MS',  'Matemáticas', 'Asso', TRUE),
(201, 'Alz Heimer','Juárez',      550500.00,  3240600.00, 7, 'MS',  'Geología',    'Full', FALSE),
(204, 'Park Ison', 'Col. Centro', 270000.00,   890000.00, 2, 'PhD', 'Física',      'Asst', FALSE);
 
-- Historial
INSERT INTO Historial (Fac_Numero, Hist_id, Hist_Rango, Hist_fechaRango) VALUES
(119, 1, 'Asst', '1990-08-01'),
(120, 1, 'Asso', '1995-01-01'),
(120, 2, 'Full', '2005-08-01'),
(204, 1, 'Asst', '2010-01-07');
 
-- Conferencias
INSERT INTO Conferencias (Fac_Numero, Conf_id, Conf_Titulo, Conf_NumeroVeces, Conf_UltimaVez) VALUES
(120, 1, 'Programación Móvil', 3, '2015-12-12'),
(119, 2, 'Bases de Datos',     5, '2020-08-06'),
(119, 3, 'Usando Access',      1, '2005-02-07');

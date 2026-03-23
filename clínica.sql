-- ============================================================
--  BASE DE DATOS: Clínica Dental
--  Motor: SQLite
--  Basado en diagrama E-R
-- ============================================================

PRAGMA foreign_keys = ON;

-- ------------------------------------------------------------
-- 1. PACIENTE
-- ------------------------------------------------------------
CREATE TABLE IF NOT EXISTS Paciente (
    id_paciente      INTEGER PRIMARY KEY AUTOINCREMENT,
    nombre_completo  TEXT    NOT NULL,
    fecha_nacimiento TEXT    NOT NULL,   -- formato ISO: YYYY-MM-DD
    telefono         TEXT,
    correo           TEXT,
    direccion        TEXT
);

-- ------------------------------------------------------------
-- 2. ODONTOLOGO
-- ------------------------------------------------------------
CREATE TABLE IF NOT EXISTS Odontologo (
    id_odontologo INTEGER PRIMARY KEY AUTOINCREMENT,
    nombre        TEXT NOT NULL,
    especialidad  TEXT NOT NULL,
    telefono      TEXT,
    correo        TEXT
);

-- ------------------------------------------------------------
-- 3. CONSULTORIO
-- ------------------------------------------------------------
CREATE TABLE IF NOT EXISTS Consultorio (
    id_consultorio INTEGER PRIMARY KEY AUTOINCREMENT,
    numero         TEXT NOT NULL,
    piso           INTEGER NOT NULL
);

-- ------------------------------------------------------------
-- 4. CITA
-- ------------------------------------------------------------
CREATE TABLE IF NOT EXISTS Cita (
    id_cita        INTEGER PRIMARY KEY AUTOINCREMENT,
    fecha          TEXT    NOT NULL,   -- formato ISO: YYYY-MM-DD
    hora           TEXT    NOT NULL,   -- formato: HH:MM
    motivo         TEXT,
    estado         TEXT    NOT NULL DEFAULT 'pendiente'
                           CHECK (estado IN ('pendiente', 'confirmada', 'completada', 'cancelada')),
    id_paciente    INTEGER NOT NULL,
    id_odontologo  INTEGER NOT NULL,
    id_consultorio INTEGER NOT NULL,

    FOREIGN KEY (id_paciente)    REFERENCES Paciente(id_paciente),
    FOREIGN KEY (id_odontologo)  REFERENCES Odontologo(id_odontologo),
    FOREIGN KEY (id_consultorio) REFERENCES Consultorio(id_consultorio)
);

-- ------------------------------------------------------------
-- 5. TRATAMIENTO
-- ------------------------------------------------------------
CREATE TABLE IF NOT EXISTS Tratamiento (
    id_tratamiento INTEGER PRIMARY KEY AUTOINCREMENT,
    nombre         TEXT    NOT NULL,
    descripcion    TEXT,
    costo_base     REAL    NOT NULL CHECK (costo_base >= 0)
);

-- ------------------------------------------------------------
-- 6. DETALLE_CITA_TRATAMIENTO  (tabla intermedia N:M)
-- ------------------------------------------------------------
CREATE TABLE IF NOT EXISTS Detalle_Cita_Tratamiento (
    id_cita        INTEGER NOT NULL,
    id_tratamiento INTEGER NOT NULL,
    observaciones  TEXT,
    costo_aplicado REAL    NOT NULL CHECK (costo_aplicado >= 0),

    PRIMARY KEY (id_cita, id_tratamiento),
    FOREIGN KEY (id_cita)        REFERENCES Cita(id_cita),
    FOREIGN KEY (id_tratamiento) REFERENCES Tratamiento(id_tratamiento)
);

-- ------------------------------------------------------------
-- 7. PAGO
-- ------------------------------------------------------------
CREATE TABLE IF NOT EXISTS Pago (
    id_pago      INTEGER PRIMARY KEY AUTOINCREMENT,
    fecha_pago   TEXT    NOT NULL,   -- formato ISO: YYYY-MM-DD
    monto        REAL    NOT NULL CHECK (monto > 0),
    metodo_pago  TEXT    NOT NULL
                         CHECK (metodo_pago IN ('efectivo', 'tarjeta', 'transferencia', 'otro')),
    estado       TEXT    NOT NULL DEFAULT 'pendiente'
                         CHECK (estado IN ('pendiente', 'pagado', 'anulado')),
    id_cita      INTEGER NOT NULL UNIQUE,   -- una cita → un pago

    FOREIGN KEY (id_cita) REFERENCES Cita(id_cita)
);

-- ============================================================
--  ÍNDICES para mejorar búsquedas frecuentes
-- ============================================================
CREATE INDEX IF NOT EXISTS idx_cita_paciente   ON Cita(id_paciente);
CREATE INDEX IF NOT EXISTS idx_cita_odontologo ON Cita(id_odontologo);
CREATE INDEX IF NOT EXISTS idx_cita_fecha      ON Cita(fecha);
CREATE INDEX IF NOT EXISTS idx_pago_cita       ON Pago(id_cita);

-- ============================================================
--  DATOS DE EJEMPLO
-- ============================================================

INSERT INTO Paciente (nombre_completo, fecha_nacimiento, telefono, correo, direccion)
VALUES
    ('Ana García López',    '1990-05-14', '555-1001', 'ana@email.com',    'Calle 10 #23'),
    ('Carlos Méndez Ruiz',  '1985-11-30', '555-1002', 'carlos@email.com', 'Av. Central 45'),
    ('Lucía Torres Vega',   '2000-03-22', '555-1003', 'lucia@email.com',  'Blvd. Norte 8');

INSERT INTO Odontologo (nombre, especialidad, telefono, correo)
VALUES
    ('Dr. Roberto Solis',   'Ortodoncia',      '555-2001', 'rsolis@clinica.com'),
    ('Dra. Patricia Reyes', 'Endodoncia',      '555-2002', 'preyes@clinica.com'),
    ('Dr. Manuel Castro',   'Odontología General', '555-2003', 'mcastro@clinica.com');

INSERT INTO Consultorio (numero, piso)
VALUES
    ('101', 1),
    ('202', 2),
    ('305', 3);

INSERT INTO Tratamiento (nombre, descripcion, costo_base)
VALUES
    ('Limpieza dental',   'Profilaxis completa con ultrasonido',  350.00),
    ('Extracción simple', 'Extracción de pieza sin complicación', 500.00),
    ('Resina',            'Restauración con resina compuesta',    600.00),
    ('Blanqueamiento',    'Blanqueamiento dental con luz LED',    1200.00);

INSERT INTO Cita (fecha, hora, motivo, estado, id_paciente, id_odontologo, id_consultorio)
VALUES
    ('2026-03-25', '09:00', 'Revisión general',  'confirmada', 1, 3, 1),
    ('2026-03-26', '10:30', 'Dolor muela izq.',  'pendiente',  2, 2, 2),
    ('2026-03-27', '11:00', 'Control ortodoncia','confirmada', 3, 1, 3);

INSERT INTO Detalle_Cita_Tratamiento (id_cita, id_tratamiento, observaciones, costo_aplicado)
VALUES
    (1, 1, 'Primera limpieza del año',           350.00),
    (2, 2, 'Extracción muela del juicio',         500.00),
    (3, 1, 'Limpieza previa a ajuste de brackets',350.00),
    (3, 4, 'Blanqueamiento con descuento',        950.00);

INSERT INTO Pago (fecha_pago, monto, metodo_pago, estado, id_cita)
VALUES
    ('2026-03-25', 350.00, 'tarjeta',      'pagado',   1),
    ('2026-03-26', 500.00, 'efectivo',     'pendiente', 2),
    ('2026-03-27', 1300.00,'transferencia','pendiente', 3);

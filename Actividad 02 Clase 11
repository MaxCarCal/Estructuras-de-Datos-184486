

-- Tabla: Artistas
CREATE TABLE Artistas (
    A_ID    INTEGER PRIMARY KEY,
    Nombre  TEXT NOT NULL
);

INSERT INTO Artistas VALUES (1, 'AC DC');
INSERT INTO Artistas VALUES (2, 'Scorpions');
INSERT INTO Artistas VALUES (3, 'Pink Floyd');

-- Tabla: Productoras
CREATE TABLE Productoras (
    Pro_ID  INTEGER PRIMARY KEY,
    Nombre  TEXT NOT NULL
);

INSERT INTO Productoras VALUES (1, 'Sony Music');
INSERT INTO Productoras VALUES (2, 'Universal Music');
INSERT INTO Productoras VALUES (3, 'Warner Music G.');
INSERT INTO Productoras VALUES (4, 'Emi Records');

-- Tabla: CD
CREATE TABLE CD (
    Cd_ID       INTEGER PRIMARY KEY,
    Artista     INTEGER NOT NULL,
    Title       TEXT    NOT NULL,
    Price       REAL    NOT NULL,
    Year        INTEGER NOT NULL,
    Productora  INTEGER NOT NULL,
    FOREIGN KEY (Artista)    REFERENCES Artistas(A_ID),
    FOREIGN KEY (Productora) REFERENCES Productoras(Pro_ID)
);

INSERT INTO CD VALUES (1, 1, 'Back in Black',       15.99, 1980, 1);
INSERT INTO CD VALUES (2, 1, 'Highway to Hell',      17.54, 1979, 2);
INSERT INTO CD VALUES (3, 3, 'The Wall',             16.99, 1979, 4);
INSERT INTO CD VALUES (4, 3, 'The Division Bell',    17.00, 1994, 3);
INSERT INTO CD VALUES (5, 2, 'Love at firts sting',  17.24, 1984, 4);
INSERT INTO CD VALUES (6, 2, 'Lovedrive',            17.15, 1979, 1);

-- Tabla: Track
CREATE TABLE Track (
    Cd_ID   INTEGER NOT NULL,
    Num     INTEGER NOT NULL,
    Title   TEXT    NOT NULL,
    Time    INTEGER NOT NULL,
    A_ID    INTEGER NOT NULL,
    PRIMARY KEY (Cd_ID, Num),
    FOREIGN KEY (Cd_ID) REFERENCES CD(Cd_ID),
    FOREIGN KEY (A_ID)  REFERENCES Artistas(A_ID)
);

INSERT INTO Track VALUES (1,  1,  'Hells Bells',              312, 1);
INSERT INTO Track VALUES (1,  6,  'Back in Black',            255, 1);
INSERT INTO Track VALUES (2,  1,  'Highway to hell',          216, 1);
INSERT INTO Track VALUES (2,  3,  'Walk all over you',        310, 1);
INSERT INTO Track VALUES (3,  3,  'Another Brick in the wall',215, 3);
INSERT INTO Track VALUES (3,  6,  'Comfortably Numb',         334, 3);
INSERT INTO Track VALUES (3,  5,  'Mother',                   334, 3);
INSERT INTO Track VALUES (4,  11, 'High Hopes',               514, 3);
INSERT INTO Track VALUES (4,  7,  'A Great Day For Freedom',  257, 3);
INSERT INTO Track VALUES (5,  14, 'Still Loving You',         346, 2);
INSERT INTO Track VALUES (5,  2,  'Rock you like a Hurricane',312, 2);
INSERT INTO Track VALUES (6,  4,  'Holiday',                  355, 2);

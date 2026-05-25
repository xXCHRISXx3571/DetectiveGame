#ifndef NODO_H
#define NODO_H

class Pista;

class Nodo {

public:

    char contenido;
    bool descubierto;
    bool tienePista;
    bool tieneTestigo;

    Pista* pista;
    Nodo* arriba;
    Nodo* abajo;
    Nodo* izquierda;
    Nodo* derecha;

    Nodo();
};

#endif
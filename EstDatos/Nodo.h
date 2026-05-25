#ifndef NODO_H
#define NODO_H

class pista;

class Nodo {

public:

    char contenido;
    bool descubierto;
    bool tienePista;
    bool tieneTestigo;
    
    pista* pista;
    Nodo* arriba;
    Nodo* abajo;
    Nodo* izquierda;
    Nodo* derecha;

    Nodo();
};

#endif
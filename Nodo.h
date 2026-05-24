#ifndef NODO_H
#define NODO_H

class Nodo {

public:

    char contenido;

    Nodo* arriba;
    Nodo* abajo;
    Nodo* izquierda;
    Nodo* derecha;

    Nodo();
};

#endif
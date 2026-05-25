#ifndef PILAPISTAS_H
#define PILAPISTAS_H

#include "Pista.h"
#include <iostream>
#include <stack>
using namespace std;

class PilaPistas {
    private:
        stack<Pista> pila;

    public:
        void apilar(Pista p);
        Pista desapilar();
        Pista verTope();
        bool estaVacia();
        int tamano();
        void mostrarPila();
};

#endif
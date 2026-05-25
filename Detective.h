#ifndef DETECTIVE_H
#define DETECTIVE_H

#include "PilaPistas.h"
#include <string>
#include "Nodo.h"
using namespace std;

class Detective {
    public:
        string nombre;
        int puntuacion;
        Nodo* posicion;
        PilaPistas pilaDeEvidencias;

        Detective();
        Detective(string nombre, Nodo* posicion);

        void moverArriba();
        void moverAbajo();  
        void moverIzquierda();
        void moverDerecha();

        void recogerPista(Pista p);
        void usarPista();
        void verPistas();

        void sumarPunto();
        void mostrarPuntuacion();
};
 #endif
#ifndef TABLERO_H
#define TABLERO_H

#include "Detective.h"
#include "Nodo.h"
#include "Pista.h"

class Tablero {
private:
    Nodo* inicio;

    Nodo* escogerCasillaDisponible(bool soloOculta);
    Nodo* escogerCallejon();
    void construir();
    bool casillaDisponible(Nodo* nodo, bool soloOculta);

public:
    static const int FILAS = 9;
    static const int COLUMNAS = 9;

    Tablero();
    ~Tablero();

    Nodo* obtenerInicio();
    Nodo* obtenerPosicionInicial();

    void colocarCallejones();
    void colocarPistas();
    void colocarTestigos();

    void imprimir(Detective& detective);
    void eliminarCallejones(int cantidad);
    void teletransportar(Detective& detective);
    void resetearMapa();
    void recolocarPista(Pista pista);
};

#endif

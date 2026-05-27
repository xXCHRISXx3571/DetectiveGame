#include "Detective.h"
#include <iostream>
using namespace std;

Detective::Detective() {
    nombre = "Desconocido";
    puntuacion = 0;
    posicion = nullptr;
}

Detective::Detective(string nombre, Nodo* posicion) {
    this->nombre = nombre;
    this->puntuacion = 0;
    this->posicion = posicion;
}

void Detective::sumarPunto() {
    puntuacion++;
}

void Detective::mostrarPuntuacion() {
    cout << nombre << ", Tu puntaje actual es: " << puntuacion << endl;
}

void Detective::recogerPista(Pista p) {
    pilaDeEvidencias.apilar(p);
    cout << ">>> Recogiste una pista: " << p.getNombre() << " <<<" << endl;
}

void Detective::verPistas() {
    if (pilaDeEvidencias.estaVacia()) {
        cout << nombre << ", aun no tienes pistas." << endl;
        return;
    }
    cout << nombre << ", Mira las pistas que llevas:" << endl;
    pilaDeEvidencias.mostrarPila();
}

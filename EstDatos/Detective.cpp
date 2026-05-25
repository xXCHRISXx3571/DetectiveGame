#include "Detective.h"
#include <iostream>
#include <cstdlib>
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

void Detective::moverArriba() {
    if (posicion->arriba != nullptr && posicion->arriba->contenido != '|') {
        posicion = posicion->arriba;
        posicion->descubierto = true;
        if (posicion->contenido == 'o') posicion->contenido = ' ';
        sumarPunto();
    } else if (posicion->arriba != nullptr && posicion->arriba->contenido == '|') {
        posicion->arriba->descubierto = true;
        cout << "Hay un callejon cerrado al frente!" << endl;
        sumarPunto();
    }
}

void Detective::moverAbajo() {
    if (posicion->abajo != nullptr && posicion->abajo->contenido != '|') {
        posicion = posicion->abajo;
        posicion->descubierto = true;
        if (posicion->contenido == 'o') posicion->contenido = ' ';
        sumarPunto();
    } else if (posicion->abajo != nullptr && posicion->abajo->contenido == '|') {
        posicion->abajo->descubierto = true;
        cout << "Hay un callejon cerrado al frente!" << endl;
        sumarPunto();
    }
}

void Detective::moverIzquierda() {
    if (posicion->izquierda != nullptr && posicion->izquierda->contenido != '|') {
        posicion = posicion->izquierda;
        posicion->descubierto = true;
        if (posicion->contenido == 'o') posicion->contenido = ' ';
        sumarPunto();
    } else if (posicion->izquierda != nullptr && posicion->izquierda->contenido == '|') {
        posicion->izquierda->descubierto = true;
        cout << "Hay un callejon cerrado al frente!" << endl;
        sumarPunto();
    }
}

void Detective::moverDerecha() {
    if (posicion->derecha != nullptr && posicion->derecha->contenido != '|') {
        posicion = posicion->derecha;
        posicion->descubierto = true;
        if (posicion->contenido == 'o') posicion->contenido = ' ';
        sumarPunto();
    } else if (posicion->derecha != nullptr && posicion->derecha->contenido == '|') {
        posicion->derecha->descubierto = true;
        cout << "Hay un callejon cerrado al frente!" << endl;
        sumarPunto();
    }
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

void Detective::usarPista() {
    if (pilaDeEvidencias.estaVacia()) {
        cout << "No tienes pistas para usar." << endl;
        return;
    }

    Pista p = pilaDeEvidencias.desapilar();

    cout << "Usaste: " << p.getNombre() << endl;
    cout << "Efecto: " << p.getDescripcionEfecto() << endl;

    switch (p.tipo) {
        case HUELLA:
            puntuacion = puntuacion / 2;
            cout << "Tu puntaje ahora es: " << puntuacion << endl;
            break;

        case COARTADA:
            cout << "Se eliminaran 2 callejones del tablero." << endl;
            break;

        case TESTIMONIO:
            if (rand() % 2 == 0) {
                puntuacion = 0;
                cout << "Mala suerte... puntaje a cero." << endl;
            } else {
                puntuacion = puntuacion * 2;
                cout << "Puntaje duplicado a: " << puntuacion << endl;
            }
            break;

        case PRUEBA_FORENSE:
            cout << "El detective se teletransportara a una posicion aleatoria." << endl;
            break;
    }
}
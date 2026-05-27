#include "Tablero.h"
#include <cstdlib>
#include <iostream>
using namespace std;

Tablero::Tablero() {
    inicio = nullptr;
    construir();
}

Tablero::~Tablero() {
    Nodo* filaActual = inicio;
    while (filaActual != nullptr) {
        Nodo* siguienteFila = filaActual->abajo;
        Nodo* actual = filaActual;

        while (actual != nullptr) {
            Nodo* siguiente = actual->derecha;
            delete actual->pista;
            delete actual;
            actual = siguiente;
        }

        filaActual = siguienteFila;
    }
}

void Tablero::construir() {
    Nodo* filaAnterior = nullptr;

    for (int i = 0; i < FILAS; i++) {
        Nodo* primerNodoFila = nullptr;
        Nodo* nodoIzquierdo = nullptr;
        Nodo* nodoSuperior = filaAnterior;

        for (int j = 0; j < COLUMNAS; j++) {
            Nodo* nuevo = new Nodo(i, j);

            if (primerNodoFila == nullptr) {
                primerNodoFila = nuevo;
            }

            if (nodoIzquierdo != nullptr) {
                nodoIzquierdo->derecha = nuevo;
                nuevo->izquierda = nodoIzquierdo;
            }

            if (nodoSuperior != nullptr) {
                nodoSuperior->abajo = nuevo;
                nuevo->arriba = nodoSuperior;
                nodoSuperior = nodoSuperior->derecha;
            }

            nodoIzquierdo = nuevo;
        }

        if (inicio == nullptr) {
            inicio = primerNodoFila;
        }

        filaAnterior = primerNodoFila;
    }
}

Nodo* Tablero::obtenerInicio() {
    return inicio;
}

bool Tablero::casillaDisponible(Nodo* nodo, bool soloOculta) {
    if (nodo == nullptr) return false;
    if (nodo->contenido != 'o') return false;
    if (nodo->tienePista || nodo->tieneTestigo) return false;
    if (soloOculta && nodo->descubierto) return false;
    return true;
}

Nodo* Tablero::escogerCasillaDisponible(bool soloOculta) {
    Nodo* elegido = nullptr;
    int encontrados = 0;

    for (Nodo* fila = inicio; fila != nullptr; fila = fila->abajo) {
        for (Nodo* actual = fila; actual != nullptr; actual = actual->derecha) {
            if (casillaDisponible(actual, soloOculta)) {
                encontrados++;
                if (rand() % encontrados == 0) {
                    elegido = actual;
                }
            }
        }
    }

    return elegido;
}

Nodo* Tablero::escogerCallejon() {
    Nodo* elegido = nullptr;
    int encontrados = 0;

    for (Nodo* fila = inicio; fila != nullptr; fila = fila->abajo) {
        for (Nodo* actual = fila; actual != nullptr; actual = actual->derecha) {
            if (actual->contenido == '|') {
                encontrados++;
                if (rand() % encontrados == 0) {
                    elegido = actual;
                }
            }
        }
    }

    return elegido;
}

Nodo* Tablero::obtenerPosicionInicial() {
    return escogerCasillaDisponible(false);
}

void Tablero::colocarCallejones() {
    int colocados = 0;
    while (colocados < 16) {
        Nodo* casilla = escogerCasillaDisponible(false);
        if (casilla == nullptr) return;
        casilla->contenido = '|';
        colocados++;
    }
}

void Tablero::colocarPistas() {
    TipoPista tipos[4] = {HUELLA, COARTADA, TESTIMONIO, PRUEBA_FORENSE};
    int colocadas = 0;

    while (colocadas < 10) {
        Nodo* casilla = escogerCasillaDisponible(false);
        if (casilla == nullptr) return;
        casilla->tienePista = true;
        casilla->pista = new Pista(tipos[rand() % 4]);
        colocadas++;
    }
}

void Tablero::colocarTestigos() {
    int colocados = 0;

    while (colocados < 5) {
        Nodo* casilla = escogerCasillaDisponible(false);
        if (casilla == nullptr) return;
        casilla->tieneTestigo = true;
        casilla->contenido = 'W';
        colocados++;
    }
}

void Tablero::imprimir(Detective& detective) {
    detective.mostrarPuntuacion();
    cout << "# # # # # # # # # # #" << endl;

    for (Nodo* fila = inicio; fila != nullptr; fila = fila->abajo) {
        cout << "# ";
        for (Nodo* actual = fila; actual != nullptr; actual = actual->derecha) {
            if (actual == detective.posicion) {
                cout << "D ";
            } else if (!actual->descubierto) {
                cout << "o ";
            } else {
                cout << actual->contenido << " ";
            }
        }
        cout << "#" << endl;
    }

    cout << "# # # # # # # # # # #" << endl;
}

void Tablero::eliminarCallejones(int cantidad) {
    int eliminados = 0;

    while (eliminados < cantidad) {
        Nodo* callejon = escogerCallejon();
        if (callejon == nullptr) break;

        callejon->contenido = ' ';
        callejon->descubierto = true;
        eliminados++;
    }

    cout << "Se eliminaron " << eliminados << " callejones del tablero." << endl;
}

void Tablero::teletransportar(Detective& detective) {
    Nodo* destino = escogerCasillaDisponible(true);

    if (destino == nullptr) {
        cout << "No hay una ubicacion oculta disponible para teletransportar." << endl;
        return;
    }

    detective.posicion = destino;
    detective.posicion->descubierto = true;
    cout << "El detective fue teletransportado!" << endl;
}

void Tablero::resetearMapa() {
    for (Nodo* fila = inicio; fila != nullptr; fila = fila->abajo) {
        for (Nodo* actual = fila; actual != nullptr; actual = actual->derecha) {
            if (actual->contenido == ' ') {
                actual->contenido = 'o';
                actual->descubierto = false;
            }
        }
    }
}

void Tablero::recolocarPista(Pista pista) {
    Nodo* casilla = escogerCasillaDisponible(false);

    if (casilla == nullptr) {
        cout << "No se encontro una casilla libre para recolocar la pista." << endl;
        return;
    }

    casilla->tienePista = true;
    casilla->pista = new Pista(pista.tipo);
    cout << "La pista " << pista.getNombre() << " volvio al mapa." << endl;
}

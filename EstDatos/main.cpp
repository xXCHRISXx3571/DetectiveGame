#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>

#include "Nodo.h"

using namespace std;

const int FILAS = 9;
const int COLUMNAS = 9;

void imprimirTablero(Nodo* tablero[FILAS][COLUMNAS], Nodo* detective) {

    cout << "# # # # # # # # # # #" << endl;

    for (int i = 0; i < FILAS; i++) {

        cout << "# ";

        for (int j = 0; j < COLUMNAS; j++) {

            if (tablero[i][j] == detective) {
                cout << "D ";
            }
            else {
                cout << tablero[i][j]->contenido << " ";
            }
        }

        cout << "#" << endl;
    }

    cout << "# # # # # # # # # # #" << endl;
}

int main() {

    srand(time(0));

    Nodo* tablero[FILAS][COLUMNAS];

    // CREAR NODOS

    for (int i = 0; i < FILAS; i++) {

        for (int j = 0; j < COLUMNAS; j++) {

            tablero[i][j] = new Nodo();
        }
    }

    // CONECTAR NODOS

    for (int i = 0; i < FILAS; i++) {

        for (int j = 0; j < COLUMNAS; j++) {

            // ARRIBA
            if (i > 0) {
                tablero[i][j]->arriba = tablero[i - 1][j];
            }

            // ABAJO
            if (i < FILAS - 1) {
                tablero[i][j]->abajo = tablero[i + 1][j];
            }

            // IZQUIERDA
            if (j > 0) {
                tablero[i][j]->izquierda = tablero[i][j - 1];
            }

            // DERECHA
            if (j < COLUMNAS - 1) {
                tablero[i][j]->derecha = tablero[i][j + 1];
            }
        }
    }

    // DETECTIVE ALEATORIO

    int filaRandom = rand() % FILAS;
    int columnaRandom = rand() % COLUMNAS;

    Nodo* detective = tablero[filaRandom][columnaRandom];

    char movimiento;

    while (true) {

        system("cls");

        imprimirTablero(tablero, detective);

        cout << endl;
        cout << "W = Arriba" << endl;
        cout << "S = Abajo" << endl;
        cout << "A = Izquierda" << endl;
        cout << "D = Derecha" << endl;
        cout << "Q = Salir" << endl;

        cin >> movimiento;

        movimiento = toupper(movimiento);

        if (movimiento == 'Q') {
            break;
        }

        // ARRIBA
        if (movimiento == 'W') {

            if (detective->arriba != nullptr) {
                detective = detective->arriba;
            }
        }

        // ABAJO
        else if (movimiento == 'S') {

            if (detective->abajo != nullptr) {
                detective = detective->abajo;
            }
        }

        // IZQUIERDA
        else if (movimiento == 'A') {

            if (detective->izquierda != nullptr) {
                detective = detective->izquierda;
            }
        }

        // DERECHA
        else if (movimiento == 'D') {

            if (detective->derecha != nullptr) {
                detective = detective->derecha;
            }
        }
    }

    return 0;
}
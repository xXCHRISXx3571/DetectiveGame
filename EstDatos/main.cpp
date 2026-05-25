#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <vector>
#include <string>

#include "Nodo.h"
#include "Detective.h"
#include "TablaHash.h"
#include "ColaTestigos.h"
#include "ABB.h"

using namespace std;

const int FILAS = 9;
const int COLUMNAS = 9;

void imprimirTablero(Nodo* tablero[FILAS][COLUMNAS], Detective& det) {

    det.mostrarPuntuacion();

    cout << "# # # # # # # # # # #" << endl;

    for (int i = 0; i < FILAS; i++) {
        cout << "# ";
        for (int j = 0; j < COLUMNAS; j++) {

            if (tablero[i][j] == det.posicion) {
                cout << "I "; // I de Investigador
            }
            else if (!tablero[i][j]->descubierto) {
                cout << "o ";
            }
            else {
                cout << tablero[i][j]->contenido << " ";
            }
        }
        cout << "#" << endl;
    }

    cout << "# # # # # # # # # # #" << endl;
}

void colocarCallejones(Nodo* tablero[FILAS][COLUMNAS]) {
    int colocados = 0;
    while (colocados < 16) {
        int f = rand() % FILAS;
        int c = rand() % COLUMNAS;
        if (tablero[f][c]->contenido == 'o') {
            tablero[f][c]->contenido = '|';
            colocados++;
        }
    }
}

void colocarPistas(Nodo* tablero[FILAS][COLUMNAS]) {
    TipoPista tipos[4] = {HUELLA, COARTADA, TESTIMONIO, PRUEBA_FORENSE};
    int colocados = 0;
    while (colocados < 10) {
        int f = rand() % FILAS;
        int c = rand() % COLUMNAS;
        if (tablero[f][c]->contenido == 'o' && !tablero[f][c]->tienePista) {
            tablero[f][c]->tienePista = true;
            tablero[f][c]->pista = new Pista(tipos[rand() % 4]);
            colocados++;
        }
    }
}

void colocarTestigos(Nodo* tablero[FILAS][COLUMNAS]) {
    string nombresTestigos[5] = {"Ana", "Luis", "Pedro", "Maria", "Jose"};
    int colocados = 0;
    while (colocados < 5) {
        int f = rand() % FILAS;
        int c = rand() % COLUMNAS;
        if (tablero[f][c]->contenido == 'o' && !tablero[f][c]->tienePista && !tablero[f][c]->tieneTestigo) {
            tablero[f][c]->tieneTestigo = true;
            tablero[f][c]->contenido = 'W';
            colocados++;
        }
    }
}

void eliminarCallejones(Nodo* tablero[FILAS][COLUMNAS]) {
    int eliminados = 0;
    int intentos = 0;
    while (eliminados < 2 && intentos < 100) {
        int f = rand() % FILAS;
        int c = rand() % COLUMNAS;
        if (tablero[f][c]->contenido == '|') {
            tablero[f][c]->contenido = ' ';
            tablero[f][c]->descubierto = true;
            eliminados++;
        }
        intentos++;
    }
    cout << "Se eliminaron " << eliminados << " callejones del tablero." << endl;
}

void teletransportar(Nodo* tablero[FILAS][COLUMNAS], Detective& det) {
    int intentos = 0;
    while (intentos < 100) {
        int f = rand() % FILAS;
        int c = rand() % COLUMNAS;
        if (tablero[f][c]->contenido == 'o' &&
            !tablero[f][c]->tienePista &&
            !tablero[f][c]->tieneTestigo) {
            det.posicion = tablero[f][c];
            cout << "El detective fue teletransportado!" << endl;
            return;
        }
        intentos++;
    }
}

void resetearMapa(Nodo* tablero[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (tablero[i][j]->contenido == ' ') {
                tablero[i][j]->contenido = 'o';
                tablero[i][j]->descubierto = false;
            }
        }
    }
}

void recolocarPista(Nodo* tablero[FILAS][COLUMNAS], Pista p) {
    int intentos = 0;
    while (intentos < 100) {
        int f = rand() % FILAS;
        int c = rand() % COLUMNAS;
        if (tablero[f][c]->contenido == 'o' && !tablero[f][c]->tienePista) {
            tablero[f][c]->tienePista = true;
            tablero[f][c]->pista = new Pista(p.tipo);
            return;
        }
        intentos++;
    }
}

int main() {

    srand(time(0));

    Nodo* tablero[FILAS][COLUMNAS];

    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS; j++)
            tablero[i][j] = new Nodo();

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (i > 0) tablero[i][j]->arriba = tablero[i-1][j];
            if (i < FILAS-1) tablero[i][j]->abajo = tablero[i+1][j];
            if (j > 0) tablero[i][j]->izquierda = tablero[i][j-1];
            if (j < COLUMNAS-1) tablero[i][j]->derecha = tablero[i][j+1];
        }
    }

    colocarCallejones(tablero);
    colocarPistas(tablero);
    colocarTestigos(tablero);

    string nombreDetective;
    cout << "Ingresa el nombre del detective: ";
    cin >> nombreDetective;

    int fD, cD;
    do {
        fD = rand() % FILAS;
        cD = rand() % COLUMNAS;
    } while (tablero[fD][cD]->contenido != 'o' ||
             tablero[fD][cD]->tienePista ||
             tablero[fD][cD]->tieneTestigo);

    Detective detective(nombreDetective, tablero[fD][cD]);
    detective.posicion->descubierto = true;

    Sospechoso candidatos[10] = {
        Sospechoso("Carlos",   "alto",  "negro",   "clara",  "grande",     "masculino", "diestro"),
        Sospechoso("Diana",    "alta",  "rubio",   "clara",  "respingada", "femenino",  "zurda"),
        Sospechoso("Eduardo",  "bajo",  "castano", "morena", "pequena",    "masculino", "diestro"),
        Sospechoso("Fernanda", "alta",  "rojo",    "clara",  "respingada", "femenino",  "zurda"),
        Sospechoso("Gonzalo",  "alto",  "negro",   "oscura", "grande",     "masculino", "diestro"),
        Sospechoso("Hilda",    "alta",  "rubio",   "morena", "pequena",    "femenino",  "diestra"),
        Sospechoso("Ivan",     "bajo",  "castano", "clara",  "grande",     "masculino", "zurdo"),
        Sospechoso("Julia",    "alta",  "negro",   "oscura", "respingada", "femenino",  "diestra"),
        Sospechoso("Kevin",    "alto",  "rubio",   "clara",  "pequena",    "masculino", "diestro"),
        Sospechoso("Laura",    "baja",  "rojo",    "morena", "grande",     "femenino",  "zurda")
    };

    TablaHash tablaHash;
    bool usado[10] = {false};
    int insertados = 0;

    while (insertados < 8) {
        int r = rand() % 10;
        if (!usado[r]) {
            usado[r] = true;
            tablaHash.insertar(candidatos[r]);
            insertados++;
        }
    }

    vector<string> nombresInsertados;
    for (int i = 0; i < 10; i++)
        if (usado[i]) nombresInsertados.push_back(candidatos[i].nombre);

    Sospechoso* culpable = tablaHash.buscar(nombresInsertados[rand() % 8]);
    if (culpable != nullptr) culpable->esCulpable = true;

    string atributosCulpable[6];
    if (culpable != nullptr) {
        atributosCulpable[0] = culpable->estatura;
        atributosCulpable[1] = culpable->cabello;
        atributosCulpable[2] = culpable->piel;
        atributosCulpable[3] = culpable->nariz;
        atributosCulpable[4] = culpable->sexo;
        atributosCulpable[5] = culpable->mano;
    }
    int atributoActual = 0;

    ColaTestigos colaTestigos;

    string declaraciones[5] = {
        atributosCulpable[0],
        atributosCulpable[1],
        atributosCulpable[2],
        atributosCulpable[3],
        atributosCulpable[4]
    };

    ABB historial;

    historial.buscarDetective(nombreDetective);

    int pistasRecogidas = 0;
    char movimiento;

    while (pistasRecogidas < 10) {

        system("cls");
        imprimirTablero(tablero, detective);

        cout << endl;
        cout << "W=Arriba  S=Abajo  A=Izquierda  D=Derecha" << endl;
        cout << "T=Ver pistas  S=Ver sospechosos  I=Interrogar  X=Usar pista  Q=Salir" << endl;

        cin >> movimiento;
        movimiento = toupper(movimiento);

        if (movimiento == 'Q') break;

        if (movimiento == 'T') {
            detective.verPistas();
            system("pause");
            continue;
        }

        if (movimiento == 'S') {
            tablaHash.mostrarTodos();
            system("pause");
            continue;
        }

        if (movimiento == 'I') {
            if (!colaTestigos.estaVacia()) {
                Testigo t = colaTestigos.desencolar();
                t.mostrar();
                tablaHash.revelarAtributo(t.declaracion);
            } else {
                cout << "No hay testigos en la cola." << endl;
            }
            system("pause");
            continue;
        }

        if (movimiento == 'X') {
            if (!detective.pilaDeEvidencias.estaVacia()) {
                Pista p = detective.pilaDeEvidencias.desapilar();
                cout << "Usaste: " << p.getNombre() << endl;
                cout << "Efecto: " << p.getDescripcionEfecto() << endl;

                switch (p.tipo) {
                    case HUELLA:
                        detective.puntuacion = detective.puntuacion / 2;
                        cout << "Tu puntaje ahora es: " << detective.puntuacion << endl;
                        break;

                    case COARTADA:
                        eliminarCallejones(tablero);
                        break;

                    case TESTIMONIO:
                        if (rand() % 2 == 0) {
                            detective.puntuacion = 0;
                            cout << "Mala suerte... puntaje a cero." << endl;
                        } else {
                            detective.puntuacion = detective.puntuacion * 2;
                            cout << "Puntaje duplicado a: " << detective.puntuacion << endl;
                        }
                        break;

                    case PRUEBA_FORENSE:
                        teletransportar(tablero, detective);
                        break;
                }

                recolocarPista(tablero, p);
                resetearMapa(tablero);
                pistasRecogidas--;

            } else {
                cout << "No tienes pistas para usar." << endl;
            }
            system("pause");
            continue;
        }

        Nodo* siguiente = nullptr;

        if (movimiento == 'W') siguiente = detective.posicion->arriba;
        else if (movimiento == 'S') siguiente = detective.posicion->abajo;
        else if (movimiento == 'A') siguiente = detective.posicion->izquierda;
        else if (movimiento == 'D') siguiente = detective.posicion->derecha;

        if (siguiente == nullptr) {
            cout << "No puedes salir del mapa!" << endl;
            system("pause");
            continue;
        }

        if (siguiente->contenido == '|') {
            siguiente->descubierto = true;
            cout << "Hay un callejon cerrado, busca otra ruta!" << endl;
            detective.sumarPunto();
            system("pause");
            continue;
        }

        detective.posicion = siguiente;
        detective.posicion->descubierto = true;
        if (detective.posicion->contenido == 'o')
            detective.posicion->contenido = ' ';
        detective.sumarPunto();

        if (detective.posicion->tienePista && detective.posicion->pista != nullptr) {
            Pista p = *(detective.posicion->pista);
            detective.recogerPista(p);
            pistasRecogidas++;

            if (atributoActual < 6) {
                tablaHash.revelarAtributo(atributosCulpable[atributoActual]);
                atributoActual++;
            }

            detective.posicion->tienePista = false;
            delete detective.posicion->pista;
            detective.posicion->pista = nullptr;
            detective.posicion->contenido = ' ';

            system("pause");
        }

        if (detective.posicion->tieneTestigo) {
            string decl = "";
            if (atributoActual < 6) decl = atributosCulpable[atributoActual];
            Testigo t("Testigo", decl);
            colaTestigos.encolar(t);
            detective.posicion->tieneTestigo = false;
            detective.posicion->contenido = ' ';
        }
    }

    system("cls");
    cout << "\n" << detective.nombre << ", has recolectado las 10 pistas. Es momento de acusar.\n" << endl;
    tablaHash.mostrarTodos();

    cout << "\n A quien acusas? > ";
    string acusado;
    cin >> acusado;

    Sospechoso* sospechoso = tablaHash.buscar(acusado);

    if (sospechoso != nullptr && sospechoso->esCulpable) {
        cout << "\n Caso resuelto! " << acusado << " era el culpable." << endl;
    } else {
        cout << "\n Acusacion incorrecta. El caso se cierra como fracasado." << endl;
        detective.puntuacion = detective.puntuacion * 2;
        cout << "Puntaje penalizado al doble: " << detective.puntuacion << endl;
    }

    cout << "Puntaje final: " << detective.puntuacion << " movimientos." << endl;

    historial.guardarPuntaje(detective.nombre, detective.puntuacion);
    historial.mostrarTodos();

    system("pause");
    return 0;
}
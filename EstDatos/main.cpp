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

// =============================================
// IMPRIMIR TABLERO
// =============================================
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

// =============================================
// COLOCAR CALLEJONES CERRADOS (16 en total)
// =============================================
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

// =============================================
// COLOCAR PISTAS (10 en total, ocultas)
// =============================================
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

// =============================================
// COLOCAR TESTIGOS (5 en total)
// =============================================
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

// =============================================
// ELIMINAR 2 CALLEJONES (efecto Coartada)
// =============================================
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

// =============================================
// TELETRANSPORTAR DETECTIVE (efecto Prueba Forense)
// =============================================
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

// =============================================
// RESETEAR MAPA (cuando se usa una pista con X)
// =============================================
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

// =============================================
// RECOLOCAR PISTA EN LUGAR ALEATORIO
// =============================================
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

// =============================================
// MAIN
// =============================================
int main() {

    srand(time(0));

    // --- CREAR TABLERO ---
    Nodo* tablero[FILAS][COLUMNAS];

    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS; j++)
            tablero[i][j] = new Nodo();

    // --- CONECTAR NODOS ---
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (i > 0) tablero[i][j]->arriba = tablero[i-1][j];
            if (i < FILAS-1) tablero[i][j]->abajo = tablero[i+1][j];
            if (j > 0) tablero[i][j]->izquierda = tablero[i][j-1];
            if (j < COLUMNAS-1) tablero[i][j]->derecha = tablero[i][j+1];
        }
    }

    // --- COLOCAR ELEMENTOS ---
    colocarCallejones(tablero);
    colocarPistas(tablero);
    colocarTestigos(tablero);

    // --- CREAR DETECTIVE ---
    string nombreDetective;
    cout << "Ingresa el nombre del detective: ";
    cin >> nombreDetective;

    // Posicion aleatoria que no tenga pista ni testigo ni callejon
    int fD, cD;
    do {
        fD = rand() % FILAS;
        cD = rand() % COLUMNAS;
    } while (tablero[fD][cD]->contenido != 'o' ||
             tablero[fD][cD]->tienePista ||
             tablero[fD][cD]->tieneTestigo);

    Detective detective(nombreDetective, tablero[fD][cD]);
    detective.posicion->descubierto = true;

    // --- CREAR SOSPECHOSOS ---
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

    // Marcar culpable al azar
    vector<string> nombresInsertados;
    for (int i = 0; i < 10; i++)
        if (usado[i]) nombresInsertados.push_back(candidatos[i].nombre);

    Sospechoso* culpable = tablaHash.buscar(nombresInsertados[rand() % 8]);
    if (culpable != nullptr) culpable->esCulpable = true;

    // Atributos del culpable para revelar uno a uno
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

    // --- COLA DE TESTIGOS ---
    ColaTestigos colaTestigos;

    // Testigos predefinidos con declaraciones del culpable
    string declaraciones[5] = {
        atributosCulpable[0],
        atributosCulpable[1],
        atributosCulpable[2],
        atributosCulpable[3],
        atributosCulpable[4]
    };

    // --- ABB HISTORIAL ---
    ABB historial;

    // Verificar si el detective ya jugo antes
    historial.buscarDetective(nombreDetective);

    int pistasRecogidas = 0;
    char movimiento;

    // =============================================
    // BUCLE PRINCIPAL DEL JUEGO
    // =============================================
    while (pistasRecogidas < 10) {

        system("cls");
        imprimirTablero(tablero, detective);

        cout << endl;
        cout << "W=Arriba  S=Abajo  A=Izquierda  D=Derecha" << endl;
        cout << "T=Ver pistas  S=Ver sospechosos  I=Interrogar  X=Usar pista  Q=Salir" << endl;

        cin >> movimiento;
        movimiento = toupper(movimiento);

        if (movimiento == 'Q') break;

        // --- VER PISTAS (T) ---
        if (movimiento == 'T') {
            detective.verPistas();
            system("pause");
            continue;
        }

        // --- VER SOSPECHOSOS (S) ---
        if (movimiento == 'S') {
            tablaHash.mostrarTodos();
            system("pause");
            continue;
        }

        // --- INTERROGAR TESTIGO (I) ---
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

        // --- USAR PISTA (X) ---
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

                // La pista vuelve al mapa y se resetea
                recolocarPista(tablero, p);
                resetearMapa(tablero);
                pistasRecogidas--;

            } else {
                cout << "No tienes pistas para usar." << endl;
            }
            system("pause");
            continue;
        }

        // --- MOVIMIENTO ---
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

        // Mover detective
        detective.posicion = siguiente;
        detective.posicion->descubierto = true;
        if (detective.posicion->contenido == 'o')
            detective.posicion->contenido = ' ';
        detective.sumarPunto();

        // Verificar si hay pista
        if (detective.posicion->tienePista && detective.posicion->pista != nullptr) {
            Pista p = *(detective.posicion->pista);
            detective.recogerPista(p);
            pistasRecogidas++;

            // Revelar atributo del culpable
            if (atributoActual < 6) {
                tablaHash.revelarAtributo(atributosCulpable[atributoActual]);
                atributoActual++;
            }

            // Limpiar pista del nodo
            detective.posicion->tienePista = false;
            delete detective.posicion->pista;
            detective.posicion->pista = nullptr;
            detective.posicion->contenido = ' ';

            system("pause");
        }

        // Verificar si hay testigo
        if (detective.posicion->tieneTestigo) {
            string decl = "";
            if (atributoActual < 6) decl = atributosCulpable[atributoActual];
            Testigo t("Testigo", decl);
            colaTestigos.encolar(t);
            detective.posicion->tieneTestigo = false;
            detective.posicion->contenido = ' ';
        }
    }

    // =============================================
    // FASE DE ACUSACION
    // =============================================
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

    // Guardar en historial
    historial.guardarPuntaje(detective.nombre, detective.puntuacion);
    historial.mostrarTodos();

    system("pause");
    return 0;
}
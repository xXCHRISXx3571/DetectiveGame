#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "ABB.h"
#include "ColaTestigos.h"
#include "Detective.h"
#include "Sospechoso.h"
#include "TablaHash.h"
#include "Tablero.h"
#include "Testigo.h"

using namespace std;

const int TOTAL_PISTAS = 10;
const int TOTAL_ATRIBUTOS = 6;

void limpiarPantalla() {
    system("cls");
}

void pausar() {
    system("pause");
}

string tomarAtributo(string atributos[], int& siguienteAtributo) {
    if (siguienteAtributo >= TOTAL_ATRIBUTOS) {
        return "";
    }

    string atributo = atributos[siguienteAtributo];
    siguienteAtributo++;
    return atributo;
}

void revelarSiExiste(TablaHash& tablaHash, string atributo) {
    if (atributo == "") {
        cout << "Ya se revelaron todos los atributos del culpable." << endl;
        return;
    }

    tablaHash.revelarAtributo(atributo);
}

void mostrarMenu() {
    cout << endl;
    cout << "Movimiento: W=Arriba  S=Abajo  A=Izquierda  D=Derecha" << endl;
    cout << "Acciones: T=Pistas  V=Sospechosos  I=Interrogar  X=Usar pista" << endl;
    cout << "Historial: H=Ver todos  B=Buscar detective  Q=Salir" << endl;
}

void cargarSospechosos(TablaHash& tablaHash, Sospechoso*& culpable) {
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

    bool usado[10] = {false};
    vector<string> nombresInsertados;

    while (nombresInsertados.size() < 8) {
        int indice = rand() % 10;
        if (!usado[indice]) {
            usado[indice] = true;
            tablaHash.insertar(candidatos[indice]);
            nombresInsertados.push_back(candidatos[indice].nombre);
        }
    }

    string nombreCulpable = nombresInsertados[rand() % nombresInsertados.size()];
    culpable = tablaHash.buscar(nombreCulpable, false);
    if (culpable != nullptr) {
        culpable->esCulpable = true;
    }
}

Nodo* obtenerSiguiente(Nodo* posicion, char movimiento) {
    if (movimiento == 'W') return posicion->arriba;
    if (movimiento == 'S') return posicion->abajo;
    if (movimiento == 'A') return posicion->izquierda;
    if (movimiento == 'D') return posicion->derecha;
    return nullptr;
}

void usarPista(Detective& detective, Tablero& tablero, int& pistasRecogidas) {
    if (detective.pilaDeEvidencias.estaVacia()) {
        cout << "No tienes pistas para usar." << endl;
        return;
    }

    Pista pista = detective.pilaDeEvidencias.desapilar();
    cout << "Usaste: " << pista.getNombre() << endl;
    cout << "Efecto: " << pista.getDescripcionEfecto() << endl;

    switch (pista.tipo) {
        case HUELLA:
            detective.puntuacion = detective.puntuacion / 2;
            cout << "Tu puntaje ahora es: " << detective.puntuacion << endl;
            break;

        case COARTADA:
            tablero.eliminarCallejones(2);
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
            tablero.teletransportar(detective);
            break;
    }

    tablero.recolocarPista(pista);
    tablero.resetearMapa();
    detective.posicion->descubierto = true;
    pistasRecogidas--;
}

void jugarPartida(ABB& historial) {
    Tablero tablero;
    tablero.colocarCallejones();
    tablero.colocarPistas();
    tablero.colocarTestigos();

    string nombreDetective;
    cout << "Ingresa el nombre del detective: ";
    cin >> nombreDetective;

    historial.buscarDetective(nombreDetective);

    Nodo* posicionInicial = tablero.obtenerPosicionInicial();
    Detective detective(nombreDetective, posicionInicial);
    detective.posicion->descubierto = true;

    TablaHash tablaHash;
    Sospechoso* culpable = nullptr;
    cargarSospechosos(tablaHash, culpable);

    if (culpable == nullptr) {
        cout << "No se pudo seleccionar culpable. La partida no puede continuar." << endl;
        return;
    }

    string atributosCulpable[TOTAL_ATRIBUTOS] = {
        culpable->estatura,
        culpable->cabello,
        culpable->piel,
        culpable->nariz,
        culpable->sexo,
        culpable->mano
    };

    int siguienteAtributo = 0;
    int pistasRecogidas = 0;
    int testigosEncontrados = 0;
    bool salir = false;
    ColaTestigos colaTestigos;

    while (pistasRecogidas < TOTAL_PISTAS && !salir) {
        limpiarPantalla();
        tablero.imprimir(detective);
        mostrarMenu();

        char accion;
        cin >> accion;
        accion = toupper(static_cast<unsigned char>(accion));

        if (accion == 'Q') {
            salir = true;
        } else if (accion == 'T') {
            detective.verPistas();
            pausar();
        } else if (accion == 'V') {
            tablaHash.mostrarTodos();
            pausar();
        } else if (accion == 'H') {
            historial.mostrarTodos();
            pausar();
        } else if (accion == 'B') {
            string nombreBuscado;
            cout << "Nombre del detective a buscar: ";
            cin >> nombreBuscado;
            historial.buscarDetective(nombreBuscado);
            pausar();
        } else if (accion == 'I') {
            if (!colaTestigos.estaVacia()) {
                Testigo testigo = colaTestigos.desencolar();
                testigo.mostrar();
                revelarSiExiste(tablaHash, testigo.declaracion);
            } else {
                cout << "No hay testigos en la cola." << endl;
            }
            pausar();
        } else if (accion == 'X') {
            usarPista(detective, tablero, pistasRecogidas);
            pausar();
        } else if (accion == 'W' || accion == 'S' || accion == 'A' || accion == 'D') {
            Nodo* siguiente = obtenerSiguiente(detective.posicion, accion);

            if (siguiente == nullptr) {
                cout << "No puedes atravesar los edificios del borde." << endl;
                pausar();
            } else if (siguiente->contenido == '|') {
                siguiente->descubierto = true;
                detective.sumarPunto();
                cout << "Hay un callejon cerrado, busca otra ruta!" << endl;
                pausar();
            } else {
                detective.posicion = siguiente;
                detective.posicion->descubierto = true;
                detective.sumarPunto();

                if (detective.posicion->contenido == 'o') {
                    detective.posicion->contenido = ' ';
                }

                if (detective.posicion->tienePista && detective.posicion->pista != nullptr) {
                    Pista pista = *(detective.posicion->pista);
                    detective.recogerPista(pista);
                    pistasRecogidas++;
                    revelarSiExiste(tablaHash, tomarAtributo(atributosCulpable, siguienteAtributo));

                    detective.posicion->tienePista = false;
                    delete detective.posicion->pista;
                    detective.posicion->pista = nullptr;
                    detective.posicion->contenido = ' ';
                    pausar();
                }

                if (detective.posicion->tieneTestigo) {
                    testigosEncontrados++;
                    Testigo testigo(
                        "No. " + to_string(testigosEncontrados),
                        tomarAtributo(atributosCulpable, siguienteAtributo)
                    );
                    colaTestigos.encolar(testigo);
                    detective.posicion->tieneTestigo = false;
                    detective.posicion->contenido = ' ';
                    pausar();
                }
            }
        } else {
            cout << "Comando no valido." << endl;
            pausar();
        }
    }

    limpiarPantalla();

    if (salir) {
        cout << "Partida cancelada. No se guarda puntaje porque el caso no finalizo." << endl;
        return;
    }

    cout << "\n" << detective.nombre
         << ", has recolectado las 10 pistas. Es momento de acusar.\n" << endl;
    tablaHash.mostrarTodos();

    cout << "\nA quien acusas? > ";
    string acusado;
    cin >> acusado;

    Sospechoso* sospechoso = tablaHash.buscar(acusado);

    if (sospechoso != nullptr && sospechoso->esCulpable) {
        cout << "\nCaso resuelto! " << sospechoso->nombre << " era el culpable." << endl;
    } else {
        cout << "\nAcusacion incorrecta. El caso se cierra como fracasado." << endl;
        detective.puntuacion = detective.puntuacion * 2;
        cout << "Puntaje penalizado al doble: " << detective.puntuacion << endl;
    }

    cout << "Puntaje final: " << detective.puntuacion << " movimientos." << endl;
    historial.guardarPuntaje(detective.nombre, detective.puntuacion);
    historial.mostrarTodos();
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    ABB historial;
    char continuar;

    do {
        jugarPartida(historial);
        cout << "\nDeseas jugar otra partida? (S/N): ";
        cin >> continuar;
        continuar = toupper(static_cast<unsigned char>(continuar));
    } while (continuar == 'S');

    pausar();
    return 0;
}

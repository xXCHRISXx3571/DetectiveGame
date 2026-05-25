#include "ABB.h"

ABB::ABB() {
    raiz = nullptr;
}

NodoABB* ABB::insertar(NodoABB* nodo, string nombre, int puntaje) {
    if (nodo == nullptr) {
        return new NodoABB(nombre, puntaje);
    }

    if (nodo->nombreDetective == nombre) {
        if (puntaje < nodo->mejorPuntaje) {
            nodo->mejorPuntaje = puntaje;
        }
        return nodo;
    }

    if (puntaje < nodo->mejorPuntaje) {
        nodo->izquierda = insertar(nodo->izquierda, nombre, puntaje);
    } else {
        nodo->derecha = insertar(nodo->derecha, nombre, puntaje);
    }

    return nodo;
}

NodoABB* ABB::buscar(NodoABB* nodo, string nombre) {
    if (nodo == nullptr) return nullptr;
    if (nodo->nombreDetective == nombre) return nodo;

    NodoABB* izq = buscar(nodo->izquierda, nombre);
    if (izq != nullptr) return izq;

    return buscar(nodo->derecha, nombre);
}

void ABB::mostrarOrdenado(NodoABB* nodo) {
    if (nodo == nullptr) return;
    mostrarOrdenado(nodo->izquierda);
    cout << " " << nodo->nombreDetective
         << " | Puntaje: " << nodo->mejorPuntaje << endl;
    mostrarOrdenado(nodo->derecha);
}

void ABB::guardarPuntaje(string nombre, int puntaje) {
    raiz = insertar(raiz, nombre, puntaje);
    cout << "Puntaje guardado para " << nombre << endl;
}

void ABB::buscarDetective(string nombre) {
    NodoABB* resultado = buscar(raiz, nombre);
    if (resultado != nullptr) {
        cout << nombre << " ha jugado antes. Mejor puntaje: "
             << resultado->mejorPuntaje << endl;
    } else {
        cout << nombre << " no ha jugado antes." << endl;
    }
}

void ABB::mostrarTodos() {
    if (raiz == nullptr) {
        cout << "No hay puntajes registrados." << endl;
        return;
    }
    cout << "\nHistorial de detectives (menor a mayor puntaje):" << endl;
    mostrarOrdenado(raiz);
}
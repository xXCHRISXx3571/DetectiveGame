#include "ABB.h"
#include <algorithm>

ABB::ABB() {
    raiz = nullptr;
}

ABB::~ABB() {
    liberar(raiz);
}

void ABB::liberar(NodoABB* nodo) {
    if (nodo == nullptr) return;
    liberar(nodo->izquierda);
    liberar(nodo->derecha);
    delete nodo;
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

void ABB::recolectar(NodoABB* nodo, vector<NodoABB*>& datos) {
    if (nodo == nullptr) return;
    recolectar(nodo->izquierda, datos);
    datos.push_back(nodo);
    recolectar(nodo->derecha, datos);
}

void ABB::guardarPuntaje(string nombre, int puntaje) {
    NodoABB* existente = buscar(raiz, nombre);
    if (existente != nullptr) {
        if (puntaje < existente->mejorPuntaje) {
            existente->mejorPuntaje = puntaje;
            cout << "Nuevo mejor puntaje guardado para " << nombre << endl;
        } else {
            cout << "Se conserva el mejor puntaje anterior de " << nombre << endl;
        }
        return;
    }

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

    vector<NodoABB*> datos;
    recolectar(raiz, datos);
    sort(datos.begin(), datos.end(), [](NodoABB* a, NodoABB* b) {
        return a->mejorPuntaje < b->mejorPuntaje;
    });

    for (NodoABB* nodo : datos) {
        cout << " " << nodo->nombreDetective
             << " | Puntaje: " << nodo->mejorPuntaje << endl;
    }
}

#include "TablaHash.h"
#include <iostream>
using namespace std;

TablaHash::TablaHash() {
    capacidad = 10;
    tabla.resize(capacidad);
    atributosRevelados = 0;
    for (int i = 0; i < 6; i++) pistasCulpable[i] = "";
}

int TablaHash::hashFuncion(string nombre) {
    int suma = 0;
    for (int i = 0; i < nombre.size(); i++) {
        suma += nombre[i];
    }
    return suma % capacidad;
}

void TablaHash::insertar(Sospechoso s) {
    int indice = hashFuncion(s.nombre);
    tabla[indice].push_back(s);
}

Sospechoso* TablaHash::buscar(string nombre) {
    int indice = hashFuncion(nombre);
    cout << "Buscando en indice: " << indice << " (O(1) promedio)" << endl;

    for (auto& s : tabla[indice]) {
        if (s.nombre == nombre) {
            return &s;
        }
    }
    return nullptr;
}

void TablaHash::revelarAtributo(string atributo) {
    if (atributosRevelados < 6) {
        pistasCulpable[atributosRevelados] = atributo;
        atributosRevelados++;
        cout << ">>> Nuevo atributo revelado del culpable: "
             << atributo << " <<<" << endl;
    }
}

void TablaHash::mostrarTodos() {
    cout << "\nSospechosos del caso:" << endl;
    cout << "Atributos confirmados del culpable: ";

    if (atributosRevelados == 0) {
        cout << "ninguno aun" << endl;
    } else {
        for (int i = 0; i < atributosRevelados; i++) {
            cout << pistasCulpable[i];
            if (i < atributosRevelados - 1) cout << ", ";
        }
        cout << endl;
    }

    cout << "\nLista de sospechosos:" << endl;
    for (int i = 0; i < capacidad; i++) {
        for (auto& s : tabla[i]) {
            cout << " " << s.nombre;
            if (s.esCulpable) {

            }
            cout << endl;
        }
    }
}

string TablaHash::getNombreCulpable() {
    for (int i = 0; i < capacidad; i++) {
        for (auto& s : tabla[i]) {
            if (s.esCulpable) return s.nombre;
        }
    }
    return "";
}
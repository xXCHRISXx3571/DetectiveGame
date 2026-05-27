#include "TablaHash.h"
#include <cctype>
#include <iostream>
using namespace std;

TablaHash::TablaHash() {
    capacidad = 10;
    tabla.resize(capacidad);
    atributosRevelados = 0;
    for (int i = 0; i < 6; i++) pistasCulpable[i] = "";
}

string TablaHash::normalizar(string texto) {
    for (size_t i = 0; i < texto.size(); i++) {
        texto[i] = static_cast<char>(tolower(static_cast<unsigned char>(texto[i])));
    }
    return texto;
}

int TablaHash::hashFuncion(string nombre) {
    nombre = normalizar(nombre);
    int suma = 0;
    for (size_t i = 0; i < nombre.size(); i++) {
        suma += nombre[i];
    }
    return suma % capacidad;
}

void TablaHash::insertar(Sospechoso s) {
    int indice = hashFuncion(s.nombre);
    tabla[indice].push_back(s);
}

Sospechoso* TablaHash::buscar(string nombre, bool mostrarProceso) {
    int indice = hashFuncion(nombre);
    if (mostrarProceso) {
        cout << "Buscando en indice: " << indice << " (O(1) promedio)" << endl;
    }

    for (auto& s : tabla[indice]) {
        if (normalizar(s.nombre) == normalizar(nombre)) {
            return &s;
        }
    }
    return nullptr;
}

bool TablaHash::atributoYaRevelado(string atributo) {
    for (int i = 0; i < atributosRevelados; i++) {
        if (pistasCulpable[i] == atributo) {
            return true;
        }
    }
    return false;
}

void TablaHash::revelarAtributo(string atributo) {
    if (atributo == "") {
        cout << "No hay nuevos atributos por revelar." << endl;
        return;
    }

    if (atributoYaRevelado(atributo)) {
        cout << "Ese atributo ya estaba revelado: " << atributo << endl;
        return;
    }

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
            s.mostrar();
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

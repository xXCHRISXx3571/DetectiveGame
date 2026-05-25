#ifndef ABB_H
#define ABB_H

#include <string>
#include <iostream>
using namespace std;

struct NodoABB {
    string nombreDetective;
    int mejorPuntaje;
    NodoABB* izquierda;
    NodoABB* derecha;

    NodoABB(string nombre, int puntaje) {
        nombreDetective = nombre;
        mejorPuntaje = puntaje;
        izquierda = nullptr;
        derecha = nullptr;
    }
};

class ABB {
private:
    NodoABB* raiz;

    // Metodos privados recursivos
    NodoABB* insertar(NodoABB* nodo, string nombre, int puntaje);
    NodoABB* buscar(NodoABB* nodo, string nombre);
    void mostrarOrdenado(NodoABB* nodo); // Inorden = menor a mayor

public:
    ABB();
    void guardarPuntaje(string nombre, int puntaje);
    void buscarDetective(string nombre);
    void mostrarTodos();
};

#endif
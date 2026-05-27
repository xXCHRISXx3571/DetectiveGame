#ifndef ABB_H
#define ABB_H

#include <string>
#include <iostream>
#include <vector>
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

    NodoABB* insertar(NodoABB* nodo, string nombre, int puntaje);
    NodoABB* buscar(NodoABB* nodo, string nombre);
    void recolectar(NodoABB* nodo, vector<NodoABB*>& datos);
    void liberar(NodoABB* nodo);

public:
    ABB();
    ~ABB();
    void guardarPuntaje(string nombre, int puntaje);
    void buscarDetective(string nombre);
    void mostrarTodos();
};

#endif

#ifndef TABLAHASH_H
#define TABLAHASH_H

#include "Sospechoso.h"
#include <vector>
#include <list>
using namespace std;

class TablaHash {
private:
    // Cada posicion del vector tiene una lista (para manejar colisiones)
    vector<list<Sospechoso>> tabla;
    int capacidad;
    int atributosRevelados;     // Cuantos atributos del culpable se han revelado
    string pistasCulpable[6];   // Atributos revelados del culpable

    int hashFuncion(string nombre); // Convierte nombre en indice

public:
    TablaHash();
    void insertar(Sospechoso s);
    Sospechoso* buscar(string nombre);  // Busqueda O(1) promedio
    void mostrarTodos();                // Para tecla S
    void revelarAtributo(string atributo); // Cuando se recoge pista
    void mostrarAtributosRevelados();
    string getNombreCulpable();
};

#endif
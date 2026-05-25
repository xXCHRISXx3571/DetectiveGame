#ifndef TABLAHASH_H
#define TABLAHASH_H

#include "Sospechoso.h"
#include <vector>
#include <list>
using namespace std;

class TablaHash {
private:

    vector<list<Sospechoso>> tabla;
    int capacidad;
    int atributosRevelados;
    string pistasCulpable[6];

    int hashFuncion(string nombre);

public:
    TablaHash();
    void insertar(Sospechoso s);
    Sospechoso* buscar(string nombre);
    void mostrarTodos();
    void revelarAtributo(string atributo);
    void mostrarAtributosRevelados();
    string getNombreCulpable();
};

#endif
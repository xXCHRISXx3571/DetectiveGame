#ifndef SOSPECHOSO_H
#define SOSPECHOSO_H

#include <string>
using namespace std;

class Sospechoso {
public:
    string nombre;
    string estatura;
    string cabello;
    string piel;
    string nariz;
    string sexo;
    string mano;
    bool esCulpable;

    Sospechoso();
    Sospechoso(string nombre, string estatura, string cabello,
               string piel, string nariz, string sexo, string mano);

    void mostrar();
    void mostrarConAtributos(string atributos[]);
};

#endif
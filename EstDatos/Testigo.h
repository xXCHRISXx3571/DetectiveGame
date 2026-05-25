#ifndef TESTIGO_H
#define TESTIGO_H

#include <string>
using namespace std;

class Testigo {
public:
    string nombre;
    string declaracion;

    Testigo();
    Testigo(string nombre, string declaracion);
    void mostrar();
};

#endif
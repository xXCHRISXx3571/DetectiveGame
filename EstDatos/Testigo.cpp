#include "Testigo.h"
#include <iostream>
using namespace std;

Testigo::Testigo() {
    nombre = "Testigo";
    declaracion = "";
}

Testigo::Testigo(string nombre, string declaracion) {
    this->nombre = nombre;
    this->declaracion = declaracion;
}

void Testigo::mostrar() {
    cout << "Testigo " << nombre
         << " dice: el culpable es " << declaracion << endl;
}
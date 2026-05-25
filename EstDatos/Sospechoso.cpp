#include "Sospechoso.h"
#include <iostream>
using namespace std;

Sospechoso::Sospechoso() {
    nombre = "";
    estatura = "";
    cabello = "";
    piel = "";
    nariz = "";
    sexo = "";
    mano = "";
    esCulpable = false;
}

Sospechoso::Sospechoso(string nombre, string estatura, string cabello,
                       string piel, string nariz, string sexo, string mano) {
    this->nombre = nombre;
    this->estatura = estatura;
    this->cabello = cabello;
    this->piel = piel;
    this->nariz = nariz;
    this->sexo = sexo;
    this->mano = mano;
    this->esCulpable = false;
}

void Sospechoso::mostrar() {
    cout << " " << nombre << " | estatura: " << estatura
         << " | cabello: " << cabello
         << " | piel: " << piel
         << " | nariz: " << nariz
         << " | sexo: " << sexo
         << " | mano: " << mano << endl;
}
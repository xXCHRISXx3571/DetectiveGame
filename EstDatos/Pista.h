#ifndef PISTA_H
#define PISTA_H

#include <string>
using namespace std;

enum TipoPista {
    HUELLA,
    COARTADA,
    TESTIMONIO,
    PRUEBA_FORENSE
};

class Pista {
public:
    TipoPista tipo;
    bool recogida;
    bool visible;

    Pista();
    Pista(TipoPista t);

    char getSimboloTablero();
    string getNombre();
    string getDescripcionEfecto();
};

#endif
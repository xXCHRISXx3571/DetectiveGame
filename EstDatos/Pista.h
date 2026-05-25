#ifndef PISTA_H
#define PISTA_H

#include <string>
using namespace std;

enum tipoPista {
    HUELLA,
    COARTADA,
    TESTIMONIO,
    PRUEBA_FORENSE
};

class Pista {
    public:
        tipoPista tipo;
        bool recogida;
        bool visible;

        Pista();
        Pista(tipoPista t);

        char getSimboloTablero();
        string getNombre();
        string getDescriocionEfecto();     
};    

#endif
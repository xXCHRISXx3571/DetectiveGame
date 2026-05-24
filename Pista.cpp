#include "Pista.h"

Pista::Pista() {
    tipo = HUELLA;
    recogida = false;
    visible = false;
}

Pista::Pista(tipoPista t) {
    tipo = t;
    recogida = false;
    visible = false;
}

char Pista::getSimboloTablero() {
    switch (tipo) {
        case HUELLA:
            return 'H';
        case COARTADA:
            return 'C';
        case TESTIMONIO:
            return 'T';
        case PRUEBA_FORENSE:
            return 'P';
        default:
            return '?';
    }
}


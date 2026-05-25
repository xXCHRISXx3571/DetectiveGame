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

string Pista::getNombre() {
    switch (tipo) {
        case HUELLA:
            return "Huella";
        case COARTADA:
            return "Coartada";
        case TESTIMONIO:
            return "Testimonio";
        case PRUEBA_FORENSE:
            return "Prueba Forense";
        default:
            return "Desconocida";
    }
}

string Pista::getDescriocionEfecto() {
    switch (tipo) {
        case HUELLA:
            return "Deja una huella digital en el lugar del crimen";
        case COARTADA:
            return "Prueba de presencia en el lugar del crimen";
        case TESTIMONIO:
            return "Información obtenida de un testigo";
        case PRUEBA_FORENSE:
            return "Evidencia científica recolectada del lugar del crimen";
        default:
            return "";
    }
}
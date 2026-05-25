#include "Pista.h"

Pista::Pista() {
    tipo = HUELLA;
    recogida = false;
    visible = false;
}

Pista::Pista(TipoPista t) {
    tipo = t;
    recogida = false;
    visible = false;
}

char Pista::getSimboloTablero() {
    switch (tipo) {
        case HUELLA:         return 'H';
        case COARTADA:       return 'C';
        case TESTIMONIO:     return 'T';
        case PRUEBA_FORENSE: return 'P';
        default:             return '?';
    }
}

string Pista::getNombre() {
    switch (tipo) {
        case HUELLA:         return "Huella";
        case COARTADA:       return "Coartada";
        case TESTIMONIO:     return "Testimonio";
        case PRUEBA_FORENSE: return "Prueba Forense";
        default:             return "Desconocida";
    }
}

string Pista::getDescripcionEfecto() {
    switch (tipo) {
        case HUELLA:         return "Reduce tu puntuacion a la mitad";
        case COARTADA:       return "Elimina dos callejones del tablero";
        case TESTIMONIO:     return "Tu puntaje se duplica o se vuelve 0";
        case PRUEBA_FORENSE: return "El detective se teletransporta a una casilla aleatoria";
        default:             return "";
    }
}
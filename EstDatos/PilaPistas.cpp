#include "PilaPistas.h"

void PilaPistas::apilar(Pista p) {
    pila.push(p);
}

Pista PilaPistas::desapilar() {
    Pista tope = pila.top();
    pila.pop();
    return tope;
}

Pista PilaPistas::verTope() {
    return pila.top();

}

bool PilaPistas::estaVacia() {
    return pila.empty();
}

int PilaPistas::tamano() {
    return pila.size();

}

void PilaPistas::mostrarPila() {
    stack<Pista> temporal = pila;
    stack<Pista> invertida;
    while (!temporal.empty()) {
        invertida.push(temporal.top());
        temporal.pop();
    }

    cout << "['# #']" << endl;
    cout << "['# #']" << endl;

    int total = invertida.size();
    int contador = 0;

    while (!invertida.empty()) {
        Pista p = invertida.top();
        invertida.pop();
        contador++;

        cout << "['# " << p.getSimboloTablero() << " #']";

        if (contador == total)
            cout << " <- ultima (se usa con X)";
        else if (contador == total - 1)
            cout << " <- penultima";
        else if (contador == total - 2)
            cout << " <- antepenultima";

        cout << endl;
    }
    cout << "['# # # #']" << endl;
}

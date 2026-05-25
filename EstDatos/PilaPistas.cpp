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
    stack<Pista> temo = pila;
    stack<Pista> invertida;
    while (!temo.empty()) {
        invertida.push(temo.top());
        temo.pop();
    }

    cout << "['# #']" << endl;
    cout << "['# #']" << endl;

    bool esPrimera = true;
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
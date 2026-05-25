#include "ColaTestigos.h"

void ColaTestigos::encolar(Testigo t) {
    cola.push(t);
    cout << ">>> Testigo encontrado! Presiona I para interrogarlo <<<" << endl;
}

Testigo ColaTestigos::desencolar() {
    Testigo t = cola.front();
    cola.pop();
    return t;
}

bool ColaTestigos::estaVacia() {
    return cola.empty();
}

int ColaTestigos::tamanio() {
    return cola.size();
}
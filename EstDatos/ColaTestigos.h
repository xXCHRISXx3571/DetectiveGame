#ifndef COLATESTIGOS_H
#define COLATESTIGOS_H

#include "Testigo.h"
#include <queue>
#include <iostream>
using namespace std;

class ColaTestigos {
private:
    queue<Testigo> cola;

public:
    void encolar(Testigo t);      // Cuando detective pisa al testigo
    Testigo desencolar();         // Cuando usuario presiona I
    bool estaVacia();
    int tamanio();
};

#endif
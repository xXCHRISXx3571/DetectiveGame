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
    void encolar(Testigo t);
    Testigo desencolar();
    bool estaVacia();
    int tamanio();
};

#endif
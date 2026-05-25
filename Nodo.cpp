#include "Nodo.h"
#include "Pista.h"

Nodo::Nodo() {

    contenido = 'o';
    descubierto = false;
    tienePista = false;
    tieneTestigo = false;
    pista = nullptr;
    
    arriba = nullptr;
    abajo = nullptr;
    izquierda = nullptr;
    derecha = nullptr;
}
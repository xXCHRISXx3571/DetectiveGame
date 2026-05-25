#ifndef SOSPECHOSO_H
#define SOSPECHOSO_H

#include <string>
using namespace std;

class Sospechoso {
public:
    string nombre;
    string estatura;      // "alto" o "bajo"
    string cabello;       // "negro", "rubio", "rojo", "castano"
    string piel;          // "clara", "morena", "oscura"
    string nariz;         // "grande", "pequena", "respingada"
    string sexo;          // "masculino" o "femenino"
    string mano;          // "zurdo" o "diestro"
    bool esCulpable;      // Solo uno sera true

    Sospechoso();
    Sospechoso(string nombre, string estatura, string cabello,
               string piel, string nariz, string sexo, string mano);

    void mostrar();                          // Muestra todos sus datos
    void mostrarConAtributos(string atributos[]); // Muestra solo atributos revelados
};

#endif
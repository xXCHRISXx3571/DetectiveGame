cmake_minimum_required(VERSION 3.10)
project(detective)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(detective
        ABB.cpp
        ABB.h
        ColaTestigos.cpp
        ColaTestigos.h
        Detective.cpp
        Detective.h
        main.cpp
        Nodo.cpp
        Nodo.h
        PilaPistas.cpp
        PilaPistas.h
        Pista.cpp
        Pista.h
        Sospechoso.cpp
        Sospechoso.h
        Tablero.cpp
        Tablero.h
        TablaHash.cpp
        TablaHash.h
        Testigo.cpp
        Testigo.h)

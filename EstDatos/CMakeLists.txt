cmake_minimum_required(VERSION 4.2)
project(estrct)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(estrct
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
        TablaHash.cpp
        TablaHash.h
        Testigo.cpp
        Testigo.h)

cmake_minimum_required(VERSION 4.2)
project(EstDatos)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(EstDatos
        Nodo.cpp Nodo.h
        Pista.cpp Pista.h
        PilaPistas.cpp PilaPistas.h
        Detective.cpp Detective.h
        Sospechoso.cpp Sospechoso.h
        TablaHash.cpp TablaHash.h
        Testigo.cpp Testigo.h
        ColaTestigos.cpp ColaTestigos.h
        ABB.cpp ABB.h
        main.cpp)

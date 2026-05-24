cmake_minimum_required(VERSION 4.2)
project(EstDatos)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(EstDatos
        Nodo.cpp
        Nodo.h
        main.cpp)

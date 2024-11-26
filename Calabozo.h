#pragma once
#include <iostream>
#include <string>
#include "Monstruo.h"
#include "Grafo.h"

template <typename T>
class Cuarto {
private:
    Monstruos<T>* monstruos;  // Puntero al objeto Monstruos

public:
    Cuarto(Monstruos<T>* monstruos) : monstruos(monstruos) {}

    ~Cuarto() {}

    Monstruos<T>* getMonstruos() {
        return monstruos;
    }
};

template <typename T>
class Calabozo {
private:
    Grafo<int> grafo;
    Cuarto<T>** cuartos;
    int numVertices;

public:
    // Constructor
    explicit Calabozo(int numCuartos)
        : grafo(numCuartos), numVertices(numCuartos) {
        cuartos = new Cuarto<T>*[numVertices];
        for (int i = 0; i < numVertices; ++i) {
            cuartos[i] = nullptr;
        }
    }

    // Destructor
    ~Calabozo() {
        for (int i = 0; i < numVertices; ++i) {
            delete cuartos[i];
        }
        delete[] cuartos;
    }

    // Crear un cuarto y asignarlo a un nodo
    bool makeCuarto(int id, Monstruos<T>* monstruos) {
        if (!monstruos) {
            std::cerr << "Error: Monstruos no puede ser nullptr." << std::endl;
            return false;
        }
        if (id >= numVertices) {
            std::cerr << "Error: El ID del cuarto está fuera de los límites." << std::endl;
            return false;
        }
        cuartos[id] = new Cuarto<T>(monstruos);
        return true;
    }


    void conectarCuartos(int origen, int destino) {
        if (origen >= numVertices || destino >= numVertices) {
            std::cerr << "Error: Índices fuera de los límites." << std::endl;
            return;
        }
        grafo.agregarArista(origen, destino);
    }


    void mostrarCalabozo() const {
        for (int i = 0; i < numVertices; ++i) {
            if (cuartos[i] && cuartos[i]->getMonstruos()) {
                std::cout << "[" << i << "] Cuarto con " << cuartos[i]->getMonstruos()->getNombre() << " : ";
            } else {
                std::cout << "[" << i << "] Cuarto vacío : ";
            }
            grafo.imprimirListaAdyacencia(i);
        }
    }

    bool cargarDesdeArchivo(const std::string& archivo = "../dungeon.txt") {
        return grafo.cargarDesdeArchivo();
    }

    // Obtener el tamaño del calabozo
    unsigned int getSize()  {
        return numVertices;
    }

};

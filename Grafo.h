#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Listaligada.h"  // Incluir la clase ListaLigada

template <typename T>
class Grafo {
private:
    int numVertices;            // Número de vértices
    ListaLigada<T>** adjList;   // Arreglo de punteros a listas de adyacencia

public:
    // Constructor
    Grafo(int vertices) : numVertices(vertices) {
        adjList = new ListaLigada<T>*[numVertices];
        for (int i = 0; i < numVertices; ++i) {
            adjList[i] = new ListaLigada<T>(); // Inicializar cada lista como vacía
        }
    }

    // Destructor
    ~Grafo() {
        for (int i = 0; i < numVertices; ++i) {
            delete adjList[i]; // Liberar cada lista ligada
        }
        delete[] adjList; // Liberar el arreglo de listas
    }

    // Agregar una arista al grafo
    void agregarArista(T origen, T destino) {
        adjList[origen]->agregarAlFinal(destino);
    }

    // Imprimir el grafo
    void imprimirGrafo() const {
        for (int i = 0; i < numVertices; ++i) {
            std::cout << "[" << i << "]: ";
            adjList[i]->imprimirLista();
            std::cout << std::endl;
        }
    }

    // Imprimir la lista de adyacencia de un vértice específico
    void imprimirListaAdyacencia(int vertice) const {
        if (vertice >= numVertices) {
            std::cerr << "Error: El vértice está fuera de los límites." << std::endl;
            return;
        }
        adjList[vertice]->imprimirLista();
        std::cout << std::endl;
    }

    // Obtener el tamaño del grafo desde un archivo
    int obtenerTamanoDesdeArchivo(const std::string& archivo) {
        std::ifstream entrada(archivo);
        if (!entrada.is_open()) {
            std::cerr << "No se pudo abrir el archivo: " << archivo << std::endl;
            return -1;
        }

        std::string linea;

        // Ignorar la primera línea (que dice "Grafo")
        if (!getline(entrada, linea)) {
            std::cerr << "Error: Archivo vacío o formato incorrecto." << std::endl;
            return -1;
        }

        // Leer la segunda línea, que contiene el número de vértices
        if (!getline(entrada, linea)) {
            std::cerr << "Error: No se encontró el número de vértices en el archivo." << std::endl;
            return -1;
        }

        entrada.close();

        // Convertir la línea a un entero
        if (linea.empty() || linea.find_first_not_of("0123456789") != std::string::npos) {
            std::cerr << "Formato inválido para el número de vértices: " << linea << std::endl;
            return -1;
        }

        return std::stoi(linea);  // Devuelve el número de vértices
    }

    // Cargar las conexiones desde un archivo
    bool cargarDesdeArchivo() {
        std::ifstream archivo("../dungeon.txt");
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo dungeon.txt" << std::endl;
            return false;
        }

        std::string linea;

        // Ignorar la primera línea del archivo
        if (!getline(archivo, linea)) {
            std::cerr << "Error: Archivo vacío o formato incorrecto." << std::endl;
            return false;
        }
        if (linea != "Grafo") {
            std::cerr << "Error: La primera línea del archivo debe ser 'Grafo'" << std::endl;
            return false;
        }

        // Leer el número de vértices desde la segunda línea
        if (!getline(archivo, linea)) {
            std::cerr << "Error: No se encontró el número de vértices." << std::endl;
            return false;
        }

        int totalVertices = std::stoi(linea);
        if (totalVertices != numVertices) {
            std::cerr << "Error: El número de vértices no coincide con el tamaño del grafo." << std::endl;
            return false;
        }

        // Leer las conexiones (aristas) de cada vértice
        for (int i = 0; i < numVertices; ++i) {
            if (!getline(archivo, linea)) {
                std::cerr << "No se encontraron suficientes líneas para las conexiones." << std::endl;
                return false;
            }

            std::istringstream ss(linea);
            T destino;
            while (ss >> destino) {
                agregarArista(i, destino);
            }
        }

        archivo.close();
        return true;
    }
};

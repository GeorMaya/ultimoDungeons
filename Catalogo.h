#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Arbol.h"
#include "Monstruo.h"

template <typename T>
class Catalogo {
private:
    Arbol<Monstruos<T>> arbol;  // Arbol binario para almacenar monstruos

    int contarNodos(NodoArbol<Monstruos<T>*>* nodo) const {
        if (nodo == nullptr) return 0;
        return 1 + contarNodos(nodo->left) + contarNodos(nodo->right);
    }

    // Metodo para buscar un nodo por índice
    Monstruos<T>* buscarPorIndice(NodoArbol<Monstruos<T>*>* nodo, int& indice, int objetivo) const {
        if (nodo == nullptr) return nullptr;

        // Buscar en la rama izquierda
        Monstruos<T>* encontrado = buscarPorIndice(nodo->left, indice, objetivo);
        if (encontrado != nullptr) return encontrado;

        // Incrementar el índice al visitar el nodo actual
        if (indice == objetivo) return nodo->dato;
        indice++;

        // Buscar en la rama derecha
        return buscarPorIndice(nodo->right, indice, objetivo);
    }

public:
    Catalogo() {}

    ~Catalogo() {}

    // Cargar monstruos desde un archivo CSV
    bool cargarCSV(const std::string& archivo = "../monsters.csv") {
        std::ifstream file(archivo);
        if (!file.is_open()) {
            std::cerr << "No se pudo abrir el archivo CSV " << archivo << std::endl;
            return false;
        }

        std::string line;
        getline(file, line);  // Saltar la primera línea
        while (getline(file, line)) {
            std::stringstream ss(line);
            std::string name, type, size, align;
            double cr, ac, hp;

            // Leer cada campo separado por comas
            getline(ss, name, ',');     // Nombre
            ss >> cr; ss.ignore();      // CR
            getline(ss, type, ',');     // Tipo
            getline(ss, size, ',');     // Tamaño
            ss >> ac; ss.ignore();      // AC
            ss >> hp; ss.ignore();      // HP
            getline(ss, align, ',');    // Alineación

            // Crear un objeto monstruo y agregarlo al árbol
            Monstruos<T>* monstruo = new Monstruos<T>(name, cr, type, size, ac, hp, align);
            arbol.insertar(monstruo);

        }

        file.close();
        return true;
    }

    // Obtener un monstruo aleatorio
    Monstruos<T>* getRandomMonstruo() {
        // Obtener el nodo raíz del árbol (a través de un metodo público en Arbol)
        NodoArbol<Monstruos<T>*>* raiz = arbol.obtenerRaiz();
        if (raiz == nullptr) return nullptr;

        // Contar el total de nodos en el árbol
        int totalNodos = contarNodos(raiz);
        if (totalNodos == 0) return nullptr;

        // Seleccionar un índice aleatorio
        int indiceAleatorio = rand() % totalNodos;

        // Buscar el monstruo correspondiente al índice aleatorio
        int indiceActual = 0;
        return buscarPorIndice(raiz, indiceActual, indiceAleatorio);
    }

};

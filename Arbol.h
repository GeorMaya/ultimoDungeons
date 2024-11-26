#pragma once
#include <iostream>
#include <string>

template <typename T>
class NodoArbol {
public:
    T dato;                   // Dato almacenado (puntero a T)
    NodoArbol* left;          // Puntero al hijo izquierdo
    NodoArbol* right;         // Puntero al hijo derecho

    NodoArbol(T dato) : dato(dato), left(nullptr), right(nullptr) {}
};

template <typename T>
class Arbol {
private:
    NodoArbol<T*>* root;  // Cambiado para manejar punteros como datos

    // Recorrer el árbol y liberar memoria
    void destruirArbol(NodoArbol<T*>* nodo) {
        if (nodo != nullptr) {
            destruirArbol(nodo->left);
            destruirArbol(nodo->right);
            delete nodo->dato;  // Liberar el dato almacenado
            delete nodo;        // Liberar el nodo
        }
    }

    // Buscar un nodo específico en el árbol (por índice)
    NodoArbol<T*>* buscarIndex(NodoArbol<T*>* nodo, int& indice, int numero) const {
        if (nodo == nullptr) return nullptr;

        // Buscar en la rama izquierda
        NodoArbol<T*>* found = buscarIndex(nodo->left, indice, numero);
        if (found != nullptr) return found;

        indice++;
        if (indice == numero) return nodo;

        // Buscar en la rama derecha
        return buscarIndex(nodo->right, indice, numero);
    }

    // Contar nodos en el árbol
    int contarNodos(NodoArbol<T*>* nodo) const {
        if (nodo == nullptr) return 0;
        return 1 + contarNodos(nodo->left) + contarNodos(nodo->right);
    }

    // Insertar un nuevo nodo (recursivamente)
    NodoArbol<T*>* insertar(NodoArbol<T*>* nodo, T* dato) {
        if (nodo == nullptr) {
            return new NodoArbol<T*>(dato);  // Crear un nuevo nodo con el puntero
        }

        if (*dato < *(nodo->dato)) {  // Comparar los datos apuntados
            nodo->left = insertar(nodo->left, dato);
        } else {
            nodo->right = insertar(nodo->right, dato);
        }
        return nodo;
    }

public:
    // Constructor
    Arbol() : root(nullptr) {}

    // Destructor
    ~Arbol() {
        destruirArbol(root);
    }

    // Insertar un nuevo dato en el árbol
    void insertar(T* dato) {
        root = insertar(root, dato);
    }

    // Obtener la raíz del árbol (necesario para operaciones externas como getRandomMonstruo)
    NodoArbol<T*>* obtenerRaiz() const {
        return root;
    }

    // Obtener un nodo aleatorio
    T* obtenerAleatorio() {
        int totalNodos = contarNodos(root);
        if (totalNodos == 0) return nullptr;

        int randNum = rand() % totalNodos + 1;
        return buscar(randNum);
    }

    // Buscar un nodo por índice
    T* buscar(int num) const {
        int indice = 0;
        NodoArbol<T*>* nodo = buscarIndex(root, indice, num);
        return nodo ? nodo->dato : nullptr;
    }
};

#pragma once
#include <iostream>

template <typename T>
class Nodo {
public:
    T dato;               // Dato almacenado
    Nodo* siguiente;      // Puntero al siguiente nodo

    Nodo(T valor) : dato(valor), siguiente(nullptr) {}
};

template <typename T>
class ListaLigada {
private:
    Nodo<T>* head;        // Puntero al inicio de la lista

public:
    ListaLigada() : head(nullptr) {}

    ~ListaLigada() {
        // Liberar memoria de todos los nodos
        Nodo<T>* actual = head;
        while (actual != nullptr) {
            Nodo<T>* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }

    // Agregar un nodo al final de la lista
    void agregarAlFinal(const T& valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(valor);
        if (head == nullptr) {
            head = nuevoNodo; // Si la lista está vacía, el nuevo nodo es la cabeza
        } else {
            Nodo<T>* actual = head;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevoNodo; // Insertar al final
        }
    }

    // Imprimir la lista
    void imprimirLista() const {
        Nodo<T>* actual = head;
        while (actual != nullptr) {
            std::cout << actual->dato << " ";
            actual = actual->siguiente;
        }
    }

    // Obtener el nodo inicial
    Nodo<T>* obtenerInicio() const {
        return head;
    }
};


#pragma once
#include "Calabozo.h"

template<typename T>
class Jugador {
private:
    T raza;
    T nombre;
    double hp;
    double mp;

    Cuarto<T>* head;
    Cuarto<T>* tail;

public:
    Jugador(T raza=T(), T nombre=T(), double hp = double(), double mp = double())
        : raza(raza), nombre(nombre), hp(hp), mp(mp), head(nullptr), tail(nullptr) {}

    ~Jugador() {
        Cuarto<T>* temp = head;
        while (temp != nullptr) {
            Cuarto<T>* next = temp->right;
            if (temp -> getMonstruos())
                delete temp->getMonstruos();
            delete temp;
            temp = next;
        }
    }

    bool addCuarto(Cuarto<T>* cuarto) {
        if(!cuarto)
            return false;

        if(head == nullptr) {
            head == cuarto;
            tail == cuarto;
        }
        else {
            tail->right = cuarto;
            cuarto->left = tail;
            tail=cuarto;
        }
        return true;
    }
};
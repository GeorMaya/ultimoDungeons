#pragma once
#include <string>

template <typename T>
class Monstruos {
public:
    // Constructor por defecto
    Monstruos() :  cr(0), ac(0), hp(0) {}

    // Constructor con valores específicos
    Monstruos(T nombre, double cr, T tamano, T tipo, double ac, double hp, T align)
        : nombre(nombre), cr(cr), tipo(tipo), tamano(tamano), ac(ac), hp(hp), align(align) {}

    // Destructor
    ~Monstruos() {}

    // Métodos para devolver cada atributo de Monstruos
    T getNombre() const {
        return nombre;
    }
    T getTipo() const {
        return tipo;
    }
    T getTamano() const {
        return tamano;
    }
    T getAlign() const {
        return align;
    }
    double getCr() const {
        return cr;
    }
    double getAc() const {
        return ac;
    }
    double getHp() const {
        return hp;
    }

    // Sobrecarga del operador
    bool operator<(const Monstruos& otro) const {
        return cr < otro.cr;  // Compara utilizando el atributo CR (Challenge Rating)
    }

private:
    T nombre, tipo, tamano, align;
    double cr, ac, hp;
};

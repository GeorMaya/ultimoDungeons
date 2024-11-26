#include <iostream>
#include <ctime>
#include "Jugador.h"
#include "Calabozo.h"
#include "Catalogo.h"


using namespace std;

int main() {
    srand(time(0));
    using J = std::string;

    Catalogo<J> miCatalogo;

    Grafo<int> grafo(0);  // Se usa como objeto para llamar al metodo
    const std::string archivoDungeon = "../dungeon.txt";
    int tamanoCalabozo = grafo.obtenerTamanoDesdeArchivo(archivoDungeon);
    if (tamanoCalabozo <= 0) {
        std::cerr << "No se pudo determinar el tamaño del calabozo." << std::endl;
        return 1;
    }

    Calabozo<J> miCalabozo(tamanoCalabozo);


    if (!miCatalogo.cargarCSV()) {
        std::cout << "Catálogo no creado" << std::endl;
        return 0;
    }

    if (!miCalabozo.cargarDesdeArchivo()) {
        std::cout << "Error al cargar el archivo del calabozo." << std::endl;
        return 0;
    }

    // Asignar monstruos a los cuartos
    for (int i = 0; i < 31; i++) {
        Monstruos<J>* pMonstruo = miCatalogo.getRandomMonstruo();

        if (!pMonstruo) {
            std::cout << "No hay monstruos" << std::endl;
            return 0;
        }

        if (!miCalabozo.makeCuarto(i, pMonstruo)) {
            std::cout << "No se creó el cuarto" << std::endl;
            return 0;
        }
    }

    miCalabozo.mostrarCalabozo();
    return 0;
}

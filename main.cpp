// main.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include "Graph.h"
#include "Monstruo.h"
#include "Heroe.h"
#include "Combate.h"

using namespace std;

// Estructura para manejar array dinámico de monstruos
struct ArrayMonstruos {
    Monstruo** datos;
    int size;
    int capacidad;

    ArrayMonstruos() : datos(nullptr), size(0), capacidad(0) {}

    ~ArrayMonstruos() {
        for (int i = 0; i < size; i++) {
            delete datos[i];
        }
        delete[] datos;
    }

    void agregar(Monstruo* m) {
        if (size >= capacidad) {
            capacidad = (capacidad == 0) ? 10 : capacidad * 2;
            Monstruo** nuevoArray = new Monstruo*[capacidad];
            for (int i = 0; i < size; i++) {
                nuevoArray[i] = datos[i];
            }
            delete[] datos;
            datos = nuevoArray;
        }
        datos[size++] = m;
    }
};

/*ArrayMonstruos* cargarMonstruos(const string& archivo) {
    ArrayMonstruos* monstruos = new ArrayMonstruos();
    ifstream file(archivo);
    string linea;

    while (getline(file, linea)) {
        stringstream ss(linea);
        int id, hp, atk, def, rHP, rATK, rDEF;
        string nombre;
        double prob;

        ss >> id >> nombre >> hp >> atk >> def >> prob >> rHP >> rATK >> rDEF;
        monstruos->agregar(new Monstruo(id, nombre, hp, atk, def, prob, rHP, rATK, rDEF));
    }

    return monstruos;
}

Graph<int>* cargarGrafo(const string& archivo) {
    Graph<int>* grafo = new Graph<int>();
    ifstream file(archivo);
    string linea;

    // Primera pasada: crear casillas
    while (getline(file, linea)) {
        if (linea.empty()) break;
        stringstream ss(linea);
        int id;
        string nombre;
        double prob;

        ss >> id >> nombre >> prob;
        grafo->addCasilla(id);

        if (nombre == "Tesoro") {
            grafo->setCasillaTesoro(id);
        }
    }

    // Reiniciar el stream para la segunda pasada
    file.clear();
    file.seekg(0);

    // Segunda pasada: conectar vecinos
    while (getline(file, linea)) {
        stringstream ss(linea);
        int id1, id2;
        ss >> id1 >> id2;

        grafo->addEdge(id1, id2, false);
    }

    return grafo;
} */

/*int main() {
    srand(time(0));

    cout << "=== DUNGEON CRAWLER ===\n";
    cout << "Ingresa tu nombre (o 'mysticpath' para modo cheat): ";
    string input;
    cin >> input;

    auto grafo = cargarGrafo("dungeon.txt");
    auto monstruos = cargarMonstruos("monstruos.txt");

    if (input == "mysticpath") {
        grafo->mostrarRutaBFS();
        cout << "Presiona Enter para jugar...";
        cin.ignore();
        cin.get();
    }

    Heroe heroe(input, 50, 10, 5);
    auto casillaActual = grafo->getCasillaInicial();

    while (true) {
        cout << "\n=== " << casillaActual->getNombre() << " ===\n";
        cout << "Stats: HP=" << heroe.getHP() << " ATK=" << heroe.getATK()
             << " DEF=" << heroe.getDEF() << "\n";

        // Encuentro con monstruo
        if (!casillaActual->esVisitada()) {
            double rand_prob = (double)rand() / RAND_MAX;
            if (rand_prob < casillaActual->getProbabilidad()) {
                int idx = rand() % monstruos->size;
                Monstruo enemigo = *monstruos->datos[idx];

                if (!Combate::pelear(heroe, enemigo)) {
                    cout << "\nGAME OVER\n";
                    break;
                }
            }
            casillaActual->marcarVisitada();
        }

        // Verificar victoria
        if (casillaActual->getNombre() == "Tesoro") {
            cout << "\n¡HAS ENCONTRADO EL TESORO! ¡VICTORIA!\n";
            break;
        }

        // Mostrar opciones
        cout << "\nCasillas conectadas:\n";
        Casilla<int>** vecinos = casillaActual->getVecinos();
        int numVecinos = casillaActual->getNumVecinos();
        for (int i = 0; i < numVecinos; i++) {
            cout << i + 1 << ". " << vecinos[i]->getNombre() << "\n";
        }

        cout << "Elige tu movimiento: ";
        int eleccion;
        cin >> eleccion;

        if (eleccion > 0 && eleccion <= numVecinos) {
            casillaActual = vecinos[eleccion - 1];
        }
    }

    delete grafo;
    delete monstruos;
    return 0;
} */


int main() {
    Graph<int> g;

    g.addCasilla(1);
    g.addCasilla(2);
    g.addCasilla(3);

    g.addEdge(1, 2, false);
    g.addEdge(2, 3, false);

    g.print();          // Debe mostrar algo como:
                        //  <nombre casilla 1>: 2
                        //  <nombre casilla 2>: 1 3
                        //  <nombre casilla 3>: 2

    g.mostrarRutaBFS(); // Por ahora solo imprime el mensaje

    return 0;
}
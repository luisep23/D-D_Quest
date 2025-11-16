//
// Created by Dell on 11/11/2025.
//
// Graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include "Casilla.h"
#include <map>
#include <queue>
#include <iostream>

template <typename T>
class Graph {
private:
    Casilla<T>** casillas;
    int numCasillas;
    int capacidadCasillas;
    Casilla<T>* casillaInicial;
    Casilla<T>* casillaTesoro;

public:
    Graph() : casillas(nullptr), numCasillas(0), capacidadCasillas(0),
              casillaInicial(nullptr), casillaTesoro(nullptr) {}

    ~Graph() {
        for (int i = 0; i < numCasillas; i++) {
            delete casillas[i];
        }
        delete[] casillas;
    }

    void agregarCasilla(Casilla<T>* casilla) {
        if (numCasillas >= capacidadCasillas) {
            capacidadCasillas = (capacidadCasillas == 0) ? 10 : capacidadCasillas * 2;
            Casilla<T>** nuevoArray = new Casilla<T>*[capacidadCasillas];
            for (int i = 0; i < numCasillas; i++) {
                nuevoArray[i] = casillas[i];
            }
            delete[] casillas;
            casillas = nuevoArray;
        }
        casillas[numCasillas++] = casilla;
        if (numCasillas == 1) {
            casillaInicial = casilla;
        }
    }

    void setCasillaTesoro(Casilla<T>* tesoro) {
        casillaTesoro = tesoro;
    }

    Casilla<T>* getCasillaInicial() { return casillaInicial; }

    Casilla<T>* buscarCasillaPorId(T id) {
        for (int i = 0; i < numCasillas; i++) {
            if (casillas[i]->getId() == id) {
                return casillas[i];
            }
        }
        return nullptr;
    }

    // BFS para encontrar ruta más corta
    void mostrarRutaBFS() {
        if (!casillaInicial || !casillaTesoro) {
            std::cout << "No se puede calcular la ruta.\n";
            return;
        }

        std::queue<Casilla<T>*> cola;
        std::map<Casilla<T>*, Casilla<T>*> padre;
        std::map<Casilla<T>*, bool> visitado;

        cola.push(casillaInicial);
        visitado[casillaInicial] = true;
        padre[casillaInicial] = nullptr;

        bool encontrado = false;

        while (!cola.empty() && !encontrado) {
            Casilla<T>* actual = cola.front();
            cola.pop();

            if (actual == casillaTesoro) {
                encontrado = true;
                break;
            }

            Casilla<T>** vecinos = actual->getVecinos();
            int numVecinos = actual->getNumVecinos();
            for (int i = 0; i < numVecinos; i++) {
                if (!visitado[vecinos[i]]) {
                    visitado[vecinos[i]] = true;
                    padre[vecinos[i]] = actual;
                    cola.push(vecinos[i]);
                }
            }
        }

        if (encontrado) {
            std::cout << "\n=== RUTA MÁS CORTA AL TESORO ===\n";

            // Contar tamaño de ruta
            int tamRuta = 0;
            Casilla<T>* temp = casillaTesoro;
            while (temp != nullptr) {
                tamRuta++;
                temp = padre[temp];
            }

            // Crear array para ruta
            Casilla<T>** ruta = new Casilla<T>*[tamRuta];
            Casilla<T>* actual = casillaTesoro;
            int idx = 0;
            while (actual != nullptr) {
                ruta[idx++] = actual;
                actual = padre[actual];
            }

            for (int i = tamRuta - 1; i >= 0; i--) {
                std::cout << ruta[i]->getNombre();
                if (i > 0) std::cout << " -> ";
            }
            std::cout << "\n\n";

            delete[] ruta;
        } else {
            std::cout << "No se encontró ruta al tesoro.\n";
        }
    }
};

#endif

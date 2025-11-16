// Casilla.h
#ifndef CASILLA_H
#define CASILLA_H

#include <string>

template <typename T>
class Casilla {
private:
    T id;
    std::string nombre;
    double probabilidadMonstruo;
    bool visitada;
    Casilla<T>** vecinos;
    int numVecinos;
    int capacidadVecinos;

public:
    Casilla(T id, std::string nombre, double prob)
            : id(id), nombre(nombre), probabilidadMonstruo(prob), visitada(false),
              vecinos(nullptr), numVecinos(0), capacidadVecinos(0) {}

    ~Casilla() {
        delete[] vecinos;
    }

    T getId() const { return id; }
    std::string getNombre() const { return nombre; }
    double getProbabilidad() const { return probabilidadMonstruo; }
    bool esVisitada() const { return visitada; }
    void marcarVisitada() { visitada = true; }

    void agregarVecino(Casilla<T>* vecino) {
        if (numVecinos >= capacidadVecinos) {
            capacidadVecinos = (capacidadVecinos == 0) ? 4 : capacidadVecinos * 2;
            Casilla<T>** nuevoArray = new Casilla<T>*[capacidadVecinos];
            for (int i = 0; i < numVecinos; i++) {
                nuevoArray[i] = vecinos[i];
            }
            delete[] vecinos;
            vecinos = nuevoArray;
        }
        vecinos[numVecinos++] = vecino;
    }

    Casilla<T>** getVecinos() const { return vecinos; }
    int getNumVecinos() const { return numVecinos; }
};

#endif

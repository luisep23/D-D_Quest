// Casilla.h
#ifndef CASILLA_H
#define CASILLA_H

#include <string>

template <typename T>
class Casilla{
private:
    T id;
    
    std::string nombre;
    double probabilidadMonstruo;
    bool visitada;

    int numVecinos;
    int capacidadVecinos;

public:
    Casilla(const T& id, const std::string& nombre = "", double probMonstruo = 0.0)
        : id(id), nombre(nombre), probabilidadMonstruo(probMonstruo), visitada(false),  numVecinos(0), capacidadVecinos(0) {}


    ~Casilla() {
        delete[] vecinos;
    }

    T getId() const { return id; }
    std::string getNombre() const { return nombre; }
    double getProbabilidad() const { return probabilidadMonstruo; }
    bool esVisitada() const { return visitada; }
    void marcarVisitada() { visitada = true; }
    LinkedList<Casilla<T>> vecinos;

    /*Se eliminaron de vecinos para simplificar, se incluyen en Graph.tpp como edges en formato de lista ligada*/ 
};

#endif

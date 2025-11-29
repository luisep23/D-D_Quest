// Casilla.h
#ifndef CASILLA_H
#define CASILLA_H

#include <string>
#include "Edge.h"
#include "LinkedList.h"


/*Alusion a lo que en la clase fue conocido como Vertice. Misma logica para el grafo, mas informacion. Comparamos con el id y la data es el nombre*/

template <typename T>
class Casilla{
private:
    T id;
    
    std::string nombre;
    double probabilidadMonstruo;
    bool visitada;

public:
    
    bool operator==(const Casilla<T>& v) const {
        return id==v.getId();
    }

    Casilla(const T& id, const std::string& nombre = "", double probMonstruo = 0.0)
        : id(id), nombre(nombre), probabilidadMonstruo(probMonstruo), visitada(false){}


    ~Casilla() = default;

    T getId() const { return id; }
    std::string getNombre() const { return nombre; }
    double getProbabilidad() const { return probabilidadMonstruo; }
    bool esVisitada() const { return visitada; }
    void marcarVisitada() { visitada = true; }

    LinkedList<Edge<T>> vecinos; //solo guarda las ids de las casillas vecinas. Se implementa en Graph como lista ligada de edges y se arregla con print en Graph.tpp.

    /*Se eliminaron las funciones de vecinos para simplificar, se incluyen en Graph.tpp como edges en formato de lista ligada*/ 
};


//Implementado anteriormente dentro de la clase, separada por fallo de compilacion
template <typename T>
std::ostream& operator<<(std::ostream& out, const Casilla<T>& v) {
    out << v.getNombre() << " (" << v.getId() << ")";
    return out;
}

#endif

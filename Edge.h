#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

// Clase creada para solucionar el problema del peso sin tener que modificar drasticamente la estructura del grafo original

#include <iostream>
using namespace std;

template <typename T>
class Edge{
public:
    Edge(const T& value):destino(value), costo(0){}

    Edge(const T& value, costo):destino(value), costo(costo){}
    T destino;
    int costo;

    friend ostream& operator<<(ostream& out, const Vertex<T>& v) {
        out << v.destino << " (w=" << v.costo << ")";
        return out;
    }

    bool operator==(const Vertex<T>& v) const {
        return destino == v.destino;
    }

};


#endif // Edge_H_INCLUDED

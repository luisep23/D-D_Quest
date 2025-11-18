#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include "LinkedList.h"
#include "Casilla.h"

template <typename T>
class Graph{
private:
    LinkedList<Casilla<T>> vertices;

    Node<Casilla<T>>* findCasilla(const T& v);

    Node<Casilla<T>>* casillaInicial;

    Node<Casilla<T>>* casillaTesoro;


public:

    void setCasillaTesoro(Casilla<T>* tesoro);

    void setCasillaInicial(Casilla<T>* inicio);

    Graph() : vertices(), casillaInicial(nullptr), casillaTesoro(nullptr) {}

    bool addCasilla(const T& v, const std::string& nombre, double prob);

    bool addEdge(const T& from, const T& to, const bool directed);

    void print() const;

    void mostrarRutaBFS();
};

#include "Graph.tpp"

#endif // GRAFO_H_INCLUDED

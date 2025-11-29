#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include "LinkedList.h"
#include "Casilla.h"
#include <limits>
#include <iostream>

using namespace std;

template <typename T>
class Graph{
private:
    LinkedList<Casilla<T>> vertices;

    Node<Casilla<T>>* findCasilla(const T& v);

    Node<Casilla<T>>* casillaInicial;

    Node<Casilla<T>>* casillaTesoro;


public:

    Graph() : vertices(), casillaInicial(nullptr), casillaTesoro(nullptr) {}

    bool addCasilla(const T& v, const std::string& nombre, double prob);

    bool addEdge(const T& from, const T& to, const bool directed, int costo = 0);

    void print();

    void mostrarRutaBFS();

    void dijkstra(); // Para sacar la ruta de menor costo al tesoro
};

#include "Graph.tpp"

#endif // GRAFO_H_INCLUDED

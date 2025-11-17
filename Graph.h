#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include "LinkedList.h"
#include "Casilla.h"

template <typename T>
class Graph{
private:
    LinkedList<Casilla<T>> vertices;
    Node<Casilla<T>>* findCasilla(const T& v);


public:
    Graph()= default;


    bool addCasilla(const T& v);

    bool addEdge(const T& from, const T& to, const bool directed);

    void print() const;


};

#include "Graph.tpp"

#endif // GRAFO_H_INCLUDED

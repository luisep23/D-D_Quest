#pragma once
#include "Graph.h"

#include <iostream>

using namespace std;

template <typename T>
Node<Casilla<T>>* Graph<T>::findCasilla(const T& v){
    Node<Vertex<T>>* current= vertices.getHead();
    while (current) {
        if (current->data.getData() == v) {
            return current;
        }
        current= current->next;
    }
    return nullptr;
}

template <typename T>
void Graph<T>::setCasillaTesoro(Casilla<T> *tesoro){
    casillaTesoro= tesoro;
}

template <typename T>
inline void Graph<T>::setCasillaInicial(Casilla<T> *inicio){
    casillaInicial= inicio;
}


template <typename T>
bool Graph<T>::addCasilla(const T &v)
{
    if (findVertexNode(v) !=nullptr) {
        return false;
    }
    Vertex<T> vertex(v);
    vertices.pushBack(vertex);
    return true;
}

template <typename T>
bool Graph<T>::addEdge(const T& from,const T& to, const bool directed) {
    Node<Casilla<T>>* originNode = findVertexNode(from);
    Node<Casilla<T>>* toNode = findVertexNode(to);
    if (!originNode || !toNode) {
        return false;
    }

    if (!originNode->data.adj.search(to)) {
        originNode->data.adj.pushBack(to);
    }
    if (!directed) {
        if (!toNode->data.adj.search(from)) {
            toNode->data.adj.pushBack(from);
        }
    }
    return true;
}

template <typename T>
void Graph<T>::print() const {
    Node<Casilla<T>>* current = vertices.getHead();
    while (current) {
        cout << current->data.getNombre() <<": ";
        current->data.adj.print();
        current= current->next;
        cout<<endl;
    }
}

template <typename T>
void Graph<T>::mostrarRutaBFS(){
    // Implementación del recorrido BFS
    cout<<"Mostrando ruta BFS desde la casilla inicial hasta la casilla tesoro..."<<endl;
    // Aquí iría la lógica del BFS
}

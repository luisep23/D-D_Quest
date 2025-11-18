#pragma once
#include "Graph.h"

#include <iostream>

using namespace std;

template <typename T>
Node<Casilla<T>>* Graph<T>::findCasilla(const T& v){
    Node<Casilla<T>>* current= vertices.getHead();
    while (current) {
        if (current->data.getId() == v) {
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
bool Graph<T>::addCasilla(const T& v, const std::string& nombre, double prob){

    // No duplicados
    if (findCasilla(v) != nullptr) {
        return false;
    }

    Casilla<T> nueva(v, nombre, prob);
    vertices.pushBack(nueva);

    // Apuntar a la casilla recién insertada
    Node<Casilla<T>>* current = vertices.getHead();
    while (current->next) {
        current = current->next;
    }

    if (!casillaInicial) {
        casillaInicial = current;
    }
    // Si quieres marcar el tesoro:
    // if (nombre == "Tesoro") casillaTesoro = current;

    return true;
}

template <typename T>
bool Graph<T>::addEdge(const T& from, const T& to, const bool directed) {
    Node<Casilla<T>>* originNode = findCasilla(from);
    Node<Casilla<T>>* toNode     = findCasilla(to);

    if (!originNode || !toNode) {
        return false;
    }

    // vecinos es LinkedList<T>, T = id
    if (!originNode->data.vecinos.search(to)) {
        originNode->data.vecinos.pushBack(to);
    }

    if (!directed) {
        if (!toNode->data.vecinos.search(from)) {
            toNode->data.vecinos.pushBack(from);
        }
    }

    return true;
}

template <typename T>
void Graph<T>::print() const {
    Node<Casilla<T>>* current = vertices.getHead();
    while (current) {
        cout << current->data.getNombre() << " (" << current->data.getId() << "): ";
        current->data.vecinos.print();
        cout << endl;
        current = current->next;
    }
}

template <typename T>
void Graph<T>::mostrarRutaBFS(){
    // Implementación del recorrido BFS
    cout<<"Mostrando ruta BFS desde la casilla inicial hasta la casilla tesoro..."<<endl;
    // Aquí iría la lógica del BFS

}

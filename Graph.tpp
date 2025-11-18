#pragma once
#include "Graph.h"

#include <iostream>

using namespace std;

template <typename T>
Node<Casilla<T>>* Graph<T>::findCasilla(const T& v){
    Node<Casilla<T>>* current = vertices.getHead();
    while (current) {
        if (current->data.getId() == v) {
            return current;
        }
        current = current->next;
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
bool Graph<T>::addCasilla(const T& v,  const std::string& nombre, double prob){
    if (findCasilla(v) != nullptr) {
        return false; // ya existe
    }

    Casilla<T> nueva(v, nombre, prob);
    vertices.pushBack(nueva);

    // apuntar a la última casilla insertada
    Node<Casilla<T>>* current = vertices.getHead();
    while (current->next) {
        current = current->next;
    }

    if (!casillaInicial) {
        casillaInicial = current;
    }

    return true;
}


template <typename T>
bool Graph<T>::addEdge(const T& from, const T& to, const bool directed) {

    Node<Casilla<T>>* originNode = findCasilla(from);
    Node<Casilla<T>>* toNode     = findCasilla(to);

    if (!originNode || !toNode) {
        return false;
    }

    // vecinos es LinkedList<T> → guardamos solo IDs
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
        std::cout << current->data.getNombre()
                  << " (" << current->data.getId() << "): [";

        // Recorremos la lista de IDs vecinos
        Node<T>* vecinoIdNode = current->data.vecinos.getHead();
        while (vecinoIdNode) {
            // Buscamos la casilla asociada a ese ID
            Node<Casilla<T>>* vecinoNode =
                const_cast<Graph<T>*>(this)->findCasilla(vecinoIdNode->data);

            if (vecinoNode) {
                std::cout << " "
                          << vecinoNode->data.getNombre()
                          << " (" << vecinoNode->data.getId() << ") ->";
            } else {
                // Por si algo raro pasa, al menos mostramos el id
                std::cout << " " << vecinoIdNode->data << " ->";
            }

            vecinoIdNode = vecinoIdNode->next;
        }

        std::cout << " ]" << std::endl;
        current = current->next;
    }
}

template <typename T>
void Graph<T>::mostrarRutaBFS(){
    // Implementación del recorrido BFS
    cout<<"Mostrando ruta BFS desde la casilla inicial hasta la casilla tesoro..."<<endl;
    // Aquí iría la lógica del BFS

}

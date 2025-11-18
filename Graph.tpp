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

    if (nombre == "Inicio") {
        casillaInicial = current;
    }else if (nombre == "Tesoro") {
        casillaTesoro = current;
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
void Graph<T>::mostrarRutaBFS() {

    cout<<"\n=== MOSTRANDO RUTA MÁS CORTA AL TESORO (BFS) ===\n";

    if (!casillaInicial || !casillaTesoro) {
        std::cout << "No se puede calcular la ruta (falta inicio o tesoro).\n";
        return;
    }

    // 1) Pasar todos los vértices a un arreglo para poder indexarlos fácilmente
    int n = vertices.size();
    if (n == 0) {
        std::cout << "El grafo está vacío.\n";
        return;
    }

    Node<Casilla<T>>** nodos = new Node<Casilla<T>>*[n];
    Node<Casilla<T>>* aux = vertices.getHead();
    int idx = 0;
    while (aux != nullptr) {
        nodos[idx++] = aux;
        aux = aux->next;
    }

    // 2) Buscar el índice del inicio y del tesoro
    int idxInicio = -1;
    int idxTesoro = -1;
    for (int i = 0; i < n; ++i) {
        if (nodos[i] == casillaInicial) idxInicio = i;
        if (nodos[i] == casillaTesoro) idxTesoro = i;
    }

    if (idxInicio == -1 || idxTesoro == -1) {
        std::cout << "No se encontró inicio o tesoro en la lista de vértices.\n";
        delete[] nodos;
        return;
    }

    // 3) Arreglos auxiliares para BFS
    bool* visitado = new bool[n];
    int* padre = new int[n];      // guarda el índice del padre, -1 si no tiene
    int* cola = new int[n];       // cola simple por índices
    int ini = 0, fin = 0;         // [ini, fin) como rango en la cola

    for (int i = 0; i < n; ++i) {
        visitado[i] = false;
        padre[i] = -1;
    }

    // 4) Inicializar BFS desde el inicio
    cola[fin++] = idxInicio;
    visitado[idxInicio] = true;
    padre[idxInicio] = -1; // sin padre

    bool encontrado = false;

    // 5) BFS
    while (ini < fin && !encontrado) {
        int idxActual = cola[ini++];
        Node<Casilla<T>>* nodoActual = nodos[idxActual];

        if (idxActual == idxTesoro) {
            encontrado = true;
            break;
        }

        // Recorrer vecinos (IDs) de la casilla actual
        LinkedList<T>& listaVecinos = nodoActual->data.vecinos;
        Node<T>* v = listaVecinos.getHead();

        while (v != nullptr) {
            T idVecino = v->data;
            Node<Casilla<T>>* nodoVecino = findCasilla(idVecino);

            if (nodoVecino != nullptr) {
                // Obtener índice del vecino en el arreglo nodos[]
                int idxVecino = -1;
                for (int i = 0; i < n; ++i) {
                    if (nodos[i] == nodoVecino) {
                        idxVecino = i;
                        break;
                    }
                }

                if (idxVecino != -1 && !visitado[idxVecino]) {
                    visitado[idxVecino] = true;
                    padre[idxVecino] = idxActual;
                    cola[fin++] = idxVecino;
                }
            }

            v = v->next;
        }
    }

    // 6) Reconstruir la ruta si se encontró el tesoro
    if (encontrado) {
        std::cout << "\n=== RUTA MÁS CORTA AL TESORO ===\n";

        // Contar tamaño de la ruta desde tesoro hasta inicio usando padre[]
        int tamRuta = 0;
        for (int i = idxTesoro; i != -1; i = padre[i]) {
            ++tamRuta;
        }

        // Guardar índices de la ruta
        int* ruta = new int[tamRuta];
        int pos = tamRuta - 1;
        for (int i = idxTesoro; i != -1; i = padre[i]) {
            ruta[pos--] = i;
        }

        // Imprimir ruta de inicio a tesoro
        for (int i = 0; i < tamRuta; ++i) {
            std::cout << nodos[ruta[i]]->data.getNombre();
            if (i < tamRuta - 1) std::cout << " -> ";
        }
        std::cout << "\n\n";

        delete[] ruta;
    } else {
        std::cout << "No se encontró ruta al tesoro.\n";
    }

    // 7) Liberar memoria auxiliar
    delete[] nodos;
    delete[] visitado;
    delete[] padre;
    delete[] cola;
}

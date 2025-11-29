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
Node<Casilla<T>> *Graph<T>::getCasillaInicial(){
    return casillaInicial;
}

template <typename T>
Node<Casilla<T>> *Graph<T>::getCasillaPorId(const T &v){
    return findCasilla(v);
}


template <typename T>
bool Graph<T>::addCasilla(const T &v, const std::string &nombre, double prob)
{
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
bool Graph<T>::addEdge(const T& from, const T& to, const bool directed, int costo) {

    Node<Casilla<T>>* originNode = findCasilla(from);
    Node<Casilla<T>>* toNode     = findCasilla(to);

    if (!originNode || !toNode) {
        return false;
    }

    Edge<T> vTo(to, costo);

    // vecinos es LinkedList<T> → guardamos solo IDs
    if (!originNode->data.vecinos.search(vTo)) {
        originNode->data.vecinos.pushBack(vTo);
    }

    if (!directed) {
        Edge<T> fromEdge(from, costo);
        if (!toNode->data.vecinos.search(fromEdge)) {
            toNode->data.vecinos.pushBack(fromEdge);
        }
    }

    return true;
}


// Imprime el grafo mostrando los nombres de las casillas y sus conexiones. Arregla el problema de mostrar solo ID que hay en Casilla.h
template <typename T>

void Graph<T>::print(){
    Node<Casilla<T>>* current = vertices.getHead();
    while (current != nullptr) {
        // Imprimimos la casilla actual
       cout << current->data.getNombre() << " (" << current->data.getId() << "): [";

        //modificacion ahora incluye pesos
        
        // Recorremos la lista de IDs vecinos
        Node<Edge<T>>* vecinoIdNode = current->data.vecinos.getHead();
        Node<Casilla<T>>* vecinoNode = nullptr;

        while (vecinoIdNode != nullptr) {

            Edge<T>& v = vecinoIdNode->data;

            // Buscamos la casilla asociada a ese ID
            vecinoNode = this->findCasilla(vecinoIdNode->data.destino);

            if (vecinoNode != nullptr) {
                cout << " "<< vecinoNode->data.getNombre() << " (" << vecinoNode->data.getId() << ")" << "w= "<< v.costo <<" ->";
                /*Se impreme el id por si 2 casillas tienen el mismo nombre, asi no comparten id*/


            } else {
                // Por si algo raro pasa, al menos mostramos el id
                cout << " " << v.destino << " ->";
            }

            vecinoIdNode = vecinoIdNode->next;
        }

        cout << " ]" << endl;
        current = current->next;
    }
}

template <typename T>
void Graph<T>::mostrarRutaBFS() {

    cout<<"\n=== MOSTRANDO RUTA MÁS CORTA AL TESORO (BFS) ==="<<endl;

    if (casillaInicial == nullptr || casillaTesoro == nullptr) {
        cout << "No se puede calcular la ruta (falta inicio o tesoro)"<<endl;
        return;
    }

    
    //cuenta vertices 
    //nota para mi: posible optimizacion: guardar en un atributo el size del grafo para no estar llamando size() cada vez

    int n = vertices.size();
    if (n == 0) {
        cout << "El grafo está vacío.\n";
        return;
    }

    // 1) Pasar todos los vértices a un arreglo para poder indexarlos fácilmente
    // Nota: no lo pude resolver con LinkedList, por eso el arreglo dinámico
    Node<Casilla<T>>** nodos = new Node<Casilla<T>>*[n];
    Node<Casilla<T>>* current = vertices.getHead();
    int index = 0;
    while (current != nullptr) {
        nodos[index++] = current;
        current = current->next;
    }

    // 2) Buscar el índice del inicio y del tesoro
    int indexInicio = -1;
    int indexTesoro = -1;
    for (int i = 0; i < n; ++i) {
        if (nodos[i] == casillaInicial) {
            indexInicio = i;
        }
        if (nodos[i] == casillaTesoro) {
            indexTesoro = i;
        }
    }

    if (indexInicio == -1 || indexTesoro == -1) {
        cout << "No se encontró inicio o tesoro en la lista de vértices"<<endl;
        delete[] nodos;
        return;
    }

    // 3) Arreglos auxiliares para BFS
    bool* visitado = new bool[n];  // marca si el nodo i ya fue visitado
    int* queue = new int[n];  // queue para BFS
    int* padre = new int[n]; // para reconstruir la ruta
    int inicio = 0;
    int fin = 0;


    for (int i = 0; i < n; ++i) {
        visitado[i] = false;
        padre[i] = -1;
    }

    // 4) Inicializar BFS desde el inicio
    queue[fin++] = indexInicio;
    visitado[indexInicio] = true;
    padre[indexInicio] = -1; // sin padre

    bool encontrado = false;
    // 5) BFS
    while (inicio < fin && !encontrado) {
        int indexCurrent = queue[inicio++];
        Node<Casilla<T>>* nodoActual = nodos[indexCurrent]; /*ya ocupe current antes*/ 

        if (indexCurrent == indexTesoro) {
            encontrado = true;
            break;
        }

        // modificado a que acepte pesos
        // Recorrer vecinos (IDs) de la casilla actual
        LinkedList<Edge<T>>& listaVecinos = nodoActual->data.vecinos;
        Node<Edge<T>>* edgeActual = listaVecinos.getHead(); 

        while (edgeActual != nullptr) {
            Edge<T>& edge = edgeActual->data;
            // Buscar el índice del vecino
            T idVecino = edge.destino;


            // Buscar el nodo de la casilla vecina por su id
            Node<Casilla<T>>* nodoVecino = findCasilla(idVecino);

            if (nodoVecino != nullptr) {
                // Encontrar el índice del nodo vecino
                int indexVecino = -1;
                for (int i = 0; i < n; ++i) {
                    if (nodos[i] == nodoVecino) {
                        indexVecino = i;
                        break;
                    }
                }

                // Si no ha sido visitado, marcarlo y agregarlo a la queue
                if (indexVecino != -1 && !visitado[indexVecino]) {
                    visitado[indexVecino] = true;
                    padre[indexVecino] = indexCurrent;
                    queue[fin++] = indexVecino;
                }
            }
            edgeActual = edgeActual->next;

        }

    }
    // 6) Reconstruir la ruta si se encontró el tesoro
    if (encontrado) {
        cout << endl << "==== RUTA SECRETA AL TESORO ====" << endl;

        // Calcular el tamaño de la ruta
        int tamanoRuta = 0;
        for (int i = indexTesoro; i != -1; i = padre[i]) {
            ++tamanoRuta;
        }

        int* ruta = new int[tamanoRuta];
        int rutaIndex = tamanoRuta - 1;
        for (int i = indexTesoro; i != -1; i = padre[i]) {
            ruta[rutaIndex--] = i;
        }

        // Imprimir la ruta
        for (int i = 0; i < tamanoRuta; ++i) {
            int idx = ruta[i];
            cout << nodos[idx]->data.getNombre() << " (" << nodos[idx]->data.getId() << ")";
            if (i < tamanoRuta - 1) {
                cout << " -> ";
            }
        }
        cout << endl;

        // Imprimir el costo total de la ruta

        // Calcular el costo total de la ruta
        int costoTotal = 0;
        for (int i = 0; i < tamanoRuta - 1; ++i) {
            int idxActual = ruta[i];
            int idxSiguiente = ruta[i + 1];
            T idSiguiente = nodos[idxSiguiente]->data.getId();

            // Buscar el edge que conecta idxActual con idxSiguiente
            LinkedList<Edge<T>>& listaVecinos = nodos[idxActual]->data.vecinos;
            Node<Edge<T>>* edgeActual = listaVecinos.getHead();
            while (edgeActual != nullptr) {
                if (edgeActual->data.destino == idSiguiente) {
                    costoTotal += edgeActual->data.costo;
                    break;
                }
                edgeActual = edgeActual->next;
            }
        }
        // Ahora si imprimimos el costo total
        cout << "Costo total de la ruta: " << costoTotal << endl;
        cout << "Esta es la ruta mas corta(no la mas barata), no te pierdas!" << endl;




        delete[] ruta;

    }else {
        cout << "No se encontró una ruta al tesoro." << endl;
    }


    // 7) Liberar memoria auxiliar
    delete[] nodos;
    delete[] visitado;
    delete[] padre;
    delete[] queue;
}

template <typename T>
void Graph<T>::dijkstra(){
    Node<Casilla<T>>* current = vertices.getHead();


    // Revisamos que exista estas casillas y que haya conexion con el inicio
    int n = vertices.size();
    if (casillaInicial == nullptr || casillaTesoro == nullptr || n==0) {
        cout << "No se puede calcular la ruta (falta inicio o tesoro)"<<endl;
        return;
    }

    // 2) Crear arreglo de punteros a los nodos de la lista de vértices
    Node<Casilla<T>>** nodos = new Node<Casilla<T>>*[n];
    Node<Casilla<T>>* actual = vertices.getHead();
    int idx = 0;
    while (actual) {
        nodos[idx++] = actual;
        actual = actual->next;
    }

    // Localizar índices de inicio y tesoro
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

    // 3) Arreglos auxiliares: distancias, visitado, padre
    const int INF = std::numeric_limits<int>::max();

    int* dist      = new int[n];
    bool* visitado = new bool[n];
    int* padre     = new int[n];

    for (int i = 0; i < n; ++i) {
        dist[i]      = INF;
        visitado[i]  = false;
        padre[i]     = -1;
    }

    dist[idxInicio] = 0;

    // 4) Dijkstra O(n^2)
    for (int iter = 0; iter < n; ++iter) {
        // Elegir el vértice NO visitado con menor distancia
        int u = -1;
        int mejorDist = INF;
        for (int i = 0; i < n; ++i) {
            if (!visitado[i] && dist[i] < mejorDist) {
                mejorDist = dist[i];
                u = i;
            }
        }

        // Si ya no hay alcanzables, terminamos
        if (u == -1 || mejorDist == INF) break;

        // Si llegamos al tesoro, podemos cortar (opcional)
        if (u == idxTesoro) break;

        visitado[u] = true;

        Node<Casilla<T>>* nodoU = nodos[u];

        // Recorrer vecinos (Edge<T>: destino + costo)
        LinkedList<Edge<T>>& listaVecinos = nodoU->data.vecinos;
        Node<Edge<T>>* edge = listaVecinos.getHead();

        while (edge) {
            const Edge<T>& arista = edge->data;
            T idVecino = arista.destino;
            int peso   = arista.costo;

            // Buscar la casilla vecina por id
            Node<Casilla<T>>* nodoV = findCasilla(idVecino);
            if (nodoV) {
                // Obtener el índice v de ese nodo en nodos[]
                int v = -1;
                for (int i = 0; i < n; ++i) {
                    if (nodos[i] == nodoV) {
                        v = i;
                        break;
                    }
                }

                if (v != -1 && !visitado[v] && dist[u] != INF) {
                    int nuevaDist = dist[u] + peso;
                    if (nuevaDist < dist[v]) {
                        dist[v]  = nuevaDist;
                        padre[v] = u;
                    }
                }
            }

            edge = edge->next;
        }
    }

    // 5) Revisar si hay camino al tesoro
    if (dist[idxTesoro] == INF) {
        std::cout << "No hay ruta al tesoro.\n";
    } else {
        // 6) Reconstruir ruta usando padre[]
        int tamRuta = 0;
        for (int i = idxTesoro; i != -1; i = padre[i]) {
            ++tamRuta;
        }

        int* ruta = new int[tamRuta];
        int pos = tamRuta - 1;
        for (int i = idxTesoro; i != -1; i = padre[i]) {
            ruta[pos--] = i;
        }

        std::cout << "\n=== RUTA DE MENOR COSTO AL TESORO ===\n";
        std::cout << "Costo total = " << dist[idxTesoro] << "\n";

        for (int i = 0; i < tamRuta; ++i) {
            std::cout << nodos[ruta[i]]->data.getNombre()
                      << " (" << nodos[ruta[i]]->data.getId() << ")";
            if (i < tamRuta - 1) std::cout << " -> ";
        }
        std::cout << "\n\n";

        delete[] ruta;
    }

    // 7) Liberar memoria auxiliar
    delete[] nodos;
    delete[] dist;
    delete[] visitado;
    delete[] padre;

}

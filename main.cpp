
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include "Graph.h"
#include "Monstruo.h"
#include "Heroe.h"
#include "Combate.h"

using namespace std;

// Estructura para manejar array dinámico de monstruos
struct ArrayMonstruos {
    Monstruo** datos;
    int size;
    int capacidad;

    ArrayMonstruos() : datos(nullptr), size(0), capacidad(0) {}

    ~ArrayMonstruos() {
        for (int i = 0; i < size; i++) {
            delete datos[i];
        }
        delete[] datos;
    }

    void agregar(Monstruo* m) {
        if (size >= capacidad) {
            capacidad = (capacidad == 0) ? 10 : capacidad * 2;
            Monstruo** nuevoArray = new Monstruo*[capacidad];
            for (int i = 0; i < size; i++) {
                nuevoArray[i] = datos[i];
            }
            delete[] datos;
            datos = nuevoArray;
        }
        datos[size++] = m;
    }
};

ArrayMonstruos* cargarMonstruos(const string& archivo) {
    ArrayMonstruos* monstruos = new ArrayMonstruos();
    ifstream file(archivo);
    string linea;

    while (getline(file, linea)) {
        stringstream ss(linea);
        int id, hp, atk, def, rHP, rATK, rDEF;
        string nombre;
        double prob;

        ss >> id >> nombre >> hp >> atk >> def >> prob >> rHP >> rATK >> rDEF;
        monstruos->agregar(new Monstruo(id, nombre, hp, atk, def, prob, rHP, rATK, rDEF));
    }

    return monstruos;
}

Graph<int>* cargarGrafo(const std::string& archivo) {
    std::ifstream file(archivo);

    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << archivo << std::endl;
        return nullptr;
    }

    Graph<int>* grafo = new Graph<int>();

    std::string linea;

    // ============================
    // Buscar la sección ROOMS
    // ============================
    while (std::getline(file, linea)) {
        if (linea == "ROOMS")
            break;
    }

    // ============================
    // 1ª pasada: ROOMS
    // Formato:
    // id|nombre|probMonstruo
    // termina con END_ROOMS
    // ============================
    while (std::getline(file, linea)) {
        if (linea == "END_ROOMS")
            break;

        if (linea.empty() || linea[0] == '#')
            continue;

        // id|nombre|prob
        size_t p1 = linea.find('|');
        size_t p2 = linea.find('|', p1 + 1);
        if (p1 == std::string::npos || p2 == std::string::npos) {
            std::cerr << "Linea de ROOM invalida: " << linea << std::endl;
            continue;
        }

        std::string sid   = linea.substr(0, p1);
        std::string nombre = linea.substr(p1 + 1, p2 - p1 - 1);
        std::string sprob = linea.substr(p2 + 1);

        int id = std::stoi(sid);
        double prob = std::stod(sprob);

        grafo->addCasilla(id, nombre, prob);
    }

    // ============================
    // Buscar la sección EDGES
    // ============================
    while (std::getline(file, linea)) {
        if (linea == "EDGES")
            break;
    }

    // ============================
    // 2ª pasada: EDGES
    // Formato:
    // idOrigen idDestino
    // termina con END_EDGES
    // ============================
    while (std::getline(file, linea)) {
        if (linea == "END_EDGES")
            break;

        if (linea.empty() || linea[0] == '#')
            continue;

        std::stringstream ss(linea);
        int id1, id2;

        if (!(ss >> id1 >> id2)) {
            std::cerr << "Linea de EDGE invalida: " << linea << std::endl;
            continue;
        }

        // No hay costo en el archivo → asumimos 1
        grafo->addEdge(id1, id2, /*directed=*/false, /*costo=*/1);
    }

    return grafo;
}

int main() {
    srand(time(0));

    Graph<int>* grafo = cargarGrafo("dungeon.txt");
    auto monstruos = cargarMonstruos("monstruos.txt");

    cout<<"Se lee esto"<<endl;
    grafo->print();

    cout << "=== DUNGEON CRAWLER ===\n";
    cout << "Ingresa tu nombre (o 'mysticpath' para modo cheat): ";
    string input;
    cin >> input;

    
    

    if (!grafo || !monstruos) {
        cout << "Error al cargar datos.\n";
        return 1;
    }

    if (input == "mysticpath") {
        grafo->mostrarRutaBFS();
        grafo->dijkstra();
        cout << "Presiona Enter para jugar...";
        cin.ignore(); // limpia el '\n' pendiente de cin >> input
        cin.get();
    }

    Heroe heroe(input, 50, 10, 5);

    // OJO: casillaInicial es Node<Casilla<int>>*
    Node<Casilla<int>>* casillaActual = grafo->getCasillaInicial();

    while (true) {
        // data es un OBJETO Casilla<int>, no un puntero
        cout << "\n=== " << casillaActual->data.getNombre() << " ===\n";
        cout << "Stats: HP=" << heroe.getHP()
             << " ATK=" << heroe.getATK()
             << " DEF=" << heroe.getDEF() << "\n";

        // Encuentro con monstruo (solo la primera vez que entras)
        if (!casillaActual->data.esVisitada()) {
            double rand_prob = (double)rand() / RAND_MAX;
            if (rand_prob < casillaActual->data.getProbabilidad()) {
                int idx = rand() % monstruos->size;
                Monstruo enemigo = *monstruos->datos[idx];

                if (!Combate::pelear(heroe, enemigo)) {
                    cout << "\nGAME OVER\n";
                    break;
                }
            }
            casillaActual->data.marcarVisitada();
        }

        // Verificar victoria
        if (casillaActual->data.getNombre() == "Tesoro") {
            cout << "\n¡HAS ENCONTRADO EL TESORO! ¡VICTORIA!\n";
            break;
        }

        // ===============================
        // Mostrar opciones de vecinos
        // ===============================
        cout << "\nCasillas conectadas:\n";

        // vecinos es LinkedList<Edge<int>> publico en Casilla<int>
        LinkedList<Edge<int>>& listaVecinos = casillaActual->data.vecinos;

        // 1ª pasada: contar vecinos
        Node<Edge<int>>* edgeNode = listaVecinos.getHead();
        int numVecinos = 0;
        while (edgeNode) {
            numVecinos++;
            edgeNode = edgeNode->next;
        }

        if (numVecinos == 0) {
            cout << "No hay salidas desde esta casilla. Estás atrapado.\n";
            break;
        }

        // Reservamos arreglo de punteros a nodos de casillas
        Node<Casilla<int>>** opciones = new Node<Casilla<int>>*[numVecinos];

        // 2ª pasada: imprimir opciones y guardar los destinos
        edgeNode = listaVecinos.getHead();
        int idx = 0;
        while (edgeNode) {
            int idDestino = edgeNode->data.destino;  // el id de la casilla vecina
            Node<Casilla<int>>* destinoNode = grafo->getCasillaPorId(idDestino);

            // Por seguridad: si algo está raro y no encuentra la casilla
            if (!destinoNode) {
                cout << (idx + 1) << ". [ERROR: casilla " << idDestino << " no existe]\n";
                opciones[idx] = nullptr;
            } else {
                opciones[idx] = destinoNode;
                cout << (idx + 1) << ". " << destinoNode->data.getNombre()
                     << " (id: " << idDestino
                     << ", costo: " << edgeNode->data.costo << ")\n";
            }

            edgeNode = edgeNode->next;
            idx++;
        }

        cout << "Elige tu movimiento: ";
        int eleccion;
        cin >> eleccion;

        if (eleccion > 0 && eleccion <= numVecinos &&
            opciones[eleccion - 1] != nullptr) {
            casillaActual = opciones[eleccion - 1];
        } else {
            cout << "Opción inválida, te quedas en la misma casilla.\n";
        }

        delete[] opciones;
    }

    delete grafo;
    delete monstruos;
    return 0;
}
#ifndef VERTEX_H_INCLUDED
#define VERTEX_H_INCLUDED


#include "LinkedList.h"

template <typename T>
class Vertex{
private:
    T data;
    bool visited;

public:
    friend ostream& operator<<(ostream& out, const Vertex& v) {
        out<<v.getData();
        return out;
    }

    bool operator==(const Vertex<T>& v) {
        return data==v.getData();
    }

    Vertex(const T& v): data(v) {
        visited=false;
    }

    T getData() const getData() const{ return data;}
    bool isVisited() const {return visited;}
    void setVisited(bool visited){this->visited= visited;}
    LinkedList<Vertex<T>> adj;


};


#endif // VERTEX_H_INCLUDED

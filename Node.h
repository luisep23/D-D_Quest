#ifndef NODE_H
#define NODE_H

template <typename T>
class Node {
public:
    // Constructor
    Node(const T& v)Node(const T& v) : data(v), next(nullptr) {} // Declaración del constructor

    // Destructor virtual
    virtual ~Node();  // Declaración del destructor

    // Miembros de la clase
    T data;
    Node* next;
};


#endif // NODE_H


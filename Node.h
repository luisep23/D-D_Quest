#ifndef NODE_H
#define NODE_H

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;

    Node(const T& v) : data(v), next(nullptr) {}
    ~Node() = default;
};

#endif // NODE_H
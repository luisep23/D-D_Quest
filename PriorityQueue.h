#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "LinkedList.h"
#include <iostream>

template <typename T>
class PriorityQueue {
private:
    LinkedList<T> list;

public:
    PriorityQueue() = default;
    void push(const T& value);
    void pop();
    T top() const;
    bool empty() const;
    int size() const;
};

#include "PriorityQueue.tpp"


#endif

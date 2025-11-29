
#ifndef LINKEDLIST_TPP
#define LINKEDLIST_TPP

#include <iostream>
#include "LinkedList.h"

using namespace std;

template<typename T>
LinkedList<T>::LinkedList():head(nullptr), n(0){}

template<typename T>
LinkedList<T>::~LinkedList() {
    Node<T>* current=head;
    while (current) {
        head= current->next;
        delete current;
        current= head;
        n--;
    }
}

//Sacado del dijkstra por el profe
template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) : head(nullptr), n(0) {
    Node<T>* current = other.head;
    while (current) {
        pushBack(current->data);
        current = current->next;
    }
}


template<typename T>
bool LinkedList<T>::empty() const {
    return n==0;

}

template<typename T>
unsigned int LinkedList<T>::size() const{
    return n;
}

template<typename T>
void LinkedList<T>::print() {
    if (empty()) {
        cout<<"Lista vacia!"<<endl;
    }else {
        const Node<T>* current= head;
        cout<<"[";
        while (current) {
            cout<<" "<<current->data<<" ->";
            current= current->next;
        }
        cout<<"]"<<endl;
    }

}


template<typename T>
void LinkedList<T>::pushBack(const T &value) {
    Node<T>* newNode= new Node<T>(value);
    if (!head) {
        head= newNode;
    }else {
        Node<T>* current= head;
        while (current->next) {
            current= current->next;
        }
        current->next= newNode;
    }
    ++n;
}

template<typename T>
bool LinkedList<T>::insert(unsigned int index, const T &value) {
    if (index > n) return false;
    if (index==0 ) {
        pushBack(value);
        return true;
    }
    Node<T>* current= head;
    for (int i=0;i<index-1;i++) {
        current= current->next;
    }
    Node<T>* newNode= new Node<T>(value);
    newNode->next= current->next;
    current->next= newNode;
    ++n;
    return true;
}

template<typename T>
Node<T>* LinkedList<T>::search(const T& value) {
    Node<T>* current = head;
    while (current) {
        if (current->data == value) {
            return current;
        }
        current= current->next;
    }
    return nullptr;
}

template<typename T>
Node<T> *LinkedList<T>::getHead() const{
    return head;
}


#endif // LINKEDLIST_CPP




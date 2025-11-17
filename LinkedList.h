#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"


template <typename T>
class LinkedList
{
    public:
        /** Default constructor */
        LinkedList();

        /** Default destructor */
        virtual ~LinkedList();

        unsigned int size() const;
        bool empty() const;
        // void clear();
        // void pushFront(const T& value);
        void pushBack(const T& value);
        bool insert(unsigned int index, const T& value);
        //void remove(T& value);
        //T* elementAt(unsigned int index);
        Node<T>* search(const T& value);
        void print();
        Node<T>* getHead()const;

    private:
        Node<T>* head;
        unsigned int n;

};

#include "LinkedList.tpp"

#endif // LINKEDLIST_H

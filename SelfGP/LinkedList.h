// LinkedList for our locations

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"

class LinkedList {

private:
    Node* head;
    Node* tail;
    int size;
    void setSize(int size);
public:
    LinkedList();
    LinkedList(Node* newNode);
    void setHead(Node* head);
    Node* getHead() const;
    void setTail(Node* tail);
    Node* getTail() const;
    void pushBack(Node* newNode);
    int Size() const;

};

#endif
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
    LinkedList(Location* location);
    void setHead(Node* head);
    Node* getHead() const;
    void setTail(Node* tail);
    Node* getTail() const;
    void pushBack(Location* location);
    int Size() const;

};

#endif
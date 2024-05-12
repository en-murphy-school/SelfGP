// location node

#ifndef NODE_H
#define NODE_H

#include <string>
#include "Location.h"

class Node {
private:
    Location* location;
    Node* next;
public:
    Node();
    Node(Location* location);
    Node* getNext() const;
    void setNext(Node* setNext);
    Location* getData() const;
    void setData(Location* location);
};

#endif
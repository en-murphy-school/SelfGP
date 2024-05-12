#include "Node.h"
using namespace std;

Node::Node() {
    this->location = nullptr;
    this->next = nullptr;
}
Node::Node(Location* location) {
    this->location = location;
    this->next = nullptr;
}
Node* Node::getNext() const {
    return this->next;
}

void Node::setNext(Node* node) {
    this->next = node;
}

Location* Node::getData() const {
    return this->location;
}

void Node::setData(Location* location) {
    this->location = location;
}

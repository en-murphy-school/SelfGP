// LinkedList for our locations

#include "LinkedList.h"
using namespace std;

//Constructors
LinkedList::LinkedList() {
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
}
LinkedList::LinkedList(Location* location) {
    Node* node = new Node(location);
    this->head = node;
    this->tail = node;
    this->size = 1;
}
//End constructors

//setters & getters
void LinkedList::setSize(int newSize) {
    this->size = newSize;
}

void LinkedList::setHead(Node* newHead) {
    this->head = newHead;
}

Node* LinkedList::getHead() const {
    return this->head;
}

void LinkedList::setTail(Node* newTail) {
    this->tail = newTail;
}

Node* LinkedList::getTail() const {
    return this->tail;
}
int LinkedList::Size() const {
    return this->size;
}

//End setters and getters

//LinkedList methods
void LinkedList::pushBack(Location* location) {
    Node* newNode = new Node(location);
    if (this->head == nullptr) {
        this->head = newNode;
        this->tail = newNode;
        this->size++;
        return;
    }
    else {
        //disconnect tail and add new node
        Node* temp;
        temp = this->tail;
        this->tail = newNode;
        newNode = temp;
        newNode->setNext(this->tail);
        this->tail->setNext(nullptr);
        this->size++;
    }
}


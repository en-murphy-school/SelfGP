// LinkedList for our locations

#include "LinkedList.h"
using namespace std;

//Constructors
LinkedList::LinkedList() {
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
}
LinkedList::LinkedList(Node* newNode) {
    Node* node = new Node();
    node->setData(newNode->getData());
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
void LinkedList::pushBack(Node* newNode) {
    // Create a new node with the provided newNode as content
    Node* temp = new Node();
    temp->setData(newNode->getData());
    temp->setNext(nullptr);

    if (this->head == nullptr) {
        // If the list is empty, set both head and tail to the new node
        this->head = temp;
        this->tail = temp;
    }
    else {
        // If the list is not empty, append the new node to the end
        this->tail->setNext(temp);
        this->tail = temp;
    }
    this->size++;
}

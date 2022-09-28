#include "LinkedList.h"
#include <iostream>
#include <cstring>

LinkedList::LinkedList() {
    length = 0;
}

LinkedList::LinkedList(const LinkedList& list){  
    head = nullptr;
    tail = nullptr;
    length = 0;
    Node* listPtr = list.head;
    while(listPtr != nullptr){
        pushTail(listPtr->name, listPtr->amount);
        listPtr = listPtr->next;
    }
}

LinkedList& LinkedList::operator = (const LinkedList& list){
    delete head;
    head = nullptr;
    tail = nullptr;
    length = 0;
    Node* listPtr = list.head;
    while(listPtr != nullptr){
        pushTail(listPtr->name, listPtr->amount);
        listPtr = listPtr->next;
    }
    return *this;
}

LinkedList::LinkedList(LinkedList&& list) {
    head = nullptr;
    tail = nullptr;

    length = list.length;
    list.length = 0;
    head = list.head;
    list.head = nullptr;
    tail = list.tail;
    list.tail = nullptr;
}

LinkedList& LinkedList::operator = (LinkedList &&list) {  
    delete head;
    head = nullptr;
    tail = nullptr;
    length = 0;

    length = list.length;
    head = list.head;
    list.head = nullptr;
    tail = list.tail;
    list.tail = nullptr;
    list.length = 0;

    return *this;
}

LinkedList::~LinkedList() {
    delete head;
    head = nullptr;
}

void LinkedList::pushTail(string _name, float _amount) {
    length++;
    Node* newNode = new Node(_name, _amount);
    Node* current = head;
    if(head == nullptr){
        head = tail = newNode;
        return;
    }

    while(current->next != nullptr){
        current = current->next;
    }

    current->next = newNode;
    tail = newNode;
}

void LinkedList::updateNode(string _name, float _amount) {
    Node* current = head;
    bool contains = false;

    while(current != nullptr){
        if(current->name == _name){
            contains = true;
            break;
        }
        current = current->next;
    }

    if(contains){
        current->amount = _amount;
        return;
    }
}






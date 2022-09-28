#include "SurveyClass.h"
#include <iostream>

SurveyClass::SurveyClass() {
    members = new LinkedList();
}

SurveyClass::SurveyClass(const SurveyClass& other) {
    members = new LinkedList();
    Node* curr = other.members->head;
    while(curr != nullptr){
        handleNewRecord(curr->name, curr->amount);
        curr = curr->next;
    }
}

SurveyClass& SurveyClass::operator = (const SurveyClass& other){
    delete members;
    members = new LinkedList();
    Node* curr = other.members->head;
    while(curr != nullptr){
        handleNewRecord(curr->name, curr->amount);
        curr = curr->next;
    }
}

SurveyClass::SurveyClass(SurveyClass&& other){
    members = nullptr;

    members = move(other.members);
    other.members = nullptr;

}

SurveyClass& SurveyClass::operator = (SurveyClass&& other){
    delete members;
    members = nullptr;

    members = move(other.members);
    other.members = nullptr;
}

SurveyClass::~SurveyClass() {
    delete members;
}

void SurveyClass::handleNewRecord(string _name, float _amount) {
    Node* current = members->head;

    while(current != nullptr){
        if(current->name == _name){  //if the name exists , update it and return
            members->updateNode(_name, _amount);
            return;
        }
        current = current->next;
    }

    if(current == nullptr){  // if the name does not exist, create one in the list.
        members->pushTail(_name, _amount);
    }
}

float SurveyClass::calculateMinimumExpense() {
    if(members == nullptr || members->head == nullptr){
        return 0.0;
    }

    float min = members->head->amount;
    Node* current = members->head;

    while(current != nullptr){
        if(current->amount < min){
            min = current->amount;
        }
        current = current->next;
    }
    min *= 100;
    int temp = min;
    min = temp/100.0;

    return min;

}

float SurveyClass::calculateMaximumExpense() {
    float max = 0.0;

    Node* current = members->head;

    while(current != nullptr){
        if(current->amount > max){
            max = current->amount;
        }
        current = current->next;
    }


    max *= 100;
    int temp = max;
    max = temp/100.0;
    return max;
}

float SurveyClass::calculateAverageExpense() {
    int length = members->length;
    Node* current = members->head;
    float total = 0;
    float average = 0;
    while(current != nullptr){
        total += current->amount;
        current = current->next;
    }
    average = total/length;

    average *= 100;
    int temp = average;
    average = temp/100.0;

    return average;
}


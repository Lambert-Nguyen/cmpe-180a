#include "SinglyLinkedList.h"

SinglyLinkedList::SinglyLinkedList(){
    head = nullptr;
    listSize = 0;
}
SinglyLinkedList::SinglyLinkedList(int dataInit){
    head = new Node(dataInit);
    listSize = 1;
}
SinglyLinkedList::~SinglyLinkedList(){
    while (head != nullptr){
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    listSize = 0;
}
void SinglyLinkedList::insertAtHead(const int& data_i){
    Node* newNode = new Node(data_i);
    newNode->next = head;
    head = newNode;
    listSize++;
}
void SinglyLinkedList::insertAtTail(const int& data_i){
    Node* newNode = new Node(data_i);
    if(head == nullptr){
        head = newNode;
    } else {
        Node* currentNodePtr = head;
        while(currentNodePtr->next != nullptr){
            currentNodePtr = currentNodePtr->next;
        }
        currentNodePtr->next=newNode;
    }
    listSize++;
}
int SinglyLinkedList::size() const{
    return listSize;
}

bool SinglyLinkedList::empty() const {
    return listSize == 0;
}

void SinglyLinkedList::insertAtPosition(const int& data_i, int position_i){
    if(position_i < 0 || position_i > listSize){
        std::cerr << "ERROR: Invalid position input" << std::endl;
        throw std::out_of_range("Position out of range");
    }
    if(position_i==0){
        insertAtHead(data_i);
    } else if (position_i==listSize){
        insertAtTail(data_i);
    } else {
        Node* newNode = new Node(data_i);
        Node* currentNodePtr = head;
        for (int i = 0; i < position_i-1; i++){
            currentNodePtr = currentNodePtr->next;
        }
        newNode->next = currentNodePtr->next;
        currentNodePtr->next = newNode;
        listSize++;
    }
}
int SinglyLinkedList::getPosition(int position_i) const {
    if (position_i < 0 || position_i > listSize){
        throw std::out_of_range("Position Out of Range");
    }
    Node* currentPtr = head;
    for (int i = 0; i == position_i; i++){
        currentPtr = currentPtr->next;
    }
    return currentPtr->data;
}
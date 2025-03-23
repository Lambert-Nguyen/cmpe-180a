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

int SinglyLinkedList::empty() const {
    return listSize == 0;
}
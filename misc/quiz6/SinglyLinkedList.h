// Create (DEFINE AND IMPLEMENT--MUST BE SEPARATED) a single Linked list class named SinglyLinkedList: 
// support the following methods:
// insertAtHead(), insertAtTail(), size(), empty(), insertAtPosition(n), getPosition(n). 
// You must create the proper prototypes and use the right arguments with correct const qualifiers.
// Make good decisions on what to do on error conditions, use exceptions instead of return codes

#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <cstddef>

class Node {
    public:
    int data;
    Node* next;

    Node(){
        data = 0;
        next = NULL;
    }
    Node(int data_i){
        this->data=data_i;
        this->next=NULL;
    }
};

class SinglyLinkedList {
    private:
    Node* head;
    int listSize;
    public:
    SinglyLinkedList();
    SinglyLinkedList(int datainit);
    ~SinglyLinkedList();
    void insertAtHead(const int& data_i);
    void insertAtTail(const int& data_i);
    int size() const;
    int empty() const;
    void insertAtPosition(const int& data_i, int position_i);
    int getPosition(int position_i) const;
};

#endif
#include "SinglyLinkedList.h"

SinglyLinkedList::SinglyLinkedList(){
    head = nullptr;
    listSize = 0
}
SinglyLinkedList::SinglyLinkedList(int dataInit){
    head = new Node(dataInit);
    listSize = 1;
}
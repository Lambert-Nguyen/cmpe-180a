#include <iostream>
#include "SinglyLinkedList.h"

int main() {
    // Test the default constructor
    SinglyLinkedList list;
    std::cout << "Initial list size: " << list.size() << std::endl;
    std::cout << "Is list empty? " << (list.empty() ? "Yes" : "No") << std::endl;

    // Test insertAtHead: insert 10 and then 5
    list.insertAtHead(10);
    list.insertAtHead(5);
    std::cout << "\nAfter inserting 5 and 10 at head, list size: " << list.size() << std::endl;
    
    // Test insertAtTail: insert 20 at the tail
    list.insertAtTail(20);
    std::cout << "After inserting 20 at tail, list size: " << list.size() << std::endl;
    
    // Display list contents using getPosition()
    std::cout << "\nList contents:" << std::endl;
    for (int i = 0; i < list.size(); ++i) {
        std::cout << "Element at position " << i << ": " << list.getPosition(i) << std::endl;
    }
    
    // Test insertAtPosition: insert 15 at position 1
    list.insertAtPosition(15, 1);
    std::cout << "\nAfter inserting 15 at position 1, list size: " << list.size() << std::endl;
    std::cout << "Updated list contents:" << std::endl;
    for (int i = 0; i < list.size(); ++i) {
        std::cout << "Element at position " << i << ": " << list.getPosition(i) << std::endl;
    }

    // Test the parameterized constructor which creates a list with one node
    SinglyLinkedList list2(100);
    std::cout << "\nList2 created with initial value 100:" << std::endl;
    std::cout << "List2 size: " << list2.size() << std::endl;
    std::cout << "Element at position 0 in list2: " << list2.getPosition(0) << std::endl;

    return 0;
}

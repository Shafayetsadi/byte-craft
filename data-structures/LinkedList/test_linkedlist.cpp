#include "linked_list.h"

void testLinkedList() {
    LinkedList<int> myList;

    myList.push_front(10);
    myList.push_front(20);
    myList.push_front(30);
    std::cout << "After insertion at the beginning(30, 20, 10): ";
    myList.print();

    myList.push_back(40);
    myList.push_back(50);
    std::cout << "After insertion at the end(30, 20, 10, 40, 50): ";
    myList.print();

    myList.insert(35, 3);
    std::cout << "After insertion at position 3: (30, 20, 10, 35, 40, 50): ";
    myList.print();

    std::cout << "Popping from the beginning(30): " << myList.pop_front() << std::endl;
    myList.print();

    std::cout << "Popping from the end(50): " << myList.pop_back() << std::endl;
    myList.print();

    int pos = myList.find(10);
    if (pos != -1) {
        std::cout << "Element 10 found at position: " << pos << std::endl;
    } else {
        std::cout << "Element not found" << std::endl;
    }

    pos = myList.find(100);
    if (pos != -1) {
        std::cout << "Element 100 found at position: " << pos << std::endl;
    } else {
        std::cout << "Element 100 not found" << std::endl;
    }

    while (!myList.empty()) {
        std::cout << "pop_front(): " << myList.pop_front() << std::endl;
    }
    std::cout << "List after popping all elements: ";
    myList.print();
}

int main() {
    testLinkedList();
    return 0;
}

#ifndef LinkedList_H
#define LinkedList_H
#include <cassert>
#include <iostream>

// Node structure for a generic linked list
template <typename T> struct Node {
    T data;
    Node<T> *next; // self referential structure
    Node(T data) : data(data), next(nullptr) {}
};

template <typename T> class LinkedList {
private:
    Node<T> *head;

public:
    LinkedList() : head(nullptr) {}

    void  push_front(const T &data) {
        Node<T> *temp = new Node<T>(data);
        temp->next = head;
        head = temp;
    }

    void push_back(const T &data) {
        if (!head) {
            head = new Node<T>(data);
            return;
        }
        Node<T> *curr = head;
        while (curr->next) {
            curr = curr->next;
        }
        curr->next = new Node<T>(data);
    }

    void insert(const T &data, const int &pos) {
        if(pos == 0) {
            push_front(data);
            return;
        }
        Node<T> *curr = head;
        for(int i=0; i<pos-1 and curr != nullptr; i++) {
            curr = curr->next;
        }
        if(curr == nullptr) {
            std::cerr << "Out of bounds\n";
            return;
        }
        Node<T> *temp = new Node<T>(data);
        temp->next = curr->next;
        curr->next = temp;
    }

    T pop_front() {
        assert(head != nullptr and "List is empty");
        Node<T> *temp = head;
        T data = head->data;
        head = head->next;
        delete temp;
        return data;
    }

    T pop_back() {
        assert(head != nullptr and "List is empty");
        if(head->next == nullptr) {
            T data = head->data;
            delete head;
            head = nullptr;
            return data;
        }
        Node<T> *curr = head;
        while (curr->next->next != nullptr) {
            curr = curr->next;
        }
        Node<T> *temp = curr->next;
        T data = temp->data;
        delete temp;
        curr->next = nullptr;
        return data;
    }

    int find(const T &key) {
        int pos = 0;
        Node<T> *curr = head;
        while (curr != nullptr) {
            if(curr->data == key) {
                return pos;
            }
            else {
                pos++;
                curr = curr->next;
            }
        }
        return -1;
    }

    bool empty() {
        return head == nullptr;
    }

    void print() const {
        Node<T> *curr = head;
        while (curr) {
            std::cout << curr->data << " ";
            curr = curr->next;
        }
        std::cout << std::endl;
    }

    ~LinkedList() {
        Node<T> *temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

#endif

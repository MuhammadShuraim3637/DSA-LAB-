#include <iostream>
using namespace std;
class Node {
public:
    int value;
    Node* next;

    Node(int val) {
        value = val;
        next = nullptr;
    }
};
class LinkedList {
public:
    Node* head;

    LinkedList() {
        head = nullptr;
    }

    void insert_at_start(int val) {
        Node* newnode = new Node(val);
        newnode->next = head;
        head = newnode;
    }

    void insert_at_last(int val) {
        Node* newnode = new Node(val);
        if (head == nullptr) {
            head = newnode;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newnode;
    }

    void display() {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->value << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};

int main() {
    LinkedList obj;
    obj.insert_at_start(1);
    obj.display();
    obj.insert_at_last(4);
    obj.display();
    return 0;
}

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
    void delete_at_start() {
        if (head == nullptr) {
            cout << "List is already empty.\n";
            return;
        }
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    void delete_at_end() {
        if (head == nullptr) {
            cout << "List is already empty.\n";
            return;
        }
        if (head->next == nullptr) {  
            delete head;
            head = nullptr;
            return;
        }
        Node* temp = head;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
    }
    void delete_nth_node(int n) {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }
        if (n == 1) {
            delete_at_start();
            return;
        }

        Node* temp = head;
        for (int i = 1; temp != nullptr && i < n - 1; i++) {
            temp = temp->next;
        }

        if (temp == nullptr || temp->next == nullptr) {
            cout << "Invalid position!\n";
            return;
        }

        Node* node_to_delete = temp->next;
        temp->next = temp->next->next;
        delete node_to_delete;
    }
    void delete_middle_node() {
        if (head == nullptr || head->next == nullptr) {
            delete_at_start();
            return;
        }

        Node* turtle = head;
        Node* tiger= head;
        Node* prev = nullptr;

        while (tiger != nullptr && tiger->next != nullptr) {
            prev = turtle;
            turtle = turtle->next;
            tiger = tiger->next->next;
        }

        prev->next = turtle->next;
        delete turtle;
    }
    void display() {
        if (head == nullptr) {
            cout << "LIST IS EMPTY\n";
            return;
        }
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->value << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
};

int main() {
    LinkedList list;
    list.insert_at_start(10);
    list.insert_at_start(20);
    list.insert_at_start(30);
    list.insert_at_start(40);
    list.insert_at_start(50);

    cout << "Original List: ";
    list.display();

 
    list.delete_at_start();
    cout << "After deleting first node: ";
    list.display();

    list.delete_at_end();
    cout << "After deleting last node: ";
    list.display();

    
    list.delete_nth_node(2);
    cout << "After deleting 2nd node: ";
    list.display();

    list.delete_middle_node();
    cout << "After deleting middle node: ";
    list.display();

    return 0;
}

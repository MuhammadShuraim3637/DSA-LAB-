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

    void insert_at_any_pos(int pos, int value) {
        if (pos < 1) { 
            cout << "Invalid Position!" << endl;
            return;
        }

        Node* newnode = new Node(value);

        if (pos == 1) { 
            newnode->next = head;
            head = newnode;
            return;
        }

        Node* temp = head;
        int count = 1;

        while (temp != nullptr && count < pos - 1) { 
            temp = temp->next;
            count++;
        }

        if (temp == nullptr) { 
            cout << "Invalid Position!" << endl;
            delete newnode; 
            return;
        }

        newnode->next = temp->next;
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
    LinkedList list;

    list.insert_at_any_pos(1, 5);
    list.insert_at_any_pos(2, 10); 
    list.insert_at_any_pos(3, 15); 
    list.insert_at_any_pos(2, 20); 
    list.insert_at_any_pos(10, 25);
    list.display();

    return 0;
}

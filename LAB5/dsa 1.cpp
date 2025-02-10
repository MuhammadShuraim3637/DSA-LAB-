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

    void display_first_node() {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
        }
        else {
            cout << "First Node: " << head->value << endl;
        }
    }

    void display_last_node() {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        cout << "Last Node: " << temp->value << endl;
    }

    void display_nth_node(int n) {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }
        Node* temp = head;
        int count = 1;
        while (temp != nullptr) {
            if (count == n) {
                cout << "Nth Node (" << n << "): " << temp->value << endl;
                return;
            }
            temp = temp->next;
            count++;
        }
        cout << "Position " << n << " is out of range!" << endl;
    }

    void display_center_node() {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }
        Node* turtle = head;
        Node* tiger = head;

        while (tiger != nullptr && tiger->next != nullptr) {
            turtle = turtle->next;
            tiger = tiger->next->next;
        }

        cout << "Center Node: " << turtle->value << endl;
    }
};

int main() {
    LinkedList obj;

    obj.insert_at_last(1);
    obj.insert_at_last(2);
    obj.insert_at_last(3);
    obj.insert_at_last(4);
    obj.insert_at_last(5);

    obj.display();

    obj.display_first_node();
    obj.display_last_node();
    obj.display_nth_node(3); 
    obj.display_center_node();  

    return 0;
}

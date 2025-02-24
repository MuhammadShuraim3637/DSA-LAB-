#include <iostream>
using namespace std;
class Node {
public:
    int data;
    Node* next;
    Node(int d) {
        data = d;
        next = nullptr;
    }
};
class LinkedList {
public:
    Node* head;

    LinkedList() {
        head = nullptr;
    }
    void insert_at_end(int data) {
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void display() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};

Node* merge(Node* head1, Node* head2) {
    if (!head1) return head2;
    if (!head2) return head1;

    if (head1->data < head2->data) {
        head1->next = merge(head1->next, head2);
        return head1;
    }
    else {
        head2->next = merge(head1, head2->next);
        return head2;
    }
}

int main() {
    LinkedList list1, list2;
    list1.insert_at_end(6);
    list1.insert_at_end(5);
    list1.insert_at_end(4);
    list2.insert_at_end(3);
    list2.insert_at_end(2);
    list2.insert_at_end(1);

    cout << "First Linked List: ";
    list1.display();

    cout << "Second Linked List: ";
    list2.display();

    LinkedList mergedList;
    mergedList.head = merge(list1.head, list2.head);

    cout << "Merged Linked List: ";
    mergedList.display();

    return 0;
}

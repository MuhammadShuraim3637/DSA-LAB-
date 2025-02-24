#include <iostream>
using namespace std;
class Node {
public:
    int data;
    Node* next;
    Node* prev;

    Node(int d) {
        data = d;
        next = nullptr;
        prev = nullptr;
    }
};

class DoublyLinkedList {
public:
    Node* head;

    DoublyLinkedList() {
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
            newNode->prev = temp;
        }
    }
    void display() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " <-> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};

Node* merge(Node* head1, Node* head2) {
    if (!head1) return head2;
    if (!head2) return head1;

    Node* mergedHead = nullptr;
    if (head1->data < head2->data) {
        mergedHead = head1;
        head1 = head1->next;
    }
    else {
        mergedHead = head2;
        head2 = head2->next;
    }

    Node* temp = mergedHead;
    while (head1 && head2) {
        if (head1->data < head2->data) {
            temp->next = head1;
            head1->prev = temp;
            head1 = head1->next;
        }
        else {
            temp->next = head2;
            head2->prev = temp;
            head2 = head2->next;
        }
        temp = temp->next;
    }

    if (head1) temp->next = head1, head1->prev = temp;
    if (head2) temp->next = head2, head2->prev = temp;

    return mergedHead;
}

int main() {
    DoublyLinkedList list1, list2;
    list1.insert_at_end(1);
    list1.insert_at_end(3);
    list1.insert_at_end(5);
    list2.insert_at_end(2);
    list2.insert_at_end(4);
    list2.insert_at_end(6);

    cout << "First Doubly Linked List: ";
    list1.display();

    cout << "Second Doubly Linked List: ";
    list2.display();
    DoublyLinkedList mergedList;
    mergedList.head = merge(list1.head, list2.head);

    cout << "Merged Doubly Linked List: ";
    mergedList.display();

    return 0;
}

#include <iostream>
using namespace std;
class QueueArray {
private:
    int front, rear;
    int arr[100];
    int size;

public:
    QueueArray(int s = 100) {
        size = s;
        front = rear = -1;
    }

    void enqueue(int val) {
        if (rear == size - 1) {
            cout << "Queue Overflow\n";
            return;
        }
        if (front == -1) front = 0;
        arr[++rear] = val;
    }

    void dequeue() {
        if (front == -1 || front > rear) {
            cout << "Queue Underflow\n";
            return;
        }
        front++;
    }

    void display() {
        if (front == -1 || front > rear) {
            cout << "Queue is empty\n";
            return;
        }
        cout << "Queue: ";
        for (int i = front; i <= rear; i++) {
            cout << arr[i] << " ";
        }
        cout << "\n";
    }
};

int main() {
    QueueArray qa;

    qa.enqueue(10);
    qa.enqueue(20);
    qa.enqueue(30);
    qa.display();

    qa.dequeue();
    qa.display();

    return 0;
}

#include <iostream>
using namespace std;

class StackArray {
private:
    int top;
    int arr[100]; 
    int size;

public:
    StackArray(int s = 100) {
        top = -1;
        size = s;
    }

    void push(int val) {
        if (top == size - 1) {
            cout << "Stack Overflow\n";
            return;
        }
        arr[++top] = val;
    }

    void pop() {
        if (top == -1) {
            cout << "Stack Underflow\n";
            return;
        }
        top--;
    }

    void display() {
        if (top == -1) {
            cout << "Stack is empty\n";
            return;
        }
        cout << "Stack (Top -> Bottom): ";
        for (int i = top; i >= 0; i--) {
            cout << arr[i] << " ";
        }
        cout << "\n";
    }
};

int main() {
    StackArray sa;

    sa.push(10);
    sa.push(20);
    sa.push(30);
    sa.display();

    sa.pop();
    sa.display();

    return 0;
}

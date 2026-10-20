#include <iostream>
using namespace std;

#define SIZE 5

class BankQueue {
    int items[SIZE];
    int front, rear;

public:
    BankQueue() {
        front = -1;
        rear = -1;
    }

    bool isFull() {
        return rear == SIZE - 1;
    }

    bool isEmpty() {
        return front == -1 || front > rear;
    }

    void enqueue(int token) {
        if (isFull()) {
            cout << "Queue Overflow! Cannot add customer " << token << ".\n";
            return;
        }
        if (front == -1) front = 0;
        rear++;
        items[rear] = token;
        cout << "Customer token " << token << " inserted.\n";
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow! No waiting customers to serve.\n";
            return;
        }
        cout << "Serving customer token " << items[front] << ".\n";
        front++;
    }

    void display() {
        if (isEmpty()) {
            cout << "No waiting customers.\n";
            return;
        }
        cout << "Waiting customers: ";
        for (int i = front; i <= rear; i++) {
            cout << items[i] << " ";
        }
        cout << "\n";
    }

    void countWaiting() {
        if (isEmpty()) {
            cout << "Total waiting customers: 0\n";
        } else {
            cout << "Total waiting customers: " << (rear - front + 1) << "\n";
        }
    }
};

int main() {
    BankQueue q;
    q.enqueue(101);
    q.enqueue(102);
    q.enqueue(103);

    q.display();
    q.countWaiting();

    q.dequeue();

    q.display();
    q.countWaiting();

    return 0;
}

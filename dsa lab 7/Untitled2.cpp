#include <iostream>
using namespace std;

#define SIZE 5

class CircularQueue {
    int items[SIZE];
    int front, rear;

public:
    CircularQueue() {
        front = -1;
        rear = -1;
    }

    bool isFull() {
        return (front == 0 && rear == SIZE - 1) || (front == rear + 1);
    }

    bool isEmpty() {
        return front == -1;
    }

    void enqueue(int packetId) {
        if (isFull()) {
            cout << "Buffer Full! Cannot insert packet " << packetId << ".\n";
            return;
        }
        if (front == -1) front = 0;
        rear = (rear + 1) % SIZE;
        items[rear] = packetId;
        cout << "Packet " << packetId << " inserted.\n";
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Buffer Empty! No packets to transmit.\n";
            return;
        }
        cout << "Transmitted packet " << items[front] << ".\n";
        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            front = (front + 1) % SIZE;
        }
    }

    void display() {
        if (isEmpty()) {
            cout << "Buffer is empty.\n";
            return;
        }
        cout << "Packets waiting for transmission: ";
        int i = front;
        while (true) {
            cout << items[i] << " ";
            if (i == rear) break;
            i = (i + 1) % SIZE;
        }
        cout << "\n";
    }
};

int main() {
    CircularQueue cq;
    cq.enqueue(201);
    cq.enqueue(202);
    cq.enqueue(203);

    cq.display();

    cq.dequeue();

    cq.display();

    cq.enqueue(204);
    cq.enqueue(205);
    cq.enqueue(206);

    cq.display();

    return 0;
}

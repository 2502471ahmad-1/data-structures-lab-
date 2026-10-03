#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string website;
    Node* prev;
    Node* next;
    Node(string name) {
        website = name;
        prev = nullptr;
        next = nullptr;
    }
};

class BrowserHistory {
private:
    Node* head;
    Node* tail;
public:
    BrowserHistory() {
        head = nullptr;
        tail = nullptr;
    }
    void addWebsite(string website) {
        Node* newNode = new Node(website);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    void displayForward() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->website << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    void displayBackward() {
        Node* temp = tail;
        while (temp != nullptr) {
            cout << temp->website << " ";
            temp = temp->prev;
        }
        cout << endl;
    }
};

int main() {
    BrowserHistory history;
    history.addWebsite("google.com");
    history.addWebsite("github.com");
    history.addWebsite("stackoverflow.com");
    history.addWebsite("wikipedia.org");
    history.addWebsite("youtube.com");
    history.displayForward();
    history.displayBackward();
    return 0;
}
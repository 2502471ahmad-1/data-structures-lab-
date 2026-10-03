#include <iostream>
#include <string>
using namespace std;

class PlayerNode {
public:
    string playerName;
    PlayerNode* next;
    PlayerNode(string name) {
        playerName = name;
        next = nullptr;
    }
};

class GameTurns {
private:
    PlayerNode* head;
    PlayerNode* tail;
public:
    GameTurns() {
        head = nullptr;
        tail = nullptr;
    }
    void addPlayer(string name) {
        PlayerNode* newNode = new PlayerNode(name);
        if (head == nullptr) {
            head = tail = newNode;
            newNode->next = head;
        } else {
            tail->next = newNode;
            tail = newNode;
            tail->next = head;
        }
    }
    void displayTurns() {
        if (head == nullptr) return;
        PlayerNode* temp = head;
        do {
            cout << temp->playerName << " ";
            temp = temp->next;
        } while (temp != head);
        cout << endl;
        cout << "After " << tail->playerName << " -> " << tail->next->playerName << endl;
    }
};

int main() {
    GameTurns game;
    game.addPlayer("Alice");
    game.addPlayer("Bob");
    game.addPlayer("Charlie");
    game.addPlayer("Diana");
    game.addPlayer("Ethan");
    game.displayTurns();
    return 0;
}
#include <iostream>
#include <string>
using namespace std;

class SongNode {
public:
    string songTitle;
    SongNode* next;
    SongNode(string title) {
        songTitle = title;
        next = nullptr;
    }
};

class MusicPlaylist {
private:
    SongNode* head;
    SongNode* tail;
    int count;
public:
    MusicPlaylist() {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }
    void addSong(string title) {
        SongNode* newNode = new SongNode(title);
        if (head == nullptr) {
            head = tail = newNode;
            newNode->next = head;
        } else {
            tail->next = newNode;
            tail = newNode;
            tail->next = head;
        }
        count++;
    }
    void displayOnce() {
        if (head == nullptr) return;
        SongNode* temp = head;
        do {
            cout << temp->songTitle << " ";
            temp = temp->next;
        } while (temp != head);
        cout << endl;
    }
    void simulateRounds(int rounds) {
        if (head == nullptr) return;
        SongNode* temp = head;
        int total = count * rounds;
        for (int i = 0; i < total; i++) {
            cout << temp->songTitle << endl;
            temp = temp->next;
        }
    }
};

int main() {
    MusicPlaylist playlist;
    playlist.addSong("Song 1");
    playlist.addSong("Song 2");
    playlist.addSong("Song 3");
    playlist.addSong("Song 4");
    playlist.addSong("Song 5");
    playlist.displayOnce();
    playlist.simulateRounds(2);
    return 0;
}
#include <iostream>
#include <string>
using namespace std;

class ImageNode {
public:
    string imageName;
    ImageNode* prev;
    ImageNode* next;
    ImageNode(string name) {
        imageName = name;
        prev = nullptr;
        next = nullptr;
    }
};

class ImageGallery {
private:
    ImageNode* head;
    ImageNode* tail;
public:
    ImageGallery() {
        head = nullptr;
        tail = nullptr;
    }
    void addImage(string name) {
        ImageNode* newNode = new ImageNode(name);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    void displayForward() {
        ImageNode* temp = head;
        while (temp != nullptr) {
            cout << temp->imageName << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    void displayBackward() {
        ImageNode* temp = tail;
        while (temp != nullptr) {
            cout << temp->imageName << " ";
            temp = temp->prev;
        }
        cout << endl;
    }
};

int main() {
    ImageGallery gallery;
    gallery.addImage("sunset.jpg");
    gallery.addImage("mountains.png");
    gallery.addImage("beach.jpg");
    gallery.addImage("forest.png");
    gallery.addImage("cityline.jpg");
    gallery.displayForward();
    gallery.displayBackward();
    return 0;
}
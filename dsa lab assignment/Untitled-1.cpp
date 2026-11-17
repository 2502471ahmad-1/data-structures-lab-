#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Node {
public:
    int flight_no;
    string destination;
    string departure_time;
    Node* left;
    Node* right;

    Node(int f, string d, string t) {
        flight_no = f;
        destination = d;
        departure_time = t;
        left = nullptr;
        right = nullptr;
    }
};

class FlightBST {
private:
    Node* root;

    Node* insert(Node* node, int f, string d, string t) {
        if (node == nullptr) return new Node(f, d, t);
        if (f < node->flight_no)
            node->left = insert(node->left, f, d, t);
        else if (f > node->flight_no)
            node->right = insert(node->right, f, d, t);
        return node;
    }

    Node* search(Node* node, int f) {
        if (node == nullptr || node->flight_no == f) return node;
        if (f < node->flight_no) return search(node->left, f);
        return search(node->right, f);
    }

    Node* minNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node* node, int f) {
        if (node == nullptr) return node;
        if (f < node->flight_no)
            node->left = deleteNode(node->left, f);
        else if (f > node->flight_no)
            node->right = deleteNode(node->right, f);
        else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = minNode(node->right);
            node->flight_no = temp->flight_no;
            node->destination = temp->destination;
            node->departure_time = temp->departure_time;
            node->right = deleteNode(node->right, temp->flight_no);
        }
        return node;
    }

    void inorder(Node* node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << "Flight: " << node->flight_no << " | Dest: " << node->destination << " | Time: " << node->departure_time << endl;
            inorder(node->right);
        }
    }

    void preorder(Node* node) {
        if (node != nullptr) {
            cout << "Flight: " << node->flight_no << " | Dest: " << node->destination << " | Time: " << node->departure_time << endl;
            preorder(node->left);
            preorder(node->right);
        }
    }

    void postorder(Node* node) {
        if (node != nullptr) {
            postorder(node->left);
            postorder(node->right);
            cout << "Flight: " << node->flight_no << " | Dest: " << node->destination << " | Time: " << node->departure_time << endl;
        }
    }

    int countFlights(Node* node) {
        if (node == nullptr) return 0;
        return 1 + countFlights(node->left) + countFlights(node->right);
    }

    int height(Node* node) {
        if (node == nullptr) return -1;
        return 1 + max(height(node->left), height(node->right));
    }

    void displayTree(Node* node, int level, string prefix) {
        if (node != nullptr) {
            cout << string(level * 4, ' ') << prefix << node->flight_no << " (" << node->destination << ")" << endl;
            if (node->left != nullptr || node->right != nullptr) {
                displayTree(node->left, level + 1, "L--- ");
                displayTree(node->right, level + 1, "R--- ");
            }
        }
    }

public:
    FlightBST() { root = nullptr; }

    void insert(int f, string d, string t) { root = insert(root, f, d, t); }
    Node* search(int f) { return search(root, f); }
    void remove(int f) { root = deleteNode(root, f); }
    void inorder() { inorder(root); }
    void preorder() { preorder(root); }
    void postorder() { postorder(root); }
    int countFlights() { return countFlights(root); }
    int height() { return height(root); }
    void displayTree() { displayTree(root, 0, "Root: "); }

    Node* findMin() {
        if (root == nullptr) return nullptr;
        return minNode(root);
    }

    Node* findMax() {
        if (root == nullptr) return nullptr;
        Node* current = root;
        while (current->right != nullptr)
            current = current->right;
        return current;
    }
};

int main() {
    FlightBST bst;
    bst.insert(500, "London", "08:00");
    bst.insert(300, "Dubai", "09:15");
    bst.insert(700, "New York", "10:30");
    bst.insert(200, "Istanbul", "11:00");
    bst.insert(400, "Doha", "12:20");
    bst.insert(600, "Toronto", "13:45");
    bst.insert(800, "Tokyo", "14:10");
    bst.insert(150, "Riyadh", "15:00");
    bst.insert(250, "Paris", "16:30");
    bst.insert(350, "Frankfurt", "17:40");
    bst.insert(650, "Sydney", "19:00");
    bst.insert(850, "Beijing", "21:15");

    cout << "--- In-order Traversal ---" << endl;
    bst.inorder();

    cout << "\n--- Pre-order Traversal ---" << endl;
    bst.preorder();

    cout << "\n--- Post-order Traversal ---" << endl;
    bst.postorder();

    Node* found = bst.search(400);
    if (found)
        cout << "\nSearch 400: " << found->flight_no << " -> " << found->destination << " at " << found->departure_time << endl;
    else
        cout << "\nSearch 400: Not Found" << endl;

    Node* minF = bst.findMin();
    Node* maxF = bst.findMax();
    cout << "Minimum Flight: " << minF->flight_no << " (" << minF->destination << ")" << endl;
    cout << "Maximum Flight: " << maxF->flight_no << " (" << maxF->destination << ")" << endl;
    cout << "Total Flights: " << bst.countFlights() << endl;
    cout << "Tree Height: " << bst.height() << endl;

    bst.remove(150);
    bst.remove(800);
    bst.remove(500);

    cout << "\n--- Final BST Structure After Deletions (150, 800, 500) ---" << endl;
    bst.displayTree();

    return 0;
}
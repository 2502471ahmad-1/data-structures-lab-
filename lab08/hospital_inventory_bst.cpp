#include <iostream>
#include <algorithm>
using namespace std;

class Node {
public:
    int id;
    Node* left;
    Node* right;

    Node(int val) : id(val), left(nullptr), right(nullptr) {}
};

class HospitalBST {
private:
    Node* root;

    Node* insert(Node* node, int id) {
        if (node == nullptr) {
            cout << "ID " << id << " inserted successfully.\n";
            return new Node(id);
        }
        if (id < node->id) {
            node->left = insert(node->left, id);
        } else if (id > node->id) {
            node->right = insert(node->right, id);
        } else {
            cout << "Error: Duplicate ID " << id << " rejected!\n";
        }
        return node;
    }

    bool search(Node* node, int target) {
        if (node == nullptr) return false;
        if (node->id == target) return true;
        if (target < node->id) return search(node->left, target);
        return search(node->right, target);
    }

    Node* findMin(Node* node) {
        while (node && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* remove(Node* node, int id, bool& deleted) {
        if (node == nullptr) return nullptr;

        if (id < node->id) {
            node->left = remove(node->left, id, deleted);
        } else if (id > node->id) {
            node->right = remove(node->right, id, deleted);
        } else {
            deleted = true;
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = findMin(node->right);
            node->id = temp->id;
            node->right = remove(node->right, temp->id, deleted);
        }
        return node;
    }

    void inOrder(Node* node) {
        if (node == nullptr) return;
        inOrder(node->left);
        cout << node->id << " ";
        inOrder(node->right);
    }

    void preOrder(Node* node) {
        if (node == nullptr) return;
        cout << node->id << " ";
        preOrder(node->left);
        preOrder(node->right);
    }

    void postOrder(Node* node) {
        if (node == nullptr) return;
        postOrder(node->left);
        postOrder(node->right);
        cout << node->id << " ";
    }

    int countNodes(Node* node) {
        if (node == nullptr) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    int getHeight(Node* node) {
        if (node == nullptr) return -1;
        return 1 + max(getHeight(node->left), getHeight(node->right));
    }

    void destroy(Node* node) {
        if (node == nullptr) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    HospitalBST() : root(nullptr) {}
    ~HospitalBST() { destroy(root); }

    void insert(int id) { root = insert(root, id); }

    void search(int id) {
        if (search(root, id)) {
            cout << "Record ID " << id << " exists in the system.\n";
        } else {
            cout << "Record ID " << id << " DOES NOT exist.\n";
        }
    }

    void remove(int id) {
        if (root == nullptr) {
            cout << "Cannot delete from an empty tree!\n";
            return;
        }
        bool deleted = false;
        root = remove(root, id, deleted);
        if (deleted) {
            cout << "ID " << id << " deleted successfully.\nUpdated Tree (In-Order): ";
            displayInOrder();
        } else {
            cout << "ID " << id << " not found. No deletion performed.\n";
        }
    }

    void displayInOrder() {
        if (!root) { cout << "Tree is empty.\n"; return; }
        inOrder(root); cout << "\n";
    }

    void displayPreOrder() {
        if (!root) { cout << "Tree is empty.\n"; return; }
        preOrder(root); cout << "\n";
    }

    void displayPostOrder() {
        if (!root) { cout << "Tree is empty.\n"; return; }
        postOrder(root); cout << "\n";
    }

    int getCount() { return countNodes(root); }
    int getHeight() { return getHeight(root); }
};

int main() {
    HospitalBST tree;
    int initial[] = {55, 35, 75, 25, 45, 65, 85, 40, 50};
    cout << "Initializing tree with default IDs...\n";
    for (int id : initial) {
        tree.insert(id);
    }

    int choice, val;
    do {
        cout << "\n--- Hospital Inventory Management Menu ---\n";
        cout << "1. Insert an ID\n2. Search for an ID\n3. Delete an ID\n";
        cout << "4. Display In-Order Traversal\n5. Display Pre-Order Traversal\n6. Display Post-Order Traversal\n";
        cout << "7. Count Total Nodes\n8. Calculate Height of BST\n9. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter ID to insert: ";
                cin >> val;
                tree.insert(val);
                break;
            case 2:
                cout << "Enter ID to search: ";
                cin >> val;
                tree.search(val);
                break;
            case 3:
                cout << "Enter ID to delete: ";
                cin >> val;
                tree.remove(val);
                break;
            case 4:
                cout << "In-Order Traversal: ";
                tree.displayInOrder();
                break;
            case 5:
                cout << "Pre-Order Traversal: ";
                tree.displayPreOrder();
                break;
            case 6:
                cout << "Post-Order Traversal: ";
                tree.displayPostOrder();
                break;
            case 7:
                cout << "Total Nodes: " << tree.getCount() << "\n";
                break;
            case 8:
                cout << "Tree Height: " << tree.getHeight() << "\n";
                break;
            case 9:
                cout << "Exiting system. Memory cleaned up.\n";
                break;
            default:
                cout << "Invalid choice! Please enter a number between 1 and 9.\n";
        }
    } while (choice != 9);

    return 0;
}
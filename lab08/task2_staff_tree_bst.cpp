#include <iostream>
#include <string>
using namespace std;

class GeneralNode {
public:
    string name;
    GeneralNode* left;
    GeneralNode* right;

    GeneralNode(string val) : name(val), left(nullptr), right(nullptr) {}
};

void displayGeneralTree(GeneralNode* root) {
    if (root == nullptr) return;

    cout << "Staff Member: " << root->name << "\n";
    cout << "  Left Child:  " << (root->left ? root->left->name : "NULL") << "\n";
    cout << "  Right Child: " << (root->right ? root->right->name : "NULL") << "\n\n";

    displayGeneralTree(root->left);
    displayGeneralTree(root->right);
}

class BSTNode {
public:
    int id;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int val) : id(val), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root;

    BSTNode* insert(BSTNode* node, int id) {
        if (node == nullptr) {
            return new BSTNode(id);
        }
        if (id < node->id) {
            node->left = insert(node->left, id);
        } else if (id > node->id) {
            node->right = insert(node->right, id);
        } else {
            cout << "Duplicate ID (" << id << ") rejected.\n";
        }
        return node;
    }

    bool search(BSTNode* node, int target, int& visits) {
        if (node == nullptr) return false;
        visits++;
        if (node->id == target) return true;
        if (target < node->id) return search(node->left, target, visits);
        return search(node->right, target, visits);
    }

    BSTNode* findMin(BSTNode* node) {
        while (node && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    BSTNode* remove(BSTNode* node, int id) {
        if (node == nullptr) return nullptr;

        if (id < node->id) {
            node->left = remove(node->left, id);
        } else if (id > node->id) {
            node->right = remove(node->right, id);
        } else {
            if (node->left == nullptr) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }
            BSTNode* temp = findMin(node->right);
            node->id = temp->id;
            node->right = remove(node->right, temp->id);
        }
        return node;
    }

    void inOrder(BSTNode* node) {
        if (node == nullptr) return;
        inOrder(node->left);
        cout << node->id << " ";
        inOrder(node->right);
    }

    void destroyTree(BSTNode* node) {
        if (node == nullptr) return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { destroyTree(root); }

    void insert(int id) { root = insert(root, id); }
    void remove(int id) { root = remove(root, id); }

    void searchAndPrint(int id) {
        int visits = 0;
        bool found = search(root, id, visits);
        if (found) {
            cout << "ID " << id << " FOUND in the BST (Visits: " << visits << ")\n";
        } else {
            cout << "ID " << id << " NOT FOUND in the BST (Visits: " << visits << ")\n";
        }
    }

    void displayInOrder() {
        cout << "In-Order Traversal: ";
        inOrder(root);
        cout << "\n";
    }
};

int main() {
    cout << "=== GENERAL BINARY TREE (STAFF) ===\n";
    GeneralNode* root = new GeneralNode("Alice");
    root->left = new GeneralNode("Bob");
    root->right = new GeneralNode("Charlie");
    root->left->left = new GeneralNode("David");
    root->left->right = new GeneralNode("Eve");
    root->right->left = new GeneralNode("Frank");
    root->right->right = new GeneralNode("Grace");

    displayGeneralTree(root);

    cout << "=== BINARY SEARCH TREE (STAFF IDs) ===\n";
    BST bst;
    int initialIDs[] = {48, 28, 68, 18, 38, 58, 78};
    for (int id : initialIDs) {
        bst.insert(id);
    }

    cout << "\nInserting 3 user input IDs:\n";
    for (int i = 0; i < 3; i++) {
        int val;
        cout << "Enter Staff ID to insert: ";
        cin >> val;
        bst.insert(val);
    }

    cout << "\n--- Searching Test Cases ---\n";
    bst.searchAndPrint(38);
    bst.searchAndPrint(99);
    bst.searchAndPrint(5);

    cout << "\n--- Deletion Tests ---\n";
    cout << "Enter a Staff ID to delete: ";
    int delID;
    cin >> delID;
    bst.remove(delID);
    bst.displayInOrder();

    return 0;
}
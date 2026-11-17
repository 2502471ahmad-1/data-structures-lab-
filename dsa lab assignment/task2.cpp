#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

class AVLNode {
public:
    int emergency_id;
    string location;
    string severity;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int id, string loc, string sev) {
        emergency_id = id;
        location = loc;
        severity = sev;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class EmergencyAVL {
private:
    AVLNode* root;

    int getHeight(AVLNode* node) {
        if (node == nullptr) return 0;
        return node->height;
    }

    int getBalance(AVLNode* node) {
        if (node == nullptr) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        return y;
    }

    AVLNode* insert(AVLNode* node, int id, string loc, string sev) {
        if (node == nullptr) return new AVLNode(id, loc, sev);
        if (id < node->emergency_id)
            node->left = insert(node->left, id, loc, sev);
        else if (id > node->emergency_id)
            node->right = insert(node->right, id, loc, sev);
        else
            return node;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        if (balance > 1 && id < node->left->emergency_id)
            return rightRotate(node);
        if (balance < -1 && id > node->right->emergency_id)
            return leftRotate(node);
        if (balance > 1 && id > node->left->emergency_id) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && id < node->right->emergency_id) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    AVLNode* minNode(AVLNode* node) {
        AVLNode* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    AVLNode* deleteNode(AVLNode* node, int id) {
        if (node == nullptr) return node;
        if (id < node->emergency_id)
            node->left = deleteNode(node->left, id);
        else if (id > node->emergency_id)
            node->right = deleteNode(node->right, id);
        else {
            if (node->left == nullptr || node->right == nullptr) {
                AVLNode* temp = node->left ? node->left : node->right;
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                AVLNode* temp = minNode(node->right);
                node->emergency_id = temp->emergency_id;
                node->location = temp->location;
                node->severity = temp->severity;
                node->right = deleteNode(node->right, temp->emergency_id);
            }
        }

        if (node == nullptr) return node;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0)
            return rightRotate(node);
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && getBalance(node->right) <= 0)
            return leftRotate(node);
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    AVLNode* search(AVLNode* node, int id) {
        if (node == nullptr || node->emergency_id == id) return node;
        if (id < node->emergency_id) return search(node->left, id);
        return search(node->right, id);
    }

    void inorder(AVLNode* node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << "ID: " << node->emergency_id << " | Location: " << node->location
                 << " | Severity: " << node->severity << " | BF: " << getBalance(node) << endl;
            inorder(node->right);
        }
    }

    void displayTree(AVLNode* node, int level, string prefix) {
        if (node != nullptr) {
            cout << string(level * 4, ' ') << prefix << node->emergency_id
                 << " (" << node->location << ", Sev:" << node->severity << ", BF:" << getBalance(node) << ")" << endl;
            if (node->left != nullptr || node->right != nullptr) {
                displayTree(node->left, level + 1, "L--- ");
                displayTree(node->right, level + 1, "R--- ");
            }
        }
    }

public:
    EmergencyAVL() { root = nullptr; }

    void insert(int id, string loc, string sev) { root = insert(root, id, loc, sev); }
    void remove(int id) { root = deleteNode(root, id); }
    AVLNode* search(int id) { return search(root, id); }
    void inorder() { inorder(root); }
    void displayTree() { displayTree(root, 0, "Root: "); }

    void levelOrder() {
        if (root == nullptr) return;
        queue<AVLNode*> q;
        q.push(root);
        while (!q.empty()) {
            AVLNode* node = q.front();
            q.pop();
            cout << "ID: " << node->emergency_id << " | Location: " << node->location
                 << " | Severity: " << node->severity << " | H: " << node->height
                 << " | BF: " << getBalance(node) << endl;
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
};

int main() {
    EmergencyAVL avl;
    avl.insert(50, "Sector F-6", "High");
    avl.insert(30, "Blue Area", "Critical");
    avl.insert(70, "Sector G-9", "Medium");
    avl.insert(20, "Sector I-8", "Low");
    avl.insert(40, "Sector E-7", "High");
    avl.insert(60, "Sector F-10", "Critical");
    avl.insert(80, "Sector G-11", "Medium");
    avl.insert(10, "Sector H-12", "Critical");
    avl.insert(25, "Sector F-8", "High");
    avl.insert(35, "Sector G-6", "Low");
    avl.insert(65, "Sector I-10", "Medium");
    avl.insert(90, "Sector B-17", "High");

    cout << "--- In-order Traversal (Sorted by Emergency ID) ---" << endl;
    avl.inorder();

    cout << "\n--- Level-order (BFS) Traversal ---" << endl;
    avl.levelOrder();

    AVLNode* found = avl.search(60);
    if (found)
        cout << "\nSearch ID 60: " << found->emergency_id << " -> " << found->location << " (" << found->severity << ")" << endl;
    else
        cout << "\nSearch ID 60: Not Found" << endl;

    avl.remove(10);
    avl.remove(70);

    cout << "\n--- Final Balanced AVL Tree Structure After Deletions (10, 70) ---" << endl;
    avl.displayTree();

    return 0;
}
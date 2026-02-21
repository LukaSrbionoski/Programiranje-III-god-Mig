#include <bits/stdc++.h>
using namespace std;

class AVLNode {
public:
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;
    AVLNode(int k) {
        key = k;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class AVLTree {
private:
    AVLNode* root;

    int getHeight(AVLNode* node) {
        if (node) {
            return node->height;
        } else {
            return 0;
        }
    }

    int getBalance(AVLNode* node) {
        if (node) {
            return getHeight(node->left) - getHeight(node->right);
        } else {
            return 0;
        }
    }
    void updateHeight(AVLNode* node) {
        if (node) {
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        }
    }

    AVLNode* rotateLeft(AVLNode* z) {
        AVLNode* y = z->right;
        AVLNode* T2 = y->left;
        y->left = z;
        z->right = T2;
        updateHeight(z);
        updateHeight(y);
        return y;
    }

    AVLNode* rotateRight(AVLNode* z) {
        AVLNode* y = z->left;
        AVLNode* T3 = y->right;
        y->right = z;
        z->left = T3;
        updateHeight(z);
        updateHeight(y);
        return y;
    }

    AVLNode* rotateLeftRight(AVLNode* z) {
        z->left = rotateLeft(z->left);
        return rotateRight(z);
    }

    AVLNode* rotateRightLeft(AVLNode* z) {
        z->right = rotateRight(z->right);
        return rotateLeft(z);
    }

    AVLNode* insert(AVLNode* node, int key) {
        if (!node) {
            return new AVLNode(key);
        }
        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        } else {
            return node;
        }
        updateHeight(node);
        int balance = getBalance(node);
        if (balance > 1 && key < node->left->key) {
            return rotateRight(node);
        }

        if (balance < -1 && key > node->right->key) {
            return rotateLeft(node);
        }

        if (balance > 1 && key > node->left->key) {
            return rotateLeftRight(node);
        }

        if (balance < -1 && key < node->right->key) {
            return rotateRightLeft(node);
        }

        return node;
    }

    AVLNode* search(AVLNode* node, int key) {
        if (!node || node->key == key) {
            return node;
        }

        if (key < node->key) {
            return search(node->left, key);
        }
        return search(node->right, key);
    }

    void inorderTraversal(AVLNode* node, vector<int>& result) {
        if (node) {
            inorderTraversal(node->left, result);
            result.push_back(node->key);
            inorderTraversal(node->right, result);
        }
    }

    void clear(AVLNode* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    AVLTree() {
        root = nullptr;
    }

    ~AVLTree() {
        clear(root);
    }

    void insert(int key) {
        root = insert(root, key);
    }

    bool search(int key) {
        return search(root, key) != nullptr;
    }

    vector<int> inorderTraversal() {
        vector<int> result;
        inorderTraversal(root, result);
        return result;
    }
};


void testAVLTree() {
    cout << "=== Testing AVL Tree ===" << endl;

    AVLTree avl;
    vector<int> keys = {10, 20, 30, 40, 50, 25};

    for (int key : keys) {
        avl.insert(key);
    }

    vector<int> traversal = avl.inorderTraversal();
    cout << "Inorder traversal: ";
    for (int val : traversal) {
        cout << val << " ";
    }
    cout << endl;
    cout << "Search 25: " << (avl.search(25) ? "Found" : "Not found") << endl;
    cout << "Search 100: " << (avl.search(100) ? "Found" : "Not found") << endl;
}
int main() {
    testAVLTree();
    return 0;
}
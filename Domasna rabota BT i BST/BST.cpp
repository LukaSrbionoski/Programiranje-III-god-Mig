#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node *left;
    Node *right;
    Node(int v) {
        this->val = v;
        this->left = nullptr;
        this->right = nullptr;
    }
};
class BST {
private:
    Node* root;
public:

    Node* insert(Node* node, int v) {
        if (node == nullptr)
            return new Node(v);

        if (v < node->val)
            node->left = insert(node->left, v);
        else if (v > node->val)
            node->right = insert(node->right, v);

        return node;
    }

    bool find(Node* node, int v) {
        if (node == nullptr) return false;
        if (node->val == v) return true;

        if (v < node->val) {
            return find(node->left, v);
        }
        else {
            return find(node->right, v);
        }
    }

    void dfs_recursion(Node* node) {
        if (node == nullptr) return;
        cout << node->val << " ";
        dfs_recursion(node->left);
        dfs_recursion(node->right);
    }

    void dfs_non_recursion(Node* node) {
        if (node == nullptr) return;
        stack<Node*> st;
        st.push(node);
        while (!st.empty()) {
            Node* current = st.top();
            st.pop();
            cout << current->val << " ";
            if (current->right != nullptr)
                st.push(current->right);
            if (current->left != nullptr)
                st.push(current->left);
        }
    }


    void bfs(Node* root) {
        if (root == nullptr) return;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            cout << current->val << " ";
            if (current->left != nullptr)
                q.push(current->left);
            if (current->right != nullptr)
                q.push(current->right);
        }
    }
    int sum(Node* node) {
        if (!node) return 0;
        return node->val + sum(node->left) + sum(node->right);
    }

};
int main() {
    BST bst;
    Node* root = nullptr;

    root = bst.insert(root, 10);
    root = bst.insert(root, 5);
    root = bst.insert(root, 15);
    root = bst.insert(root, 3);
    root = bst.insert(root, 7);
    root = bst.insert(root, 12);
    root = bst.insert(root, 18);
    cout<<"DFS_recursion : ";
    bst.dfs_recursion(root);
    cout<< "\nDFS_non_recursion: ";
    bst.dfs_non_recursion(root);
    cout<<"\nBFS : ";
    bst.bfs(root);
    int testValues[] = {3, 8, 12, 20};
    cout << "\nTesting find function:" << endl;

    for (int i = 0; i < 4; i++) {
        int val = testValues[i];
        if (bst.find(root, val)) {
            cout << "Value " << val << " is in the tree" << endl;
        } else {
            cout << "Value " << val << " is NOT in the tree" << endl;
        }


    }
    cout << "\nSum of all numbers in the tree: " << bst.sum(root) << endl;
        return 0;
    }
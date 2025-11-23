#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v) {
        this->val = v;
        this->left = nullptr;
        this->right = nullptr;
    }
};
class BT {
    Node* root;
public:
    BT() {
        root = nullptr;
    }
    void setroot(int v) {
        root=new Node(v);
    }
    Node* getroot() {
        return root;
    }
    void insert(int v) {
        Node* newNode = new Node(v);
        if (!root) {
            root = newNode;
            return;
        }
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            if (!current->left) {
                current->left = newNode;
                return;
            } else {
                q.push(current->left);
            }

            if (!current->right) {
                current->right = newNode;
                return;
            } else {
                q.push(current->right);
            }
        }
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
    BT tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    cout<<"DFS_recursion : ";
    tree.dfs_recursion(tree.getroot());
    cout<< "\nDFS_non_recursion: ";
    tree.dfs_non_recursion(tree.getroot());
    cout<<"\nBFS : ";
    tree.bfs(tree.getroot());
    int testValues[] = {1, 8, 7, 13};
    cout << "\nTesting find function:" << endl;

    for (int i = 0; i < 4; i++) {
        int val = testValues[i];
        if (tree.find(tree.getroot(), val)) {
            cout << "Value " << val << " is in the tree" << endl;
        } else {
            cout << "Value " << val << " is NOT in the tree" << endl;
        }
    }
        cout << "Sum of all elements: " << tree.sum(tree.getroot()) << endl;

        return 0;
    }


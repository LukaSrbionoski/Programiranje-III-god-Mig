#include<bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node *next;
};

struct linkedList {
    Node *head = nullptr;
};

void addNode(linkedList &l, int x) {
    Node *newNode = new Node();
    newNode->val = x;
    newNode->next = nullptr;
    
    if (l.head == nullptr) {
        l.head = newNode;
    } else {
        Node *p = l.head;
        while (p->next != nullptr) {
            p = p->next;
        }
        p->next = newNode;
    }
}

void insertNode(linkedList &l, int x, int position = 0) {
    if (position < 0) {
        cout << "Invalid position!\n";
        return;
    }
    
    Node *newNode = new Node();
    newNode->val = x;

    if (position == 0) {
        newNode->next = l.head;
        l.head = newNode;
        return;
    }

    Node *p = l.head;
    for (int i = 0; i < position - 1 && p != nullptr; i++) {
        p = p->next;
    }
    
    if (p == nullptr) {
        cout << "Position out of bounds!\n";
        delete newNode;
        return;
    }
    
    newNode->next = p->next;
    p->next = newNode;
}

void removeNode(linkedList &l, int x) {
    if (l.head == nullptr) {
        cout << "List is empty!\n";
        return;
    }

    if (l.head->val == x) {
        Node *temp = l.head;
        l.head = l.head->next;
        delete temp;
        return;
    }

    Node *p = l.head;
    while (p->next != nullptr && p->next->val != x) {
        p = p->next;
    }
    
    if (p->next == nullptr) {
        cout << "Value " << x << " not found in the list!\n";
        return;
    }
    
    Node *temp = p->next;
    p->next = p->next->next;
    delete temp;
}

void outputList(const linkedList &l) {
    Node *p = l.head;
    cout << "List: ";
    while (p != nullptr) {
        cout << p->val;
        if (p->next != nullptr) {
            cout << " -> ";
        }
        p = p->next;
    }
    cout << " -> NULL\n";
}

void insertSorted(linkedList &l, int x) {
    Node *newNode = new Node();
    newNode->val = x;
    newNode->next = nullptr;

    if (l.head == nullptr || x < l.head->val) {
        newNode->next = l.head;
        l.head = newNode;
        return;
    }

    Node *p = l.head;
    while (p->next != nullptr && p->next->val < x) {
        p = p->next;
    }

    newNode->next = p->next;
    p->next = newNode;
}

void removeDuplicates(linkedList &l) {
    if (l.head == nullptr) return;
    
    Node *p = l.head;
    while (p->next != nullptr) {
        if (p->val == p->next->val) {
            Node *temp = p->next;
            p->next = p->next->next;
            delete temp;
        } else {
            p = p->next;
        }
    }
}

linkedList mergeSortedNoDuplicates(const linkedList &list1, const linkedList &list2) {
    linkedList result;

    Node *p = list1.head;
    while (p != nullptr) {
        insertSorted(result, p->val);
        p = p->next;
    }

    p = list2.head;
    while (p != nullptr) {
        insertSorted(result, p->val);
        p = p->next;
    }

    removeDuplicates(result);
    
    return result;
}

void bubbleSort(linkedList &l) {
    if (l.head == nullptr || l.head->next == nullptr) {
        return; 
    }
    
    bool swapped = true;
    while (swapped){
        swapped = false;
        Node *current = l.head;
        Node *prev = nullptr;
        
        while (current != nullptr && current->next != nullptr) {
            if (current->val > current->next->val) {
                Node *nextNode = current->next;
                
                if (prev == nullptr) {
                    l.head = nextNode;
                } else {
                    prev->next = nextNode;
                }
                
                current->next = nextNode->next;
                nextNode->next = current;
                
                swapped = true;
                prev = nextNode;
            } else {
                prev = current;
                current = current->next;
            }
        }
    }
}

void insertionSort(linkedList &l) {
    if (l.head == nullptr || l.head->next == nullptr) {
        return;
    }
    
    Node *sorted = nullptr;
    
    Node *current = l.head;
    while (current != nullptr) {
        Node *next = current->next;

        if (sorted == nullptr || current->val < sorted->val) {
            current->next = sorted;
            sorted = current;
        } else {
            Node *temp = sorted;
            while (temp->next != nullptr && temp->next->val < current->val) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        
        current = next;
    }
    
    l.head = sorted;
}

int main() {
    
    /* // zad1
        linkedList myList;
        int n; cin>> n;
        for (int i = 0; i < n; i++) {
            int x; cin >> x;
            insertSorted(myList, x);
            outputList(myList);
        }
    */


    /*  // zad2
        linkedList myList1, myList2, finalList;
        int n1, n2;
        cin >> n1 >> n2;
        for (int i = 0; i < n1; i++) {
            int x; cin >> x;
            addNode(myList1, x);
        }
        for (int i = 0; i < n2; i++) {
            int x; cin >> x;
            addNode(myList2, x);
        }
        myList1 = mergeSortedNoDuplicates(myList1, myList2);
        outputList(myList1);
    */
    /* // zad3 
        linkedList myList;
        int n; cin >> n;
        for (int i = 0; i < n; i++) {
            int x; cin >> x;
            addNode(myList, x);
        }

        //bubbleSort(myList);
        insertionSort(myList);
        outputList(myList);
    */
    

    return 0;
}
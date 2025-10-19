#include<bits/stdc++.h>

struct Node {
    int val;
    Node *next;
    Node *prev;
};

struct DoubleLinkedList {
    Node *head = nullptr;
    Node *tail = nullptr;
};

void add(DoubleLinkedList &list, int x) {
    Node *newNode = new Node();
    newNode->val = x;
    newNode->next = nullptr;
    newNode->prev = list.tail;
    
    if (list.head == nullptr) {
     
        list.head = newNode;
        list.tail = newNode;
    } else {
      
        list.tail->next = newNode;
        list.tail = newNode;
    }
}


void addInPosition(DoubleLinkedList &list, int x, int position) {
    if (position < 0) {
        std::cout << "Invalid position!\n";
        return;
    }
    
   
    if (position == 0 || list.head == nullptr) {
        Node *newNode = new Node();
        newNode->val = x;
        newNode->prev = nullptr;
        newNode->next = list.head;
        
        if (list.head != nullptr) {
            list.head->prev = newNode;
        } else {
            list.tail = newNode; 
        }
        list.head = newNode;
        return;
    }
    
    Node *current = list.head;
    int currentPos = 0;
    
    
    while (current != nullptr && currentPos < position) {
        current = current->next;
        currentPos++;
    }
    
    if (current == nullptr) {
        
        add(list, x);
    } else {
       
        Node *newNode = new Node();
        newNode->val = x;
        newNode->next = current;
        newNode->prev = current->prev;
        
        current->prev->next = newNode;
        current->prev = newNode;
    }
}


void remove(DoubleLinkedList &list, int x) {
    if (list.head == nullptr) {
        std::cout << "List is empty!\n";
        return;
    }
    
    Node *current = list.head;
    
    
    while (current != nullptr && current->val != x) {
        current = current->next;
    }
    
    if (current == nullptr) {
        std::cout << "Value " << x << " not found in the list!\n";
        return;
    }
    
    
    if (current->prev != nullptr) {
        current->prev->next = current->next;
    } else {
      
        list.head = current->next;
    }
    
    if (current->next != nullptr) {
        current->next->prev = current->prev;
    } else {
       
        list.tail = current->prev;
    }
    
    delete current;
    std::cout << "Value " << x << " removed successfully.\n";
}


Node* search(DoubleLinkedList &list, int x) {
    Node *current = list.head;
    int position = 0;
    
    while (current != nullptr) {
        if (current->val == x) {
            std::cout << "Value " << x << " found at position " << position << ".\n";
            std::cout << "Memory address: " << current << "\n";
            return current;
        }
        current = current->next;
        position++;
    }
    
    std::cout << "Value " << x << " not found in the list.\n";
    return nullptr;
}


void outputList(const DoubleLinkedList &list) {
    Node *current = list.head;
    std::cout << "List: ";
    while (current != nullptr) {
        std::cout << current->val;
        if (current->next != nullptr) {
            std::cout << " <-> ";
        }
        current = current->next;
    }
    std::cout << " -> NULL\n";
}


void deleteList(DoubleLinkedList &list) {
    Node *current = list.head;
    while (current != nullptr) {
        Node *temp = current;
        current = current->next;
        delete temp;
    }
    list.head = nullptr;
    list.tail = nullptr;
}


int main() {
    DoubleLinkedList list;
    
    std::cout << "=== Testing Double Linked List ===\n\n";
    
  
    std::cout << "Adding nodes to the end:\n";
    add(list, 10);
    add(list, 20);
    add(list, 30);
    add(list, 40);
    add(list, 50);
    outputList(list);
    
    
    std::cout << "\n=== Testing Search Function with Memory Addresses ===\n";
    Node *foundNode1 = search(list, 20);
    if (foundNode1 != nullptr) {
        std::cout << "Node value: " << foundNode1->val << "\n";
        std::cout << "Previous node value: " << (foundNode1->prev != nullptr ? std::to_string(foundNode1->prev->val) : "NULL") << "\n";
        std::cout << "Next node value: " << (foundNode1->next != nullptr ? std::to_string(foundNode1->next->val) : "NULL") << "\n\n";
    }
    
    Node *foundNode2 = search(list, 40);
    if (foundNode2 != nullptr) {
        std::cout << "Node value: " << foundNode2->val << "\n";
        std::cout << "Previous node value: " << (foundNode2->prev != nullptr ? std::to_string(foundNode2->prev->val) : "NULL") << "\n";
        std::cout << "Next node value: " << (foundNode2->next != nullptr ? std::to_string(foundNode2->next->val) : "NULL") << "\n\n";
    }
    
    
    Node *notFound = search(list, 100);
    if (notFound == nullptr) {
        std::cout << "Correctly returned nullptr for non-existent value.\n\n";
    }
    
    
    std::cout << "Adding at position 2:\n";
    addInPosition(list, 25, 2);
    outputList(list);
    
   
    std::cout << "Searching for the newly added value:\n";
    Node *newNode = search(list, 25);
    if (newNode != nullptr) {
        std::cout << "New node memory address: " << newNode << "\n";
        std::cout << "Previous node value: " << (newNode->prev != nullptr ? std::to_string(newNode->prev->val) : "NULL") << "\n";
        std::cout << "Next node value: " << (newNode->next != nullptr ? std::to_string(newNode->next->val) : "NULL") << "\n\n";
    }
    
    
    std::cout << "Removing value 30:\n";
    remove(list, 30);
    outputList(list);
    
   
    std::cout << "Searching for removed value:\n";
    Node *removedNode = search(list, 30);
    if (removedNode == nullptr) {
        std::cout << "Correctly returned nullptr for removed value.\n\n";
    }
    
   
    std::cout << "=== Testing Edge Cases ===\n";
    DoubleLinkedList emptyList;
    
    std::cout << "Searching in empty list:\n";
    Node *emptySearch = search(emptyList, 10);
    if (emptySearch == nullptr) {
        std::cout << "Correctly returned nullptr for empty list search.\n\n";
    }
    
   
    std::cout << "=== Using Returned Pointer to Access Data ===\n";
    Node *headNode = search(list, 10);
    if (headNode != nullptr) {
        std::cout << "Direct access via returned pointer:\n";
        std::cout << "Head node value: " << headNode->val << "\n";
        std::cout << "Head node address: " << headNode << "\n";
        
        
        std::cout << "Modifying head value from 10 to 15 via pointer...\n";
        headNode->val = 15;
        outputList(list);
        
       
        search(list, 15);
    }
    

    deleteList(list);
    deleteList(emptyList);
    
    return 0;
}
#include <iostream>

struct Node {
    int val;
    Node *next;
    Node *prev;
};

struct DoubleLinkedList {
    Node *head = nullptr;
    Node *tail = nullptr;
};

// Add a node to the end of the list
void add(DoubleLinkedList &list, int x) {
    Node *newNode = new Node();
    newNode->val = x;
    newNode->next = nullptr;
    newNode->prev = list.tail;
    
    if (list.head == nullptr) {
        // First node in the list
        list.head = newNode;
        list.tail = newNode;
    } else {
        // Add to the end
        list.tail->next = newNode;
        list.tail = newNode;
    }
}

// Add a node at a specific position (0-based index)
void addInPosition(DoubleLinkedList &list, int x, int position) {
    if (position < 0) {
        std::cout << "Invalid position!\n";
        return;
    }
    
    // If position is 0 or list is empty, insert at head
    if (position == 0 || list.head == nullptr) {
        Node *newNode = new Node();
        newNode->val = x;
        newNode->prev = nullptr;
        newNode->next = list.head;
        
        if (list.head != nullptr) {
            list.head->prev = newNode;
        } else {
            list.tail = newNode; // List was empty, so new node is also tail
        }
        list.head = newNode;
        return;
    }
    
    Node *current = list.head;
    int currentPos = 0;
    
    // Find the node at the position where we want to insert
    while (current != nullptr && currentPos < position) {
        current = current->next;
        currentPos++;
    }
    
    if (current == nullptr) {
        // Position is beyond the end, add to the tail
        add(list, x);
    } else {
        // Insert before current node
        Node *newNode = new Node();
        newNode->val = x;
        newNode->next = current;
        newNode->prev = current->prev;
        
        current->prev->next = newNode;
        current->prev = newNode;
    }
}

// Remove a node with specific value (first occurrence)
void remove(DoubleLinkedList &list, int x) {
    if (list.head == nullptr) {
        std::cout << "List is empty!\n";
        return;
    }
    
    Node *current = list.head;
    
    // Find the node to remove
    while (current != nullptr && current->val != x) {
        current = current->next;
    }
    
    if (current == nullptr) {
        std::cout << "Value " << x << " not found in the list!\n";
        return;
    }
    
    // Update neighbors' pointers
    if (current->prev != nullptr) {
        current->prev->next = current->next;
    } else {
        // Removing head node
        list.head = current->next;
    }
    
    if (current->next != nullptr) {
        current->next->prev = current->prev;
    } else {
        // Removing tail node
        list.tail = current->prev;
    }
    
    delete current;
    std::cout << "Value " << x << " removed successfully.\n";
}

// Search for a value in the list and return memory address
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

// Output the list from head to tail
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

// Function to delete entire list and free memory
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

// Example usage and testing
int main() {
    DoubleLinkedList list;
    
    std::cout << "=== Testing Double Linked List ===\n\n";
    
    // Test add function
    std::cout << "Adding nodes to the end:\n";
    add(list, 10);
    add(list, 20);
    add(list, 30);
    add(list, 40);
    add(list, 50);
    outputList(list);
    
    // Test search function with memory addresses
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
    
    // Test searching for non-existent value
    Node *notFound = search(list, 100);
    if (notFound == nullptr) {
        std::cout << "Correctly returned nullptr for non-existent value.\n\n";
    }
    
    // Test addInPosition function and verify memory address changes
    std::cout << "Adding at position 2:\n";
    addInPosition(list, 25, 2);
    outputList(list);
    
    // Search for the newly added value and check its neighbors
    std::cout << "Searching for the newly added value:\n";
    Node *newNode = search(list, 25);
    if (newNode != nullptr) {
        std::cout << "New node memory address: " << newNode << "\n";
        std::cout << "Previous node value: " << (newNode->prev != nullptr ? std::to_string(newNode->prev->val) : "NULL") << "\n";
        std::cout << "Next node value: " << (newNode->next != nullptr ? std::to_string(newNode->next->val) : "NULL") << "\n\n";
    }
    
    // Test remove function and verify the node is gone
    std::cout << "Removing value 30:\n";
    remove(list, 30);
    outputList(list);
    
    // Verify the removed value can't be found anymore
    std::cout << "Searching for removed value:\n";
    Node *removedNode = search(list, 30);
    if (removedNode == nullptr) {
        std::cout << "Correctly returned nullptr for removed value.\n\n";
    }
    
    // Test edge cases
    std::cout << "=== Testing Edge Cases ===\n";
    DoubleLinkedList emptyList;
    
    std::cout << "Searching in empty list:\n";
    Node *emptySearch = search(emptyList, 10);
    if (emptySearch == nullptr) {
        std::cout << "Correctly returned nullptr for empty list search.\n\n";
    }
    
    // Test using the returned pointer to access node data directly
    std::cout << "=== Using Returned Pointer to Access Data ===\n";
    Node *headNode = search(list, 10);
    if (headNode != nullptr) {
        std::cout << "Direct access via returned pointer:\n";
        std::cout << "Head node value: " << headNode->val << "\n";
        std::cout << "Head node address: " << headNode << "\n";
        
        // You can even modify the value through the pointer
        std::cout << "Modifying head value from 10 to 15 via pointer...\n";
        headNode->val = 15;
        outputList(list);
        
        // Verify the change
        search(list, 15);
    }
    
    // Clean up
    deleteList(list);
    deleteList(emptyList);
    
    return 0;
}
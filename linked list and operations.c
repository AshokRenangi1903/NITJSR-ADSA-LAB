#include <stdio.h>
#include <stdlib.h>

// Node structure 
struct Node {
    int data;
    struct Node* next;
};

// traverse and display the linked list
void traverse(struct Node* head) {
    struct Node* temp = head;
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("Linked List: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Insert at beginning
void insertAtBeginning(struct Node** head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = *head;
    *head = newNode;
}

// Insert at end
void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    struct Node* temp = *head;
    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Insert after a specific node
void insertAfter(struct Node* prevNode, int data) {
    if (prevNode == NULL) {
        printf("Previous node cannot be NULL.\n");
        return;
    }
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = prevNode->next;
    prevNode->next = newNode;
}

// Delete a node by key
void deleteNode(struct Node** head, int key) {
    struct Node *temp = *head, *prev = NULL;

    // If head node holds the key
    if (temp != NULL && temp->data == key) {
        *head = temp->next;
        free(temp);
        return;
    }

    // Search for the key
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    // If key not found
    if (temp == NULL) {
        printf("Key %d not found.\n", key);
        return;
    }

    prev->next = temp->next;
    free(temp);
}

// Search an element
int search(struct Node* head, int key) {
    struct Node* temp = head;
    while (temp != NULL) {
        if (temp->data == key)
            return 1; // found
        temp = temp->next;
    }
    return 0; // not found
}

// Main function
int main() {
    struct Node* head = NULL;

    // Insert elements
    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 30);
    traverse(head);

    insertAtBeginning(&head, 5);
    traverse(head);

    insertAfter(head->next, 15);  // insert 15 after 10
    traverse(head);

    // Searching
    int key = 20;
    if (search(head, key))
        printf("Element %d found in the list.\n", key);
    else
        printf("Element %d not found.\n", key);

    // Deletion
    deleteNode(&head, 15);
    traverse(head);

    deleteNode(&head, 5);
    traverse(head);

    deleteNode(&head, 30);
    traverse(head);

    return 0;
}
